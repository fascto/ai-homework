

#include <iostream>
#include <ostream>
#include "./include/graph.h"
#include "include/math/math_test.h"
#include "include/math/math.h"
#include "include/math/linear_algebra/Vec.h"

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
    std::cout << "Sin pi/2" << math::core::sin(math::constants::PI/2) << std::endl;
    std::cout << "Sin pi" << math::core::sin(math::constants::PI) << std::endl;

    std::cout << "Cos 1: " << math::core::cos(0) << std::endl;
    std::cout << "Cos pi/2: " << math::core::cos(math::constants::PI/2) << std::endl;
    std::cout << "Cos pi: " << math::core::cos(math::constants::PI) << std::endl;

    std::cout << "sqrt(25): " << math::core::sqrt(25, 2) << std::endl;

    // Linear alg
    const math::linear_algebra::Vec v{{2, 2}};
    v.print();
    std::cout << v.norm() << std::endl;
    const auto v_normalized = v.normalization();

    v_normalized.print();

}
