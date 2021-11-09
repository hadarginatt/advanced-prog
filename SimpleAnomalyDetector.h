

#ifndef SIMPLEANOMALYDETECTOR_H_
#define SIMPLEANOMALYDETECTOR_H_

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"

#include "timeseries.h"
#include <string>
#include <list>
#include <vector>
#define NORMAL_THRESHOLD 0.9
#include <algorithm>
#include <string.h>
#include <math.h>

struct correlatedFeatures{
	string feature1,feature2;  // names of the correlated features
	float corrlation;
	Line lin_reg;
	float threshold;
};


class SimpleAnomalyDetector{
	std::vector<correlatedFeatures> cf;

public:
    vector<correlatedFeatures> mostCorrelatedFeatures;
    SimpleAnomalyDetector();
	virtual ~SimpleAnomalyDetector();

	virtual void learnNormal(const TimeSeries& ts);
	virtual vector<AnomalyReport> detect(const TimeSeries& ts);

	std::vector<correlatedFeatures> getNormalModel(){
		return cf;
	}

    std::vector<Point> getPointsFromAxes(std::vector<float> f_i, std::vector<float> f_j);

    //Setting the threshold of the features as the farthest point from the reg line of the two features.
    float getFeaturesThreshold(std::vector<Point> featurePoints, Line regLine);


};



#endif /* SIMPLEANOMALYDETECTOR_H_ */
