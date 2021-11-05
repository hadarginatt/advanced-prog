#ifndef ADVANCED_PROG_SIMPLEANOMALYDETECTOR_H
#define ADVANCED_PROG_SIMPLEANOMALYDETECTOR_H
#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <string>
//#include <stl>
#include <list>
#define NORMAL_THRESHOLD 0.9
using namespace std;
//

struct correlatedFeatures {
    string feature1, feature2;
    float correlation;
    Line lin_reg;
    //the longest point (max deviation from reg line)
    float threshold;
};

class SimpleAnomalyDetector: public TimeSeriesAnomalyDetector {
    vector<correlatedFeatures> mostCorrelatedFeatures;


public:
    SimpleAnomalyDetector();
    virtual ~SimpleAnomalyDetector();

    //setting the features points in a vector
    vector<Point> getPointsFromAxes(vector<float> f_i, vector<float> f_j) {
        vector<Point> featuresPoints;
        for (int i = 0; i < featuresPoints.size(); i++) {
            featuresPoints[i] = Point(f_i[i], f_j[i]);
        }
        return featuresPoints;
    }
    //declaring the threshold of the features as the farthest point from the reg line of the two features.
    float getFeaturesThreshold (vector<Point> featurePoints, Line regLine) {
        Point farthestPoint = featurePoints[0];
        for (int i = 0 ; i < featurePoints.size() ; i++) {
            if (dev(featurePoints[i],regLine) > dev(farthestPoint, regLine)){
                farthestPoint = featurePoints[i];
            }
        }
        float threshold = dev(farthestPoint, regLine);
        return threshold;

    }

    //the algoritem from the file (gets the time series)
    virtual void learnNormal(const TimeSeries& ts) {
        vector<string> features = ts.getFeatures();
        float maxPearson = 0;
        int c = -1;

        for (int i = 0; i < features.size(); i++) {
            for (int j = i + 1; j < features.size(); j++) {
              vector<float> f_i = ts.getValues(features[i]);
              vector<float> f_j = ts.getValues(features[j]);

              float pearson = abs(pearson(f_i,f_j));
              if (pearson > maxPearson) {
                  maxPearson = pearson;
              }
            }

            if (c != -1 && mostCorrelated >= NORMAL_THRESHOLD){
                correlatedFeatures mostCorrelated;
                mostCorrelated.feature1 = features[i];
                mostCorrelated.feature2 = features[j];
                mostCorrelated.correlation = maxPearson;
                vector<Point> featuresPoint = getPointsFromAxes (f_i, f_j);
                //setting the linear reg line of the  feature points
                Line regLine = linear_reg(featuresPoints,featuresPoints.size());
                mostCorrelated.lin_reg = regLine;
                //setting the threshold as the farthest point from the reg line
                mostCorrelated.threshold = getFeaturesThreshold(features ,regLine);
                //setting the most correlated feature
                mostCorelatedFeatures.push_back(mostCorrelated);
                }
            }
        }
    vector<correlatedFeatures> getNormalModel() {
        return mostCorrelatedFeatures;
    }

    //another time series
    virtual vector<AnomalyReport> detect(const TimeSeries& ts) {
        //learning the normal time step
       ts::learnNormal(ts);
        vector<AnomalyReport> anomalyReports;
        for (int i = 0; i < ts.getValues().size(); i++) {
            //if (.... current threshold is crossing the correlatedFeatures threshold){

                AnomalyReport newReport = new AnomalyReport;
                newReport.description = mostCorrelatedFeatures.feature1 +  mostCorrelatedFeatures.feature2;
                cout << newReport.description;
                anomalyReports.push_back(newReport);

    }
            return anomalyReports;
}
};



#endif //ADVANCED_PROG_SIMPLEANOMALYDETECTOR_H
