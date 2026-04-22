//
// Created by tdela on 22/4/2026.
//

#ifndef IAHOMEWORK_ACTIVATIONS_FUNCTIONS_H
#define IAHOMEWORK_ACTIVATIONS_FUNCTIONS_H
#include "../math/core.h"


namespace ml::activations {

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


        return 0;
    }

    inline float arctg() {

    }

    inline tgh() {

    }

}

#endif //IAHOMEWORK_ACTIVATIONS_FUNCTIONS_H