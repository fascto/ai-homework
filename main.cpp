

#include <cmath>
#include <iostream>
#include <ostream>
#include "./include/graph.h"
#include "include/math/math_test.h"
#include "include/math/math.h"
#include "include/math/linear_algebra/Matrix.h"
#include "include/math/linear_algebra/Vec.h"
#include "include/ml/activations.h"
#include "include/ml/Perceptron.h"

float sqrt(float x) {
    return x*x + 6*x - 16;
}


int main() {
    // std::cout << "ElPepe!" << std::endl;
    //
    // Graph<int> graph{true, false};
    //
    // graph.addVertex(0);
    // graph.addVertex(1);
    // graph.addVertex(2);
    // graph.addVertex(3);
    // graph.addVertex(4);
    // graph.addVertex(5);
    // graph.addVertex(6);
    //
    // graph.addEdge(0, 1, 12);
    // graph.addEdge(0, 2, 3);
    // graph.addEdge(1, 2, 5);
    // graph.addEdge(2, 4, 4);
    // graph.addEdge(3, 4, 6);
    // graph.addEdge(4, 6, 7);
    // graph.addEdge(5, 6, 8);
    // graph.addEdge(1, 5, 11);
    //
    // graph.printGraph();
    // std::cout << "DFS" << std::endl;
    // graph.dfs(6);
    //
    // std::cout << "BFS" << std::endl;
    // graph.bfs(6);
    //
    // std::cout << "Djikstra path searching" << std::endl;
    // auto path = graph.dijkstra(0, 6);
    // for (int n : path) std::cout << n << " -> ";
    // std::cout << "NULL" << std::endl;
    //
    // std::cout << "Djikstra distance searching" << std::endl;
    // auto distances = graph.dijkstra(0);
    // for (int d : distances) std::cout << d << " ";
    // std::cout << std::endl;
    //
    // auto mst = graph.prim(0);
    // for (auto& e : mst) {
    //     std::cout << e.from << " --" << e.weight << "-- " << e.to << "\n";
    // }

    std::cout << "Sin 1: " << math::core::sin(0) << std::endl;
    std::cout << "Sin pi/2: " << math::core::sin(math::constants::PI/2) << std::endl;
    std::cout << "Sin pi: " << math::core::sin(math::constants::PI) << std::endl;

    std::cout << "Cos 0: " << math::core::cos(0) << std::endl;
    std::cout << "Cos pi/2: " << math::core::cos(math::constants::PI/2) << std::endl;
    std::cout << "Cos pi: " << math::core::cos(math::constants::PI) << std::endl;

    std::cout << "sqrt(25): " << math::core::sqrt(25, 2) << std::endl;

    // Linear algebra
    // Vector
    const math::linear_algebra::Vec v{{2, 2}};
    v.print();
    std::cout << v.norm() << std::endl;
    const auto v_normalized = v.normalization();

    v_normalized.print();

    // Matrix
    math::linear_algebra::Matrix m1 {
                            {
                                {2.f,-1.f,3.f},
                                {1.f,2.f,1.f},
                                {3.f,1.f,2.f},
                                }
    };

    math::linear_algebra::Matrix m2 {
                            {
                                {1.f,1.f,1.f},
                                {2.f,2.f,2.f},
                                }
    };

    m1.print();

    m2.print();

    std::cout << std::endl;

    auto m4 = m2.transpose();

    m4.print();

    std::cout << std::endl;

    auto elpepe = m1.determinant();

    m1.print();

    std::cout << "Determinante de m1: " << elpepe << std::endl;

    auto m5 = math::linear_algebra::Matrix::augment(m1, m4);
    m5.print();



    auto iv = std::vector<math::linear_algebra::Matrix>(
    {
        math::linear_algebra::Matrix::getIdentityMatrix(1),
        math::linear_algebra::Matrix::getIdentityMatrix(3),
        math::linear_algebra::Matrix::getIdentityMatrix(2),
        math::linear_algebra::Matrix::getIdentityMatrix(5),
    }
);

    for ( const auto& i : iv) {
        i.print();
    }

    std::cout << "Matrix(m1): " << std::endl;
    m1.print();

    std::cout << "Inverse Matrix: " << std::endl;

    const auto m1_inv = m1.inverse();
    m1_inv.print();

    std::cout << "Verificacion(m1*m1^-1): " << std::endl;

    (m1_inv*m1).print();

    auto c1 = (m1_inv*m1);

    auto c2 = (m1_inv*m1)*10.f;

    auto re1 = c1.element_wise_gt(c2);

    if (!re1) throw std::logic_error("No son del mismo tamaño :v");

    re1->print();

    (m2.transpose()*m2).print();

    std::cout << std::endl;
    std::cout << "Exp: " << std::endl;

    std::cout << exp(-1) << std::endl;
    std::cout << exp(0) << std::endl;
    std::cout << exp(1) << std::endl;

    std::cout << ml::activations::sigmoid(1) << std::endl;
    std::cout << ml::activations::sigmoid(0) << std::endl;
    std::cout << ml::activations::sigmoid(-1) << std::endl;

    math::linear_algebra::Matrix X {
        {
            {0.f, 0.f, 1.f, 1.f},
            {0.f, 1.f, 0.f, 1.f}
        }
    };

    std::vector<float> y {0.f, 0.f, 0.f, 1.f};

    Perceptron p {X, y, ml::activations::ActivationFunction::STEP, 0.f, 100};
    p.train();

    for (auto vp = p.predict(X).value(); const auto& i : vp) {
        std::cout << i << std::endl;
    }
}
