#include "timeseries.h"
#include <string>
#include <vector>

using namespace std;

TimeSeries::TimeSeries(const char *fileName) {
    ifstream file(fileName);
    string feature, value;

    // Adding all of the features listed in the file into the features vector.
    while (getline(file, feature, ',')) {
        features.push_back(feature);

        // Adding a vector of floats to each feature in _map.
        vector<float> floats;
        _map[feature] = floats;
    }

    int size = features.size();

    for (string line; getline(file, line); ) {
        stringstream st(line);
        int i = 0;

        // Adding the values in a line to their matching feature.
        while (getline(st, value, ',') && i < size) {
            string s = features[i];
            _map[s].push_back(stof(value));
            i++;
        }
    }

    file.close();
}

vector<string> TimeSeries::getFeatures() {
    return features;
}

const vector<float>& TimeSeries::getValues(const string& feature) const {
    return _map.at(feature);
}

float TimeSeries::getValueByTimeStep(string& feature, int i) {
    return _map.at(feature).at(i);
}

