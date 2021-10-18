#include "‫‪anomaly_detection_util.h"
#include <cmath>
using namespace std;

float mean(const float* x, int size) {
    if (size <= 0) {
        return 0;
    }
    float num = 0;
    for (int i = 0; i < size; i++) {
        num += x[i];
    }
    return (float) (num / (float) size);
}

float deviation(float var) {
    return sqrt(var);
}

float var(float* x, int size) {
    if (size <= 0) {
        return 0;
    }

    float m = mean(x, size), num = 0;
    for (int i = 0; i < size; i++) {
        num += x[i] * x[i];
    }
    return (float) (num / (float) size) - m * m;
}

float cov(float* x, float* y, int size) {
    if (size <= 0) {
        return 0;
    }

    float num = 0;
    for (int i = 0; i < size; i++) {
        num += x[i] * y[i];
    }
    return num / (float) size - mean(x, size) * mean(y, size);
}

float pearson(float* x, float* y, int size) {
    if (size <= 0) {
        return 0;
    }

    float covar = cov(x, y, size);
    float devX = deviation(var(x, size));
    float devY = deviation(var(y, size));

    return (float) covar / devX * devY;
}

Line linear_reg(Point** points, int size) {
    if (size <= 0) {
        return Line();
    }

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
    return abs(l.f(p.x) - p.y);
}
