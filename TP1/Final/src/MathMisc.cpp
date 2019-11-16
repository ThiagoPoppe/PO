#include "MathMisc.h"

void fixPrecision5(float& num) {
    if (std::abs(num) < 1e-5)
        num = 0.0;
}

void fixPrecision5(Vector& v) {
    for (unsigned int i = 0; i < v.GetSize(); i++)
        fixPrecision5(v[i]);
}