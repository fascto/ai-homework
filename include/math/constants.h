//
// Created by tdela on 18/4/2026.
//

#ifndef IAHOMEWORK_CONSTANTS_H
#define IAHOMEWORK_CONSTANTS_H


union FloatBits {
    int i;
    float f;
};

namespace math::constants {

    constexpr float PI = 3.14159265358979323846f;
    constexpr float E  = 2.71828182845904523536f;
    constexpr float PHI = 1.6180339887498948482f;

    constexpr float EPSILON = 1.19209290e-07f; // STL impl - std::numeric_limits::epsilon<float>() defines a macro __FLT_EPSILON__ with that value (Small float follow E754 RFC)
}
#endif //IAHOMEWORK_CONSTANTS_H