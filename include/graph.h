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

    struct Vertex {
        T data;
        int weight;
        bool visited;

        explicit Vertex(T data, int weight);
    };

    struct Edge {
        Direction dir;
        int from;
        int to;
        int weight;

        explicit Edge(Direction dir, Vertex from, Vertex to);
    };

    std::vector<std::vector<int>> adjacencyMatrix;

    std::vector<Edge> edges;
    std::vector<Vertex> vertices;

    std::vector<bool> visited = {false};

    std::size_t vertexCount {0};
    std::size_t edgeCount {0};
    bool weighted {false};
    bool directed {false};

public:

    Graph();

    void addVertex(T data);
    void addEdge(int from, int to, int weight = 1);
    void bfs(int startIndex);
    void dfs(int startIndex);

    void printGraph();
};

#endif //IAHOMEWORK_GRAPH_H