#include "anomaly_detection_util.h"
#include <cmath>
using namespace std;

// Hadar Ginatt, ID: 207542663
// Dar Mendelowitz, ID: 316491208

float mean(const float* x, int size) {
    float num = 0;
    for (int i = 0; i < size; i++) {
        num += x[i];
    }
    return num / (float) size;
}

float deviation(float var) {
    return sqrt(var);
}

float sum(float* x, float* y, int size) {
    float s = 0;
    for (int i = 0; i < size; i++) {
        s += x[i] * y[i];
    }
    return s;
}

float var(float* x, int size) {
    float m = mean(x, size), num = sum(x, x, size);
    return (num / (float) size) - (m * m);
}

float cov(float* x, float* y, int size) {
    float num = sum(x, y, size);
    return (num / (float) size) - (mean(x, size) * mean(y, size));
}

float pearson(float* x, float* y, int size) {
    float c = cov(x, y, size);
    float devX = deviation(var(x, size));
    float devY = deviation(var(y, size));

    return (float) c / (devX * devY);
}

Line linear_reg(Point** points, int size) {
    float x[size], y[size];

    for (int i = 0; i < size; i++) {
        x[i] = points[i]->x;
        y[i] = points[i]->y;
    }

    float co = cov(x, y, size);
    float a = co / var(x, size);
    float b = mean(y, size) - a * mean(x, size);

    return Line(a, b);
}

float dev(Point p, Point** points, int size) {
    return dev(p, linear_reg(points, size));
}

float dev(Point p, Line l) {
    // calculating the absolute value of two points
    float ab = l.f(p.x) - p.y;
    if (ab < 0) {
        ab *= -1;
    }

    return ab;
}