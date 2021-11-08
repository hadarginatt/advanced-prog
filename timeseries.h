#ifndef ADVANCED_PROG_TIMESERIES_H
#define ADVANCED_PROG_TIMESERIES_H
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class TimeSeries {
    map<string, vector<float>> _map;
    vector<string> features;
    friend void learnNormal(const TimeSeries& ts);

public:
    explicit TimeSeries(const char* fileName) {

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
    };

    // Returns a list of values associated with a feature.
    const vector<float>& getValues(const string& feature) const {
        return _map.at(feature);
    }

    // Returns the i'th value of a feature (the object in line i, row j).
    float getValueByTimeStep(string& feature, int i) {
        return _map.at(feature).at(i);
    }
    //Getter to the features vector.
    vector<string> getFeatures() {
        return features;
    }

    ~TimeSeries() = default;;
};

#endif
