//
// Created by tdela on 18/4/2026.
//

#ifndef IAHOMEWORK_MATRIX_H
#define IAHOMEWORK_MATRIX_H
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

        void print() const {
            std::cout << '[' << ' ';
            for (size_t i = 0; i < storage.size(); ++i) {
                std::cout << '\n' << std::setw(4) <<  "{ ";
                for (size_t j = 0; j < storage[0].size(); ++j) {
                    if (j == storage[0].size()-1 ) std::cout << std::setw(4) << storage[i][j];
                    else std::cout <<  std::setw(4) << storage[i][j] << ", ";
                }
                if (i == storage.size()-1) std::cout << " } ";
                else std::cout << " }, ";
            }
            std::cout << '\n' << ']' << std::endl;
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

        Matrix normalize() {

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

        void swap_rows(const int current_row, const int swap_row) {
                std::swap(storage[current_row], storage[swap_row]);
        }

        float determinant() {

            float determinant{1.0f};

            float pivot{0.f};
            float factor{0.f};

            const auto cols = storage[0].size();
            float sign{1};

            for (int i = 0; i < cols; i++) {
                pivot = storage[i][i];

                if (pivot == 0) {
                    int c{1};
                    while (pivot == 0 ) {
                        if (i+c >= cols)
                            return 0.f;
                        swap_rows(i, i+c);
                        sign = -sign;
                        pivot = storage[i][i];
                        c++;
                    }
                }

                for (int j=1+i; j < cols; j++) {
                    factor = storage[j][i]/pivot;
                    for (int k = 0; k < cols; k++) {
                        storage[j][k] -= factor * storage[i][k];
                    }
                }
            }

            for (int i = 0; i < cols; ++i) {
                determinant *= storage[i][i];
            }

            return (sign)*determinant;

        }

        [[nodiscard]] bool is_square() const {
            return storage.size() == storage[0].size();
        }

        Matrix inverse() {

            if (!is_square()) throw std::invalid_argument("Matrix inverse is not square");

        }


    };

}

#endif //IAHOMEWORK_MATRIX_H