#ifndef ADVANCED_PROG_TIMESERIES_H
#define ADVANCED_PROG_TIMESERIES_H
#include <map>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class TimeSeries {
    map<string, vector<float>> _map;
public:
//    TimeSeries() = default;;

    explicit TimeSeries(const char* fileName) {
        vector<string> features;
        ifstream file(fileName);
        string feature;

        while (getline(file, feature, ',')) {
            features.push_back(feature);
        }

        int size = features.size();

        for (string line; getline(file, line); ) {
            for (string s : features) {

            }
        }
    };

    // Returns a list of values associated with a feature.
    const vector<float>& getValues(const string& feature) const {
        return _map.at(feature);
    }

    // Returns the i'th value of a feature (the object in line i, row j).
    float getValueByTimeStep(string& feature, int i) {
        return _map.at(feature).at(i);
    }

    ~TimeSeries() = default;;
};

#endif
