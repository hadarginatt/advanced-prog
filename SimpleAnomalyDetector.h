#ifndef ADVANCED_PROG_SIMPLEANOMALYDETECTOR_H
#define ADVANCED_PROG_SIMPLEANOMALYDETECTOR_H
#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <string>
#include <list>
#include <vector>
#define NORMAL_THRESHOLD 0.9

using namespace std;

/*
Defines the correlation between two features according to the given time series.
*/
struct correlatedFeatures {
    string feature1, feature2;
    //According to the pearson result.
    float correlation;
    Line lin_reg;
    //The point with max deviation from reg line of the features.
    float threshold;
};

class SimpleAnomalyDetector : public TimeSeriesAnomalyDetector {
    vector<correlatedFeatures> mostCorrelatedFeatures;


public:
    SimpleAnomalyDetector() = default;

    //Setting the features points in a vector.
    vector<Point> getPointsFromAxes(vector<float> f_i, vector<float> f_j);

    //Setting the threshold of the features as the farthest point from the reg line of the two features.
    float getFeaturesThreshold(vector<Point> featurePoints, Line regLine);

    //The algorithm from the file (gets the time series).
    virtual void learnNormal(const TimeSeries &ts);

    /*
    Returns a list of all correlated features.
    */
    vector<correlatedFeatures> getNormalModel();

    /*
    Learns the correlation of the most correlated features and reports deviations once detected.
    */
    virtual vector<AnomalyReport> detect(const TimeSeries &ts);

    virtual ~SimpleAnomalyDetector() = default;
}


#endif //ADVANCED_PROG_SIMPLEANOMALYDETECTOR_H
