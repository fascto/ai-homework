//
// Created by tdela on 7/4/2026.
//

#ifndef IAHOMEWORK_GRAPH_H
#define IAHOMEWORK_GRAPH_H
#include <vector>

enum class Direction {
    IN,
    OUT,
    BOTH
};

template<typename T>
class Graph {

    struct Edge {
        int from;
        int to;
        int weight;
    };

    std::vector<T> vertices;
    std::vector<std::vector<Edge>> adjList;
    std::vector<bool> visited;

    bool weighted {false};
    bool directed {false};

public:
    Graph(bool weighted = false, bool directed = false);

    void addVertex(T data);
    void addEdge(int from, int to, int weight = 1);
    void bfs(int startIndex);
    void dfs();
    void printGraph();
};
#endif //IAHOMEWORK_GRAPH_H