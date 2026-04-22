//
// Created by tdela on 18/4/2026.
//

#ifndef IAHOMEWORK_MATRIX_H
#define IAHOMEWORK_MATRIX_H
#include <format>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <vector>

namespace math::linear_algebra {

    class Matrix {
        std::vector<std::vector<float>> storage{};

    public:

        explicit Matrix(std::vector<std::vector<float>> const& matrix = std::vector<std::vector<float>>()) {

            storage.reserve(matrix.size());
            std::ranges::copy(matrix, back_inserter(storage));
        }

        Matrix operator+(const Matrix& matrix) const {
            return sum(matrix, false);
        }

        Matrix operator-(const Matrix& matrix) const {
            return sub(matrix, false);
        }

        Matrix operator*(const Matrix& matrix) const {
            return mul(matrix).value();
        }

        Matrix operator*(const float scalar) const {
            return scalar_mul(scalar);
        }

        Matrix operator/(const float scalar) const {
            return scalar_div(scalar);
        }

        void print() const {
            std::string out = "[\n";
            for (size_t i = 0; i < storage.size(); ++i) {
                out += "    { ";
                for (size_t j = 0; j < storage[0].size(); ++j) {
                    if (j == storage[0].size() - 1)
                        out += std::format("{:>5.2f}", storage[i][j]);
                    else
                        out += std::format("{:>5.2f}, ", storage[i][j]);

                }

                if (i == storage.size() - 1)
                    out += " } ";
                else
                    out += " }, \n";

            }
            out += "\n]";
            std::cout << out << std::endl;
        }

        [[nodiscard]] Matrix sum(const Matrix& matrix, const bool broadcasting = false) const {
            if ( ( matrix.storage.size() != storage.size() ||
                matrix.storage[0].size() != storage[0].size() )
                && !broadcasting) {
                throw std::invalid_argument("Matrix sub matrix must be same dimentions");
            }

            const auto rows = storage.size();
            const auto cols = storage[0].size();

            Matrix result { std::vector(rows, std::vector(cols, 0.f))};
            for (int i = 0; i < storage.size(); ++i) {
                for (int j = 0; j < storage[i].size(); ++j) {
                    result.storage[i][j] = (storage[i][j] + matrix.storage[i][j]);
                }
            }

            return result;
        }

        [[nodiscard]] Matrix sub(const Matrix& matrix, const bool broadcasting = false) const {

            if ( ( matrix.storage.size() != storage.size() ||
                matrix.storage[0].size() != storage[0].size() )
                && !broadcasting) {
                throw std::invalid_argument("Matrix sub matrix must be same dimentions");
            }

            const auto rows = storage.size();
            const auto cols = storage[0].size();

            Matrix result { std::vector(rows, std::vector(cols, 0.f))};
            for (int i = 0; i < storage.size(); ++i) {
                for (int j = 0; j < storage[i].size(); ++j) {
                    result.storage[i][j] = (storage[i][j] - matrix.storage[i][j]);
                }
            }
            return result;
        }

        [[nodiscard]] std::optional<Matrix> mul(const Matrix& matrix, const bool broadcasting = false) const {

            if (storage[0].size() != matrix.storage.size())
                return std::nullopt;

            const auto rows = storage.size();
            const auto cols = matrix.storage[0].size();

            Matrix result {std::vector(rows, std::vector(cols, 0.f))};

            for (size_t i = 0; i < rows; ++i) {
                for (size_t j = 0; j < cols; ++j) {
                    for (size_t k = 0; k < storage[0].size(); ++k) {
                        result.storage[i][j] += this->storage[i][k] * matrix.storage[k][j];
                    }
                    if (core::abs(result.storage[i][j]) < 1e-6f) result.storage[i][j] = 0.f;
                }

            }

            return result;
        }

        [[nodiscard]] Matrix scalar_mul(const float scalar) const {
            const auto rows = storage.size();
            const auto cols = storage[0].size();

            Matrix result { std::vector(rows, std::vector(cols, 0.f))};
            for (int i = 0; i < storage.size(); ++i) {
                for (int j = 0; j < storage[i].size(); ++j) {
                    result.storage[i][j] = scalar * storage[i][j];
                }
            }
            return result;
        }

        [[nodiscard]] Matrix scalar_div(const float scalar) const {
            const auto rows = storage.size();
            const auto cols = storage[0].size();

            Matrix result { std::vector(rows, std::vector(cols, 0.f))};
            for (int i = 0; i < storage.size(); ++i) {
                for (int j = 0; j < storage[i].size(); ++j) {
                    result.storage[i][j] = scalar / storage[i][j];
                }
            }
            return result;
        }

        [[nodiscard]] std::optional<Matrix> element_wise_gt(const Matrix& m) const {

            if (storage.size() != m.storage.size())
                return std::nullopt;

            const auto rows = m.storage.size();
            const auto cols = m.storage[0].size();

            Matrix result {std::vector(rows, std::vector(cols, 0.f))};

            for (size_t i = 0; i < m.storage.size(); ++i) {
                for (size_t j = 0; j < m.storage[i].size(); ++j) {
                    if (storage[i][j] > m.storage[i][j])
                        result.storage[i][j] = 1;
                    else
                        result.storage[i][j] = 0;
                }
            }

            return result;
        }

