//
// Created by tdela on 18/4/2026.
//

#ifndef IAHOMEWORK_CALCULUS_H
#define IAHOMEWORK_CALCULUS_H

#include "types.h"
#include "core.h"

static constexpr float epsilon = 1e-6;

namespace math::calculus {

    inline function derivative(const function& f) {
        return function { .func = f.func , .order=f.order + 1 };
    };

    inline float evaluate(function f, const float eval_points) {
        float result{.0f};

        if (f.order <= 0)
            return f.func(eval_points);
        else if (f.order == 1)
            result += ((f.func(eval_points + f.h)) - (f.func(eval_points - f.h))) / (2*f.h);
        else {
            f.order= f.order - 1;
            result += (evaluate(f, eval_points + f.h) - evaluate(f, eval_points - f.h)) / (2*f.h);
        }

        return result;
    }

    inline float taylor(function& f, const float x, const float a=0, const unsigned int n=500) {

        float result{.0f};
        float prev{.0f};

        f.order = 0;
        for (int i=0; i<n; i++) {
            prev = result;
            result += evaluate(f, a)/static_cast<float>(core::factorial(i)) * core::pow(x - a, i);;

            if (core::abs(result-prev) < epsilon)
                return result;

            f.order++;
        }

        return result;
    }


}

#endif //IAHOMEWORK_CALCULUS_H