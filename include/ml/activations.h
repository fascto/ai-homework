//
// Created by tdela on 22/4/2026.
//

#ifndef IAHOMEWORK_ACTIVATIONS_FUNCTIONS_H
#define IAHOMEWORK_ACTIVATIONS_FUNCTIONS_H
#include "../math/core.h"


namespace ml::activations {

    enum class ActivationFunction {
        STEP,
        SIGMOID,
        RELU,
        ARCTG,
        TANH
    };

    inline float step(const float input) {
        if (input < 0)
            return 0;
        return 1;
    }

    inline float sigmoid(const float input) {
        return math::core::inverse(1+math::core::exp((-1.f)*input));
    }

    inline float ReLU(const float input) {
        if (input < 0) return 0;
        return input;
    }

    inline float arctg(float input) {

    }

    inline float tanh(float input) {

    }

    inline float apply(const ActivationFunction activation_function, const float x) {
        switch (activation_function) {
            case ActivationFunction::STEP:
                return step(x);
            case ActivationFunction::SIGMOID:
                return sigmoid(x);
            case ActivationFunction::RELU:
                return ReLU(x);
            case ActivationFunction::TANH:
                return tanh(x);
            case ActivationFunction::ARCTG:
                return arctg(x);
            default:
                return 0;
        }
    }

}

#endif //IAHOMEWORK_ACTIVATIONS_FUNCTIONS_H