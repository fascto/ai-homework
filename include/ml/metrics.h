//
// Created by tdela on 9/5/2026.
//

#ifndef IAHOMEWORK_METRICS_H
#define IAHOMEWORK_METRICS_H
#include <cmath>
#include <vector>

#include "../math/core.h"

namespace ml::metrics {

    enum class LossFunction {
        // Regression Loss Functions
        MSE,
        HUBER,
        // Classification Loss Functions
        CROSS_ENTROPY,
        HINGE,
    };

    // Mean Squared error
    inline float mse(const std::vector<float>& observed, const std::vector<float>& expected) {

        const auto n = observed.size();
        float result{0.f};
        for ( auto i = 0; i < n; ++i ) {
            result += math::core::pow(expected[i] - observed[i]);
        }

        return math::core::inverse(static_cast<float>(n))*result;

    };

    inline float crossEntropy;

    inline float huberLoss;

    inline float hingeLoss;


    inline float apply(const LossFunction loss_function, const std::vector<float>& observed, const std::vector<float>& expected ) {
        switch (loss_function) {
            case LossFunction::MSE:
                return mse(observed, expected);
            case LossFunction::HUBER:
                return huberLoss;
            case LossFunction::CROSS_ENTROPY:
                return crossEntropy;
            case LossFunction::HINGE:
                return hingeLoss;
            default:
                return -1;
        }
    }

}

#endif //IAHOMEWORK_METRICS_H