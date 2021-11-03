#ifndef ADVANCED_PROG_ANOMALYDETECTOR_H
#define ADVANCED_PROG_ANOMALYDETECTOR_H
#include "timeseries.h"
#include <string>
#include <vector>
using namespace std;

//class TimeSeries {};

class AnomalyReport {
public:
    const string description;
    const long timeStep;
    AnomalyReport(string description, long timeStep) : description(description), timeStep(timeStep) {}
};

class TimeSeriesAnomalyDetector {
public:
    virtual void learnNormal(const TimeSeries& ts) = 0;
    virtual vector<AnomalyReport> detect(const TimeSeries& ts) = 0;
    virtual ~TimeSeriesAnomalyDetector() {};
};
#endif //ADVANCED_PROG_ANOMALYDETECTOR_H



