

#include <iostream>
#include <ostream>
#include "./include/graph.h"

int main() {

    std::cout << "ElPepe!" << std::endl;

    Graph<int> graph{true, false};

    graph.addVertex(0);
    graph.addVertex(1);
    graph.addVertex(2);

    graph.addEdge(0, 1, 12);
    graph.addEdge(0, 2, 3);
    graph.addEdge(1, 2, 5);

    graph.printGraph();

}
