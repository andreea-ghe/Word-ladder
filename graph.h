#pragma once
#include <map>
#include <vector>
#include <algorithm>

#include <fstream>
using std::ostream;

#include <queue>
#include <cstdlib>
#include <iostream>

template <typename T>

class Graph {
private:
    std::vector<T>vertices;
    std::map<T, std::vector<T>>adjacencyList;
    std::map<T, int>indexVertex;
public:
    Graph() = default;
    Graph(std::vector<T> _vertices, std::map<T, std::vector<T>>_adjacencyList): vertices{_vertices}, adjacencyList{_adjacencyList} {};

    void addVertex(const T& vertex) {
        // find returns iterator to the first position vertex is found
        // vertices.end = next position to the last element, not last position of the sequence
        if (std::find(vertices.begin(), vertices.end(), vertex) != vertices.end())
            throw std::runtime_error("word already exists!\n");

        // add the vertex to the list of vertices
        vertices.push_back(vertex);
        // this is like a conversion from T to int
        indexVertex[vertex] = vertices.size() - 1;
    };

    bool checkVertex(const T& vertex) {
        if (std::find(vertices.begin(), vertices.end(), vertex) != vertices.end())
            return true;
        return false;
    }

    void addEdge(const T& startVertex, const T& endVertex) {
        if (std::find(vertices.begin(), vertices.end(), startVertex) == vertices.end())
            throw std::runtime_error("starting word doesn't exist!\n");
        if(std::find(vertices.begin(), vertices.end(), endVertex) == vertices.end())
            throw std::runtime_error("ending word doesn't exist!\n");

        // add the edge for the unidirected graph
        adjacencyList[startVertex].push_back(endVertex);
        adjacencyList[endVertex].push_back(startVertex);
    };

    std::vector<T> getNeighbors(const T& vertex) const {
        if (std::find(vertices.begin(), vertices.end(), vertex) == vertices.end())
            throw std::runtime_error("word doesn't exist!\n");

        // return the neighbors (adjacency list) of vertex
        return adjacencyList.at(vertex);
    };

    friend ostream& operator<<(ostream& os, const Graph<T>& graph) {
        os << "the vertices are: ";
        for (auto& nodes: graph.vertices)
            os << nodes << ' ';
        os << '\n';
        os << "the edges are:\n";
        for (auto& nodes: graph.vertices) {
            os << nodes << ": ";
            auto aux = graph.getNeighbors(nodes);
            for (auto& neighbors: aux)
                os << neighbors << ' ';
            os << '\n';
        }
        return os;
    };

    void findShortestPathBFS(const T& startVertex, const T& endVertex, std::vector<T>& path) {
        if (std::find(vertices.begin(), vertices.end(), startVertex) == vertices.end())
            throw std::runtime_error("starting word doesn't exist!\n");
        if(std::find(vertices.begin(), vertices.end(), endVertex) == vertices.end())
            throw std::runtime_error("ending word doesn't exist!\n");

        std::vector<bool>visited(vertices.size(), false);
        std::vector<int>parent(vertices.size());
        std::queue<T>bfsQueue;

        visited[indexVertex[startVertex]] = true;
        parent[indexVertex[startVertex]] = -1;
        bfsQueue.push(startVertex);

        bool found = false;
        while(!bfsQueue.empty() && !found) {
            T currentNode = bfsQueue.front();
            bfsQueue.pop();

            for (auto& neighbor: this->getNeighbors(currentNode))
                if (!visited[indexVertex[neighbor]]) {
                    visited[indexVertex[neighbor]] = true;
                    parent[indexVertex[neighbor]] = indexVertex[currentNode];
                    bfsQueue.push(neighbor);
                    if (neighbor == endVertex) {
                        found = true;
                    }
                }
        }
        if (found == true) {
            int current = indexVertex[endVertex];
            while(current != -1) {
                path.push_back(vertices[current]);
                current = parent[current];
            }
            std::reverse(path.begin(), path.end());
        }
    };

    std::pair<std::string, std::string> generateRandomWords() {
        srand(time(nullptr));
        int firstRandom = rand() % vertices.size();
        int secondRandom = rand() % vertices.size();
        return std::make_pair(vertices[firstRandom], vertices[secondRandom]);
    }

    bool checkWord(const T& word) {
        if (std::find(vertices.begin(), vertices.end(), word) != vertices.end())
            return true;
        return false;
    }

    ~Graph() = default;
};
