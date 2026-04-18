//
// Created by tdela on 18/4/2026.
//

#ifndef IAHOMEWORK_TYPES_H
#define IAHOMEWORK_TYPES_H

namespace math::types {
    typedef float (*f)(float);

    struct function {
        f func{};
        unsigned int order{1};
        float h{0.01f};
    };
}
#endif //IAHOMEWORK_TYPES_H