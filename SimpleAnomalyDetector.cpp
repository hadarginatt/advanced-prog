#include "anomaly_detection_util.h"
#include <string>
#include <list>
#include <vector>
#include "timeseries.h"

#define NORMAL_THRESHOLD 0.9

#include "SimpleAnomalyDetector.h"

SimpleAnomalyDetector::SimpleAnomalyDetector() {
    // TOD Auto-generated constructor stub

}

SimpleAnomalyDetector::~SimpleAnomalyDetector() {
    // TOD Auto-generated destructor stub
}

vector<Point> SimpleAnomalyDetector::getPointsFromAxes(vector<float> f_i, vector<float> f_j) {
    vector<Point> featuresPoints;
    for (int i = 0; i < featuresPoints.size(); i++) {
        featuresPoints[i] = Point(f_i[i], f_j[i]);
    }
    return featuresPoints;
}

float SimpleAnomalyDetector::getFeaturesThreshold(vector<Point> featurePoints, Line regLine) {
    Point farthestPoint = featurePoints[0];
    for (int i = 0; i < featurePoints.size(); i++) {
        if (dev(featurePoints[i], regLine) > dev(farthestPoint, regLine)) {
            farthestPoint = featurePoints[i];
        }
    }
    float threshold = dev(farthestPoint, regLine);
    return threshold;
}

void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    vector<string> features = ts.getFeatures();
    float maxPearson = 0;
    int c = -1;
    vector<float> f_i;
    vector<float> f_j;


    float f_1;
    float f_2;

    //Getting the features from the given time series.
    for (int i = 0; i < features.size(); i++) {
        for (int j = i + 1; j < features.size(); j++) {
            f_i = ts.getValues(features[i]);
            //f_1 = ts.getValueByTimeStep(features[i], i);
            //f_2 = ts.getValueByTimeStep(features[j], j);

            vector<float> f_j = ts.getValues(features[j]);
            float f_i_array[f_i.size()];
            float f_j_array[f_j.size()];
            for (int i = 0; i < f_i.size(); i++) {
                f_i_array[i] = f_i[i];
            }
            for (int i = 0; i < f_j.size(); i++) {
                f_j_array[i] = f_j[i];
            }
            std::copy(f_i.begin(), f_i.end(), f_i_array);
            std::copy(f_j.begin(), f_j.end(), f_j_array);

            float pearsoni = abs(pearson(f_i_array, f_j_array, f_i.size()));
            if (pearsoni > maxPearson) {
                maxPearson = pearsoni;
            }
            vector<Point> featuresPoint = getPointsFromAxes(f_i, f_j);
            Point *points[featuresPoint.size()];
            for (int i = 0; i < featuresPoint.size(); i++) {
                points[i] = &featuresPoint[i];
            }

            float mostCorrelated = getFeaturesThreshold(featuresPoint,
                                                        linear_reg(points, featuresPoint.size()));
            // In case the correlation is >= 0.9 the features are correlative.
            if (mostCorrelated >= NORMAL_THRESHOLD) {
                //Setting the struct mostCorrelated with the params of the features.
                correlatedFeatures mostCorrelated;
                mostCorrelated.feature1 = features[i];
                mostCorrelated.feature2 = features[j];
                mostCorrelated.corrlation = maxPearson;
                // Getting the points of the features for the linear reg line.
                vector<Point> featuresPoint = getPointsFromAxes(f_i, f_j);
                //Setting the linear reg line of the  feature points.
                Point *pointsT[featuresPoint.size()];
                for (int i = 0; i < featuresPoint.size(); i++) {
                    points[i] = &featuresPoint[i];
                }
                Line regLine = linear_reg(pointsT, featuresPoint.size());
                mostCorrelated.lin_reg = regLine;
                //Setting the threshold as the farthest point from the reg line
                mostCorrelated.threshold = 1.1 * (getFeaturesThreshold(featuresPoint, regLine));
                //Setting the most correlated features in the vector.
                mostCorrelatedFeatures.push_back(mostCorrelated);
            }
        }
    }
}

vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    vector<AnomalyReport> reports;
    //Pre-Learning the Normal params of the correlative features.
    this->learnNormal(ts);
    for (int i = 0; i < this->mostCorrelatedFeatures.size(); i++) {
        vector<float> feature1_values = ts.getValues(this->mostCorrelatedFeatures[i].feature1);
        vector<float> feature2_values = ts.getValues(this->mostCorrelatedFeatures[i].feature2);
        vector<Point*> testPoints;
        for (int i = 0; i < feature1_values.size(); i++) {
            Point *testPoint = new Point(feature1_values[i], feature2_values[i]);
            testPoints.push_back(testPoint);
        }
        for (int i = 0; i < feature1_values.size(); i++) {
            Line linearReg = this->mostCorrelatedFeatures[i].lin_reg;
            float delta = abs(linearReg.f(feature1_values[i]) - feature2_values[i]);
            float threshold = this->mostCorrelatedFeatures[i].threshold;
            //In case there is a deviation, reporting the detection.
            if (delta > threshold) {
                string strReport = mostCorrelatedFeatures[i].feature1 + "-" + mostCorrelatedFeatures[i].feature2;
                //Reporting the features description and timeStep.
                AnomalyReport *newReport = new AnomalyReport(strReport, (long) i);
            }
        }
    }
    return reports;
}

