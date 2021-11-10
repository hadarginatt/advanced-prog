#include "timeseries.h"

vector<string> TimeSeries::getFeatures() const {
    return _features;
}

const vector<float>& TimeSeries::getValues(const string& feature) const {
    return _map.at(feature);
}

float TimeSeries::getValueByTimeStep(string& feature, int i) const {
    return _map.at(feature).at(i);
}