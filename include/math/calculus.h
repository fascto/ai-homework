//
// Created by tdela on 18/4/2026.
//

#ifndef IAHOMEWORK_CALCULUS_H
#define IAHOMEWORK_CALCULUS_H

#include "types.h"

static constexpr float epsilon = 1e-6;

namespace math::calculus {

    inline types::function derivative(const types::function& f) {
        return types::function { .func = f.func , .order=f.order + 1 };
    };

    inline float evaluate(types::function f, const float eval_points) {
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

    inline float taylor(types::function &f, const float x, const float a = 0, const unsigned int n = 500) {
        float result{.0f};
        float prev{.0f};

        f.order = 0;
        for (int i = 0; i < n; i++) {
            prev = result;
            result += evaluate(f, a) / static_cast<float>(core::factorial(i)) * core::pow(x - a, i);

            if (core::abs(result - prev) < epsilon)
                return result;

            f.order++;
        }

        return result;
    }

    inline float nth_root(const float x, const float b) {
        types::function f;
        f.func = [x, b](const float t) -> float {
            return core::pow(t, b)-x;
        };

        auto df = f;
        df.order = 1;

        float result{1.f};
        float prev{1.f};
        for (int i = 0; i < 200; i++) {
            prev = result;
            result = result - (evaluate(f, result)/evaluate(df, result));

            if (core::abs(prev - result) < epsilon_core)
                return result;
        }
        return result;
    }

}

#endif //IAHOMEWORK_CALCULUS_H
