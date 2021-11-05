cmake_minimum_required(VERSION 3.17)
project(advanced_prog)

set(CMAKE_CXX_STANDARD 11)

add_executable (advanced_prog
        anomaly_detection_util.h
        anomaly_detection_util.cpp
        AnomalyDetector.h
        AnomalyDetector.cpp
        mainTrain.cpp
        AnomalyDetector.cpp)