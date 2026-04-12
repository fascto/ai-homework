//
// Created by tdela on 7/4/2026.
//

#ifndef IAHOMEWORK_GRAPH_H
#define IAHOMEWORK_GRAPH_H
#include <vector>
#include <iostream>

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

    Graph(const bool weighted, const bool directed): weighted(weighted), directed(directed) { }

    void addVertex(T data){

        adjList.resize(adjList.size() + 1);
        visited.resize(adjList.size(), false);

        vertices.push_back(data);
    }



    void addEdge(int from, int to, int weight = 1) {

        if (!(from < adjList.size() && to < adjList.size())) return;

        Edge e;

        if (weighted) e.weight = weight;

        e.from = from;
        e.to = to;

        adjList[from].push_back(e);

        if (!directed) {
            Edge d;

            if (weighted) d.weight = weight;

            d.from = to;
            d.to = from;
            adjList[to].push_back(d);
        }

    }
  void printGraph() {
        for (size_t i = 0; i < vertices.size(); i++) {

            std::cout << "+ - - +" << '\n';
            std::cout << '|' << "  " << vertices[i] << "  " << '|' << " -> ";

            std::cout << "[ ";
            for (auto& e : adjList[i]) {
                std::cout << e.to;
                if (weighted) std::cout << "(w:" << e.weight << ')';
                std::cout << ',' << ' ' ;
            }
            std::cout << " ]" << std::endl;
        }

        std::cout << "+ - - +" << '\n';

    }


    void bfs(int startIndex);

    void dfs();

};
#endif //IAHOMEWORK_GRAPH_H