//
// Created by tdela on 7/4/2026.
//

#ifndef IAHOMEWORK_GRAPH_H
#define IAHOMEWORK_GRAPH_H
#include <algorithm>
#include <cstring>
#include <vector>
#include <iostream>
#include <queue>
#include <limits>

constexpr long long INF = std::numeric_limits<int>::max();

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

        visited[index] = true;

        std::cout << index << " -> ";

        for (auto& e : adjList[index]) {
            if (!visited[e.to]) {
                dfsRec(e.to);
            }
        }
    }

    std::vector<int> dijkstraUtil(int source, int goal=-1) {
        using PQ = std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>>;

        std::vector<int> dist;
        dist.resize(vertices.size(), INF);

        if (adjList.empty()) return dist;

        dist[source] = 0;
        std::vector<int> prev;
        prev.resize(vertices.size(), -1);

        PQ pq;

        pq.push(std::make_pair( dist[source], source));

        while (!pq.empty()) {

            const std::pair<int, int> temp = pq.top();
            pq.pop();

            for (Edge& e : adjList[temp.second]) {

                if (dist[temp.second] + e.weight < dist[e.to]) {
                    prev[e.to] = temp.second;
                    dist[e.to] = dist[temp.second] + e.weight;
                    pq.push(std::make_pair(dist[e.to] , e.to));
                }
            }
        }

        if (goal != -1 ) {
            std::vector<int> result;

            int current = goal;
            while (current != -1) {
                result.push_back(current);
                current = prev[current];
            }

            std::reverse(result.begin(), result.end());
            return result;
        } else {
            return dist;
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
        std::cout << "NULL" << std::endl;
        std::fill(visited.begin(), visited.end(), false);
    }

    void dfs(int index) {
        if (adjList[index].size() == 0 || adjList[index].empty()) return;

        dfsRec(index);

        std::fill(visited.begin(), visited.end(), false);
        std::cout << "NULL" << std::endl;

    }

    std::vector<int> dijkstra(int start) {
        return dijkstraUtil(start);
    }

    std::vector<int> dijkstra(int start, int goal) {
        return dijkstraUtil(start, goal);
    }


};
#endif //IAHOMEWORK_GRAPH_H