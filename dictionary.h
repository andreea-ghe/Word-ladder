#pragma once
#include <string>
#include <vector>
#include <map>
#include "graph.h"
#include <fstream>
using std::ostream;
#include <iostream>

class Dictionary {
private:
    std::map<std::string, std::vector<std::string>>dictionary;
public:
    Dictionary(std::map<std::string, std::vector<std::string>>_dictionary): dictionary{_dictionary} {};
    std::map<std::string, std::vector<std::string>> getDictionary() const { return dictionary; };

    void createDictionary(std::string filePath);

    template <typename T>
    void createGraph(Graph<T>& graph) {
        for (auto wildcard: dictionary) {
            auto auxKeys = wildcard.second;
            if (auxKeys.size() > 1) {
                // if we have more than one element we can connect

                for (int i = 0; i < auxKeys.size(); i ++) {
                    if (graph.checkVertex(auxKeys[i]) == false)
                        graph.addVertex(auxKeys[i]);
                    for (int j = i + 1; j < auxKeys.size(); j++) {
                        if (graph.checkVertex(auxKeys[j]) == false)
                            graph.addVertex(auxKeys[j]);
                        graph.addEdge(auxKeys[i], auxKeys[j]);
                    }
                }
            }
        }
    }

    friend ostream& operator<<(ostream& os, const Dictionary& _dictionary);
    ~Dictionary() = default;
};