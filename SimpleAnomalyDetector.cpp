#include "SimpleAnomalyDetector.h"
#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <string>
#include <list>
#include <vector>

#define NORMAL_THRESHOLD 0.9
using namespace std;

SimpleAnomalyDetector::SimpleAnomalyDetector() {


    //Setting the features points in a vector.
    vector<Point> getPointsFromAxes(vector<float> f_i, vector<float> f_j) {
        vector<Point> featuresPoints;
        for (int i = 0; i < featuresPoints.size(); i++) {
            featuresPoints[i] = Point(f_i[i], f_j[i]);
        }
        return featuresPoints;
    }
    //Setting the threshold of the features as the farthest point from the reg line of the two features.
    float getFeaturesThreshold(vector<Point> featurePoints, Line regLine) {
        Point farthestPoint = featurePoints[0];
        for (int i = 0; i < featurePoints.size(); i++) {
            if (dev(featurePoints[i], regLine) > dev(farthestPoint, regLine)) {
                farthestPoint = featurePoints[i];
            }
        }
        float threshold = dev(farthestPoint, regLine);
        return threshold;
    }

    //The algoritem from the file (gets the time series).
    virtual void learnNormal(const TimeSeries &ts) {
        vector<string> features = ts.getFeatures();
        float maxPearson = 0;
        int c = -1;
        //Getting the features from the given time series.
        for (int i = 0; i < features.size(); i++) {
            for (int j = i + 1; j < features.size(); j++) {
                vector<float> f_i = ts.getValues(features[i]);
                vector<float> f_j = ts.getValues(features[j]);
                float pearson = abs(pearson(f_i, f_j));
                if (pearson > maxPearson) {
                    maxPearson = pearson;
                }
            }
            // In case the correlation is >= 0.9 the features are correlative.
            if (c != -1 && mostCorrelated >= NORMAL_THRESHOLD) {
                //Setting the struct mostCorrelated with the params of the features.
                correlatedFeatures mostCorrelated;
                mostCorrelated.feature1 = features[i];
                mostCorrelated.feature2 = features[j];
                mostCorrelated.correlation = maxPearson;
                // Getting the points of the features for the linear reg line.
                vector<Point> featuresPoint = getPointsFromAxes(f_i, f_j);
                //Setting the linear reg line of the  feature points.
                Line regLine = linear_reg(featuresPoints, featuresPoints.size());
                mostCorrelated.lin_reg = regLine;
                //Setting the threshold as the farthest point from the reg line
                mostCorrelated.threshold = getFeaturesThreshold(features, regLine);
                //Setting the most correlated features in the vector.
                mostCorelatedFeatures.push_back(mostCorrelated);
            }
        }
    }
    /*
    Returns a list of all correlated features.
    */
    vector<correlatedFeatures> getNormalModel() {
        return mostCorrelatedFeatures;
    }

    /*
     Learns the correlation of the most correlated features and reports deviations once detected.
     */
    virtual vector<AnomalyReport> detect(const TimeSeries &ts) {
        vector<AnomalyReport> reports;
        //Pre-Learning the Normal params of the correlative features.
        this.learnNormal(ts);
        for (int i = 0; i < this->mostCorrelatedFeatures.size(); i++) {
            vector<float> feature1_values = ts.getValues(this->mostCorrelatedFeatures[i].feature1);
            vector<float> feature2_values = ts.getValues(this->mostCorrelatedFeatures[i].feature2);
            vector<Point> testPoints;
            for (int i = 0; i < feature1_values.size(); i++) {
                Point *testPoint = new Point(feature1_values[i], feature2_values[i]);
                testPoints.push_back(testPoint);
            }
            for (int i = 0; i < feature1_values.size(); i++) {
                Line linearReg = this->mostCorrelatedFeatures[i].lin_reg.f(feature1_values[i])
                float distance = abs(linearReg - feature2_values[i]);
                float correlation = this->mostCorrelatedFeatures[i].correlation;
                //In case there is a deviation, reporting the detection.
                if (distance > correlation) {
                    String strReport = mostCorrelatedFeatures.feature1 + "-" + mostCorrelatedFeatures.feature2;
                    //Reporting the features description and timeStep.
                    AnomalyReport *newReport = new AnomalyReport(strReport, (long) i);
                }
            }
        }
        return anomalyReports;
    }
}



