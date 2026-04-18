//
// Created by tdela on 15/4/2026.
//

#ifndef IAHOMEWORK_MATH_TEST_H
#define IAHOMEWORK_MATH_TEST_H

#include <functional>
#include <iostream>

inline long long factorial(int a) {
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

typedef float (*f)(float);

struct function {
    f func{};
    unsigned int order{1};
    float h{0.01f};
};


inline function derivative(const function& f) {
    return function { .func = f.func , .order=f.order + 1 };
};

inline float evaluate(function f, const float eval_points) {
    float result{.0f};

    if (f.order <= 0) {
        return f.func(eval_points);
    } else if (f.order == 1)
        result += ((f.func(eval_points + f.h)) - (f.func(eval_points - f.h))) / (2*f.h);
    else {
        f.order= f.order - 1;
        result += (evaluate(f, eval_points + f.h) - evaluate(f, eval_points - f.h)) / (2*f.h);
    }

    return result;
}

    constexpr float epsilon = 1e-6;

inline float abs(const float x) {
    if (x < 0) return -x;
    return x;
}

inline float taylor(function& f, const float x, const float a=0, const unsigned int n=500) {

    float result{.0f};
    float prev{.0f};

    f.order = 0;
    for (int i=0; i<n; i++) {
        prev = result;
        result += evaluate(f, a)/static_cast<float>(factorial(i)) * pow(x - a, i);;

        if (abs(result-prev) < epsilon)
            return result;

        f.order++;
    }

    return result;
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

        if (abs(result-prev) < epsilon)
            return result;
    }
    return result;
}

constexpr float PI = 3.14159265358979f;



class math_test {

};


#endif //IAHOMEWORK_MATH_TEST_H