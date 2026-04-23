//
// Created by tdela on 23/4/2026.
//

#ifndef IAHOMEWORK_PERCEPTRON_H
#define IAHOMEWORK_PERCEPTRON_H
#include <random>
#include <vector>

#include "activations.h"
#include "../math/linear_algebra.h"

class Perceptron {
    math::linear_algebra::Matrix m_feature_matrix{};
    std::vector<float> m_labels{};
    ml::activations::ActivationFunction m_activation{ml::activations::ActivationFunction::RELU};

    std::vector<float> m_weights{};

    float m_bias{};
    int m_epochs{1};
    float m_error{};
    float m_learning_rate{0.1f};

    void initWeights() {

        const auto cols = m_feature_matrix.getCols();

        m_weights.resize(cols, 0);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution dis(0.f, 1.f);

        for (int i = 0; i < cols; ++i) {
            m_weights[i] = dis(gen);
        }
    }

public:

    explicit Perceptron(
            const math::linear_algebra::Matrix& feature_matrix,
            const std::vector<float>& labels,
            const ml::activations::ActivationFunction activation=ml::activations::ActivationFunction::RELU,
            const float bias=0.f,
            const int epochs = 1,
            const float learning_rate=0.1f
        )
            : m_activation(activation), m_bias(bias), m_epochs(epochs), m_learning_rate(learning_rate)
    {

        m_feature_matrix = feature_matrix;
        m_labels = labels;

        initWeights();
    }

    [[nodiscard]] float weightedSum(const int sample_idx) const {
        float result{0.f};
        for (int i = 0; i < m_feature_matrix.getCols(); ++i) {
            result += m_weights[i] * m_feature_matrix.get(i, sample_idx) + m_bias;
        }
        return result;
    }

    [[nodiscard]] float apply(const float x) const {
        return ml::activations::apply(m_activation, x);
    }


    void train() {

        float result{0.f};
        float error = {0.f};

        for (int i = 0; i < m_epochs; ++i) {
            for (int j = 0; j < m_feature_matrix.getRows() ; ++j) {
                error = 0.f;
                result = apply(weightedSum(j));
                error += result - m_labels[j];
                for (int k = 0; k < m_weights.size(); ++k) {
                    m_weights[k] = m_weights[k] + m_learning_rate * error * m_feature_matrix.get(k, j);
                }
            }
        }
    }

    [[nodiscard]] float predict(const int sample_idx) const {
        return apply(weightedSum(sample_idx));
    }

    [[nodiscard]] std::optional<float> predict(const std::vector<float> &sample) const {

        if (sample.size() != m_feature_matrix.getRows())
            return std::nullopt;

        float result{};
        float sum{0.f};


        for (int i = 0; i < m_feature_matrix.getCols(); ++i) {
                sum += m_weights[i] * sample[i] + m_bias;
                result = (apply(sum));
        }

        return result;
    }


    [[nodiscard]] std::optional<std::vector<float>> predict(const math::linear_algebra::Matrix &sample) const {

        if (sample.getCols() != m_feature_matrix.getCols())
            return std::nullopt;

        std::vector<float> result{};
        float sum{0.f};

        for (int i = 0; i < sample.getCols(); ++i) {
            sum=0.f;
            for (int j = 0; j < sample.getRows(); ++j) {
                sum += sample.get(i, j) * m_weights[j];
            }
            result.push_back(apply(sum + m_bias));
        }

        return result;
    }
};

#endif //IAHOMEWORK_PERCEPTRON_H