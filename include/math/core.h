//
// Created by tdela on 18/4/2026.
//

#ifndef IAHOMEWORK_CORE_H
#define IAHOMEWORK_CORE_H

#include "constants.h"

static constexpr float epsilon = 1e-6;

namespace math::core {
    inline long long factorial(const int a) {
        if (a == 0) return 1;
        if ( a == 1) return a;
        return a * factorial(a - 1);
    }

    inline float pow(const float a, int b) {
        float result = 1.0f;
        while (b > 0) {
            result *= a;
            b--;
        }
        return result;
    }

    inline float abs(const float x) {
        if (x < 0) return -x;
        return x;
    }

    inline float sin(const float x, const float a=0) {

        constexpr int n = 500;

        float result{.0f};
        float prev{.0f};

        int sign = -1;

        for (int i=1; i<n; i+=2) {
            prev = result;
            result += static_cast<float>((sign*(-1))) * pow(x - a, i)/static_cast<float>(factorial(i));
            sign = sign*-1;

            if (abs(result-prev) < epsilon)
                return result;
        }
        return result;
    }

    inline float cos(const float x, const float a=0) {

        constexpr int n = 500;

        float result{.0f};
        float prev{.0f};

        int sign = -1;

        for (int i=0; i<n; i+=2) {
            prev = result;
            result += static_cast<float>((sign*(-1))) * pow(x - a, i)/static_cast<float>(factorial(i));
            sign = sign*-1;

            if (abs(result-prev) < epsilon)
                return result;
        }
        return result;
    }

    inline float exp(const int x, const float a=0) {

        constexpr int n = 500;

        float result{.0f};
        float prev{.0f};

        for (int i=0; i<n; i++) {
            prev = result;
            result += 1/static_cast<float>(factorial(i));

            if (abs(result-prev) < epsilon)
                return pow(result, x);
        }
        return pow(result, x);
    }

    const float e = exp(1);

    inline float pi() {
        constexpr int n = 500;

        float result{.0f};
        float prev{.0f};

        int sign = 1;

        for (int i=1; i<n; i+=2) {
            prev = result;
            result += static_cast<float>(sign) * 4.0f/static_cast<float>(i);
            sign = sign*-1;
            std::cout << result << std::endl;

            if (abs(result-prev) < )
                return result;
        }
        return result;
    }

    inline inverse(float b) {
        return 1.0f/b;
    }

    inline sqrt(float x, float b) {
        pow(x, inverse(b));
    }
}

#endif //IAHOMEWORK_CORE_H