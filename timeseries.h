#ifndef TIMESERIES_H_
#define TIMESERIES_H_

#include <string>
#include <vector>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class TimeSeries{

public:
    map<string, vector<float>> _map;
    vector<string> features;

	TimeSeries(const char* fileName) {
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

    vector<string> getFeatures() const;

    // Returns a list of values associated with a feature.
    const vector<float>& getValues(const string& feature) const;

    // Returns the i'th value of a feature (the object in line i, row j).
    float getValueByTimeStep(string& feature, int i) const;

    ~TimeSeries() {

    };
};



#endif /* TIMESERIES_H_ */
