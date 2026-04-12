

#include <iostream>
#include <ostream>
#include "./include/graph.h"

int main() {

    std::cout << "ElPepe!" << std::endl;

    Graph<int> graph{true, false};

    graph.addVertex(0);
    graph.addVertex(1);
    graph.addVertex(2);
    graph.addVertex(3);
    graph.addVertex(4);
    graph.addVertex(5);
    graph.addVertex(6);

    graph.addEdge(0, 1, 12);
    graph.addEdge(0, 2, 3);
    graph.addEdge(1, 2, 5);
    graph.addEdge(2, 4, 4);
    graph.addEdge(3, 4, 6);
    graph.addEdge(4, 6, 7);
    graph.addEdge(5, 6, 8);
    graph.addEdge(1, 5, 11);

    graph.printGraph();
    std::cout << "DFS" << std::endl;
    graph.dfs(6);

    std::cout << "BFS" << std::endl;
    graph.bfs(6);
}
