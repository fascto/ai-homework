//
// Created by tdela on 18/4/2026.
//

#ifndef IAHOMEWORK_VEC_H
#define IAHOMEWORK_VEC_H
#include <vector>

#include "../core.h"

namespace math::linear_algebra {

    class Vec {

        std::vector<float> storage;
        size_t dim{};

    public:

        Vec(const std::vector<float>& values = std::vector<float>()){

            for (float value : values) {
                storage.push_back(value);
            }
            dim = values.size();
        }

        [[nodiscard]] Vec add(const Vec& v) const {
            if (v.dim != this->dim) throw std::runtime_error("Vector dimensions do not match");

            Vec result{};
            for (size_t i = 0; i < storage.size(); i++)
                result.storage.push_back(v.storage[i] + this->storage[i]);

            return result;
        }

        [[nodiscard]] Vec sub(const Vec& v) const {

            if (v.dim != this->dim) throw std::runtime_error("Vector dimensions do not match");

            Vec result{};
            for (size_t i = 0; i < storage.size(); i++)
                result.storage.push_back(v.storage[i] - this->storage[i]);

            return result;
        }

        [[nodiscard]] Vec scalar_mul(const float scalar) const {
            Vec result{};
            for (const auto& v : storage)
                result.storage.push_back(v * scalar);

            return result;
        }

        [[nodiscard]] Vec scalar_div(const float scalar) const {
            Vec result{};
            for (const auto& v : storage)
                result.storage.push_back(v / scalar);

            return result;
        }

        [[nodiscard]] float dot_mul(const Vec& v) const {

            if (v.dim != this->dim) throw std::runtime_error("Vector dimensions do not match");

            float result{};
            for (size_t i = 0; i < storage.size(); i++) {
                result += this->storage[i] * v.storage[i];
            }

            return result;
        }

        [[nodiscard]] Vec normalization() const {
            const float v_norm = this->norm();
            Vec result{};
            for (auto& v : storage) {
                result.storage.push_back(v/v_norm);
            }

            return result;
        }

        [[nodiscard]] float norm() const {

            float result{0.f};
            for (auto& v : storage) {
                result += core::pow(v);
            }
            return core::sqrt(result);

        }

        void print() const {
            std::cout << '[' << ' ';
            for (int i= 0; auto& v : storage ) {
                if (i == storage.size()-1) std::cout << v << ' ';
                else std::cout << v << ", ";
                i++;
            }
            std::cout << ']' << std::endl;
        }
    };

}

#endif //IAHOMEWORK_VEC_H