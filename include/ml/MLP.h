//
// Created by tdela on 23/4/2026.
//

#ifndef IAHOMEWORK_MLP_H
#define IAHOMEWORK_MLP_H
#include <random>
#include <vector>

#include "metrics.h"
#include "../math/calculus.h"
#include "../math/linear_algebra/Matrix.h"

class MLP {

    std::size_t m_layers{};
    std::vector<size_t> m_hidden_layers{};
    std::size_t m_npl{};

    math::linear_algebra::Matrix m_feature_matrix{};
    std::vector<math::linear_algebra::Matrix> m_weights{};
    ml::activations::ActivationFunction m_activation_function{};
    ml::metrics::LossFunction m_loss_function{};
    float m_learning_rate{};
    float m_bias{};

    std::vector<float> m_labels{};

    void initWeights() {
        const auto num_features = m_feature_matrix.getRows();

        m_weights.resize(m_layers+1, math::linear_algebra::Matrix{});

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution dis(0.f, 1.f);

        m_weights[0] = math::linear_algebra::Matrix{ m_npl, num_features };

        for (size_t j = 0; j < m_layers - 1; ++j) {
            if (j < m_hidden_layers.size() && m_hidden_layers[j]) {
                m_weights[j+1] = math::linear_algebra::Matrix{ m_hidden_layers[j], m_npl };
            } else {
                m_weights[j+1] = math::linear_algebra::Matrix{ m_npl, m_npl };
            }
        }

        m_weights[m_layers] = math::linear_algebra::Matrix{ 1, m_npl };

        for (auto& m : m_weights) {
            for (size_t i = 0; i < m.getRows(); ++i) {
                for (size_t j = 0; j < m.getCols(); ++j) {
                    m.set(i, j, dis(gen));
                }
            }
        }
    }


public:

    explicit MLP (
        const math::linear_algebra::Matrix& feature_matrix,
        const std::vector<float>& labels,
        const std::vector<size_t>& hidden_layers = std::vector<size_t>{},
        const std::size_t layers = 3,
        const std::size_t npl = 3,
        const float learning_rate = 0.1f,
        const float bias = 0.1f,
        const ml::activations::ActivationFunction activation_function = ml::activations::ActivationFunction::RELU,
        const ml::metrics::LossFunction loss_function = ml::metrics::LossFunction::MSE
        )
    : m_layers(layers), m_hidden_layers(hidden_layers), m_npl(npl), m_activation_function(activation_function), m_loss_function(loss_function), m_learning_rate(learning_rate), m_bias(bias), m_labels(labels) {

        m_learning_rate = learning_rate;
        m_feature_matrix = feature_matrix;
        m_labels = labels;

        initWeights();
    }

    void train(const int& epochs=100) {

        for (int i = 0; i < epochs; i++) {
            const auto gradients = backpropagation(m_loss_function, m_labels);

            const auto updated_weights = math::calculus::gradient_descent(m_weights, gradients, m_learning_rate);
            m_weights = updated_weights;
        }
    }

    [[nodiscard]] std::pair< std::vector<math::linear_algebra::Matrix>, std::vector<math::linear_algebra::Matrix> > forward(const int sample_idx, const std::vector<math::linear_algebra::Matrix>& weights) const {

        std::vector<math::linear_algebra::Matrix> z{};
        std::vector<math::linear_algebra::Matrix> z_activated{};

        auto current_input = math::linear_algebra::Matrix{m_feature_matrix.getCol(sample_idx)};

        for (auto m : weights) {
            m = m.mul(current_input).value();
            z.push_back(m);
            for (int j = 0; j < m.getRows(); ++j) {
                for (int k = 0; k < m.getCols(); ++k) {
                    m.set(j, k, ml::activations::apply(m_activation_function, m.get(j, k)));
                }
            }
            current_input = m;
            z_activated.push_back(current_input);
        }
        return {z, z_activated};
    }

    [[nodiscard]] std::vector<math::linear_algebra::Matrix> backpropagation(
        ml::metrics::LossFunction const loss_function,
        const std::vector<float> &y_real
    ) const {

        const auto weights = this->m_weights;

        std::vector<math::linear_algebra::Matrix> avg_gradients{};

        avg_gradients.resize(weights.size(), math::linear_algebra::Matrix{});

        auto compute_derivative = [this](const math::linear_algebra::Matrix& z) {
            math::linear_algebra::Matrix dz{z.getRows(), z.getCols()};
            for (size_t i = 0; i < z.getRows(); i++) {
                for (size_t j = 0; j < z.getCols(); ++j) {
                    math::types::function activation_fn;
                    activation_fn.func = [this](float x) {
                        return ml::activations::apply(m_activation_function, x);
                    };
                    activation_fn.order = 1;
                    dz.set(i, j, math::calculus::evaluate(activation_fn, z.get(i, j)));
                }
            }
            return dz;
        };

        auto accumulate = [&avg_gradients, &y_real](size_t idx, const math::linear_algebra::Matrix& gradient, int s) {
            auto scaled = gradient / static_cast<float>(y_real.size());
            if (s == 0)
                avg_gradients[idx] = scaled;
            else
                avg_gradients[idx] = avg_gradients[idx] + scaled;
        };

        for (int s = 0; s < (int)y_real.size(); s++) {

            auto [z_output, y_pred] = forward(s, weights);

            auto dz_out = compute_derivative(z_output.back());

            auto delta = (y_pred.back() - math::linear_algebra::Matrix(std::vector<float>{y_real[s]})).hadamard(dz_out);

            accumulate(m_layers, delta * y_pred[m_layers - 1].transpose(), s);

            for (int k = (int)m_layers - 1; k >= 0; k--) {
                auto dz_k = compute_derivative(z_output[k]);
                delta = (weights[k + 1].transpose() * delta).hadamard(dz_k);

                math::linear_algebra::Matrix prev_activation = (k == 0)
                    ? math::linear_algebra::Matrix{m_feature_matrix.getCol(s)}
                    : y_pred[k - 1];

                accumulate(k, delta * prev_activation.transpose(), s);
            }
        }
        return avg_gradients;
    }

    [[nodiscard]] float predict(const int sample_idx) const {
    }

    [[nodiscard]] std::optional<float> predict(const std::vector<float> &sample) const {
    }


    [[nodiscard]] std::optional<std::vector<float>> predict(const math::linear_algebra::Matrix &sample) const {
    }

};

#endif //IAHOMEWORK_MLP_H