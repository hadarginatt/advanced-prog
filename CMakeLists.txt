cmake_minimum_required(VERSION 3.20)
project(adv)

set(CMAKE_CXX_STANDARD 11)

add_executable(adv
        MainTrain.cpp
        anomaly_detection_util.cpp
        anomaly_detection_util.h
        AnomalyDetector.h
        SimpleAnomalyDetector.cpp
        SimpleAnomalyDetector.h
        timeseries.h
        timeseries.cpp)
