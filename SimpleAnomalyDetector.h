#ifndef ADVANCED_PROG_SIMPLEANOMALYDETECTOR_H
#define ADVANCED_PROG_SIMPLEANOMALYDETECTOR_H
#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <string>
using namespace std;
//

struct correlatedFeatures {
    string feature1, feature2;
    float corrlation;
    Line lin_reg;
    float threshold;
};

class SimpleAnomalyDetector: public TimeSeriesAnomalyDetector {
public:
    SimpleAnomalyDetector();
    virtual ~SimpleAnomalyDetector();

    virtual void learnNormal(const TimeSeries& ts);
    virtual vector<AnomalyReport> detect(const TimeSeries& ts);
    vector<correlatedFeatures> getNormalModel();
};

#endif //ADVANCED_PROG_SIMPLEANOMALYDETECTOR_H