        [[nodiscard]] std::optional<Matrix> element_wise_lt(const Matrix& m) const {

            if (storage.size() != m.storage.size())
                return std::nullopt;

            const auto rows = m.storage.size();
            const auto cols = m.storage[0].size();

            Matrix result {std::vector(rows, std::vector(cols, 0.f))};

            for (size_t i = 0; i < m.storage.size(); ++i) {
                for (size_t j = 0; j < m.storage[i].size(); ++j) {
                    if (storage[i][j] < m.storage[i][j])
                        result.storage[i][j] = 1;
                    else
                        result.storage[i][j] = 0;
                }
            }

            return result;
        }


        Matrix norm() {

        }

        [[nodiscard]] Matrix transpose() const {
            const auto rows = storage.size();
            const auto cols = storage[0].size();

            Matrix result { std::vector(cols, std::vector(rows, 0.f))};
            for (int i = 0; i < cols; ++i) {
                for (int j = 0; j < rows; ++j) {
                    result.storage[i][j] = storage[j][i];
                }
            }
            return result;
        }

        static Matrix augment(const Matrix& m1, const Matrix& m2) {

            if (m1.storage.size() != m2.storage.size()) {
                throw std::invalid_argument("Matrix sub matrix must be same row dimensionality");
            }

            const auto rows = m1.storage.size();
            const auto cols = m1.storage[0].size() + m2.storage[0].size();

            Matrix aug_m {std::vector<std::vector<float>>(rows, std::vector<float>(cols, 0.f))};

            for (size_t i = 0; i < aug_m.storage.size(); ++i) {
                for (size_t j = 0; j < aug_m.storage[i].size(); ++j) {
                    if (j < m1.storage[0].size())
                        aug_m.storage[i][j] = m1.storage[i][j];
                    else
                        aug_m.storage[i][j] = m2.storage[i][j - m1.storage[0].size()];
                }
            }

            return aug_m;
        }

        static void swap_rows(std::vector<std::vector<float>>& matrix, const size_t row_a, const size_t row_b) {
            std::swap(matrix[row_a], matrix[row_b]);
        }

        static std::optional<Matrix> gaussian_elimination(const Matrix &matrix, int* swaps = nullptr) {
            float pivot{0.f};
            float factor{0.f};

            const auto cols = matrix.storage[0].size();
            float sign{1};

            auto cp = matrix;

            for (int i = 0; i < matrix.storage.size() ; i++) {
                pivot = cp.storage[i][i];

                if (pivot == 0) {
                    int c{1};
                    while (pivot == 0 ) {
                        if (i+c >= cols)
                            return std::nullopt;
                        swap_rows(cp.storage, i, i+c);
                        sign = -sign;
                        if (swaps) (*swaps)++;
                        pivot = cp.storage[i][i];
                        c++;
                    }
                }

                for (int j=1+i; j < matrix.storage.size(); j++) {
                    factor = cp.storage[j][i]/pivot;
                    for (int k = 0; k < cols; k++) {
                        cp.storage[j][k] -= factor * cp.storage[i][k];
                    }
                }
            }
            return cp;
        }

        static std::optional<Matrix> gauss_jordan(const Matrix& matrix) {

            auto result = gaussian_elimination(matrix).value();

            float pivot{0.f};
            float factor{0.f};

            const auto cols = matrix.storage[0].size();

            for (size_t i = result.storage.size()-1 ; i > 0 ; i--) {
                pivot = result.storage[i][i];
                for (size_t j=0; j < i; j++) {
                    factor = result.storage[j][i]/pivot;
                    for (int k = 0; k < cols; k++) {
                        result.storage[j][k] -= factor * result.storage[i][k];
                        if (core::abs(result.storage[j][k]) < 1e-7f) result.storage[j][k] = 0.f;
                    }
                }
            }

            for (int i = 0; i < result.storage.size(); ++i) {
                pivot = result.storage[i][i];
                for (int j = 0; j < result.storage[i].size(); ++j) {
                    result.storage[i][j] /= pivot;
                }
            }

            return result;
        }

        [[nodiscard]] float determinant() const {
            float determinant{1.0f};
            float sign{1};

            const auto cols = this->storage[0].size();
            int swaps{0};
            const auto result = gaussian_elimination(*this, &swaps);

            if (swaps % 2 == 1) {
                sign = -1;
            }


            if (!result) return 0.f;

            for (int i = 0; i < cols; ++i) {
                determinant *= result->storage[i][i];
            }

            return (sign)*determinant;

        }

        [[nodiscard]] bool is_square() const {
            return storage.size() == storage[0].size();
        }

        static Matrix getIdentityMatrix(const size_t order=3) {

            Matrix identity {std::vector(order, std::vector(order, 0.f))};

            for (int i = 0; i < order; ++i) {
                identity.storage[i][i] = 1;
            }

            return identity;
        }

        [[nodiscard]] Matrix inverse() const {

            const auto cols = this->storage[0].size();
            const auto rows = this->storage.size();

            Matrix result { std::vector(rows, std::vector(cols, 0.f))};
            if (!is_square()) throw std::invalid_argument("Matrix inverse is not square");

            if (determinant() == 0 ) throw std::invalid_argument("determinant is not zero");

            Matrix unified_m = augment(*this, getIdentityMatrix(this->storage.size()));
            unified_m = gauss_jordan(unified_m).value();

            for (size_t i = 0; i < unified_m.storage.size(); ++i) {
                for (size_t j = this->storage.size() ; j < unified_m.storage[i].size(); ++j) {
                    result.storage[i][j-this->storage.size()] = unified_m.storage[i][j];
                }
            }

            return result;

        }


    };

}

#endif //IAHOMEWORK_MATRIX_H