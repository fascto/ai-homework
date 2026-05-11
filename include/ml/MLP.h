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
        const auto num_features = m_feature_matrix.getCols();

        m_weights.resize(num_features, math::linear_algebra::Matrix{});

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution dis(0.f, 1.f);

        // Input (n_feature x m_npl)
        m_weights[0] = math::linear_algebra::Matrix{ num_features, m_npl };

        // Output (1 x m_npl)
        m_weights[num_features] = math::linear_algebra::Matrix{ 1, m_npl};

        // loop for hidden layers
        for (int j = 0; j < m_layers; ++j) {
            if (m_hidden_layers[j]) {
                m_weights[j+1] = math::linear_algebra::Matrix{ m_hidden_layers[j], m_npl };
            } else
                m_weights[j+1] = math::linear_algebra::Matrix{ m_npl, m_npl };
        }

        // Init weights
        for (auto& m : m_weights) {
            for (int i = 0; i < m.getRows(); ++i) {
                for (int j = 0; j < m.getCols(); ++j) {
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
            const auto gradients = backpropagation(m_loss_function,m_labels);

            const auto updated_weights = math::calculus::gradient_descent(m_weights, gradients, m_learning_rate);
            m_weights = updated_weights;
        }
    }

    math::linear_algebra::Matrix forward(const int sample_idx) {

        auto current_input = math::linear_algebra::Matrix{m_feature_matrix.getCol(sample_idx)};

        for (auto m : m_weights) {
            m = m.mul(current_input).value();
            for (int j = 0; j < m.getRows(); ++j) {
                for (int k = 0; k < m.getCols(); ++k) {
                    m.set(j, k, ml::activations::apply(m_activation_function, m.get(j, k)));
                }
            }
            current_input = m;
        }
        return current_input;
    }

    [[nodiscard]] std::vector<float> backpropagation(
        ml::metrics::LossFunction const loss_function,
        std::vector<float> y_real
        ) const {

        auto weights = this->m_weights;
        auto x = this->m_feature_matrix;

        std::vector<float> gradients{};
        std::vector<float> avg_gradients{};

        avg_gradients.resize(weights.size(), 0.f);

        // Run gradient descent
        for (int s = 0; s < y_real.size(); s++) {

            for (int j = 0; j < weights.size(); j++) {
                auto loss = [&x, &y_real, &weights, loss_function, j, s, this](const float w_j) {
                    float z{0.0f};
                    for (int k = 0; k < weights.size(); k++) {
                        float w_k;
                        if (k == j)
                            w_k = w_j;
                        else
                            w_k = weights[k];

                        z += w_k * x.get(k, s);
                    }
                    const float y_pred = ml::activations::apply(m_activation_function, z);
                    return ml::metrics::apply(loss_function, std::vector<float>{y_pred}, std::vector<float>{y_real[s]});
                };
                const auto gradient = math::calculus::evaluate(math::types::function { .func = loss , .order = 1 }, weights[j]);
                gradients.push_back(gradient);
                avg_gradients[j] += gradient/static_cast<float>(y_real.size());
            }
        }
        return avg_gradients;
    }

};

#endif //IAHOMEWORK_MLP_H