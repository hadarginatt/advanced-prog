#ifndef ADVANCED_PROG_TIMESERIES_H
#define ADVANCED_PROG_TIMESERIES_H
#include "SimpleAnomalyDetector.h"
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class TimeSeries {
    map<string, vector<float>> _map;
    vector<string> features;
    friend void SimpleAnomalyDetector::learnNormal(const TimeSeries& ts);

public:
    explicit TimeSeries(const char* fileName);

    // Returns a list of the features.
    vector<string> getFeatures();

    // Returns a list of values associated with a feature.
    const vector<float>& getValues(const string& feature) const;

    // Returns the i'th value of a feature (the object in line i, row j).
    float getValueByTimeStep(string& feature, int i);

    ~TimeSeries() = default;;
};

#endif
