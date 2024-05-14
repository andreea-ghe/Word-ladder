#include "automatic_simulation.h"
#include "graph.h"
#include "dictionary.h"

void autoPlay() {
    std::cout << "What's the initial word?\n";
    std::string startWord;
    std::cin >> startWord;

    std::cout << "What's the word you want to reach?\n";
    std::string endWord;
    std::cin >> endWord;

    if (startWord.size() != endWord.size())
        throw std::runtime_error("The words must have the same dimension!\n");

    // creating the graph
    std::vector<std::string> vertices;
    std::map<std::string, std::vector<std::string>> adjacencyList;
    Graph<std::string> g(vertices, adjacencyList);

    // creating the dictionary
    std::map<std::string, std::vector<std::string>> dict;
    Dictionary dictionary(dict);
    // based on the number of letters we know what file to choose
    dictionary.createDictionary("../dicts/" + std::to_string(startWord.size()) + ".txt");

    // initializing the graph
    dictionary.createGraph(g);

    std::vector<std::string> path;
    g.findShortestPathBFS(startWord, endWord, path);

    if (path.empty())
        throw std::runtime_error("We can't find a path!\n");
    else {
        for (auto aux: path)
            std::cout << aux << ' ';
    }
    std::cout << '\n';
}