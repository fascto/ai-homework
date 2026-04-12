//
// Created by tdela on 7/4/2026.
//

#ifndef IAHOMEWORK_GRAPH_H
#define IAHOMEWORK_GRAPH_H
#include <cstring>
#include <vector>
#include <iostream>
#include <queue>

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

    void dfsRec(int index) {

        // Revisar si tiene vecinos
        // Si tiene entrar Iterar con un for y en cada uno llamar a la funcion

        visited[index] = true;

        std::cout << index << " -> ";

        for (auto& e : adjList[index]) {
            if (!visited[e.to]) {
                dfsRec(e.to);
            }
        }
    }


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


    void bfs(int startIndex) {

        if (adjList[startIndex].size() == 0 || adjList.empty()) return;

        std::queue<int> q;
        q.push(startIndex);
        visited[startIndex] = true;

        while (!q.empty()) {

            int temp = q.front();
            q.pop();
            std::cout << temp << " -> ";

                for (auto& e : adjList[temp]) {
                    if (!visited[e.to]) {
                        q.push(e.to);
                        visited[e.to] = true;
                    }
                }
        }
        std::cout << "NULL";
        std::fill(visited.begin(), visited.end(), false);
    }

    void dfs(int index) {
        if (adjList[index].size() == 0 || adjList[index].empty()) return;

        dfsRec(index);

        std::fill(visited.begin(), visited.end(), false);
        std::cout << index << " -> NULL";

    }

};
#endif //IAHOMEWORK_GRAPH_H