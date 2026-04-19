//
// Created by tdela on 18/4/2026.
//

#ifndef IAHOMEWORK_TYPES_H
#define IAHOMEWORK_TYPES_H

#include <functional>

namespace math::types {
    using f = std::function<float(float)>;

    struct function {
        f func{};
        unsigned int order{0};
        float h{0.01f};
    };
}
#endif //IAHOMEWORK_TYPES_H