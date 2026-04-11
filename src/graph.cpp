//
// Created by tdela on 7/4/2026.
//

#include "../include/graph.h"


template<typename T>
Graph<T>::Graph(const bool weighted, const bool directed): weighted(weighted), directed(directed) { }

template<typename T>
void Graph<T>::addVertex(T data) {

    adjList.resize(adjList.size() + 1);
    visited.resize(adjList.size(), false);

    vertices.push_back(data);
}

template<typename T>
void Graph<T>::addEdge(int from, int to, int weight) {

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


    template<typename T>
    void Graph<T>::printGraph() {

    }

    template<typename T>
    void Graph<T>::bfs(int startIndex) {

    }

    template<typename T>
    void Graph<T>::dfs() {

}