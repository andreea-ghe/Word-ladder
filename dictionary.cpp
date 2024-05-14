#include "dictionary.h"
#include <fstream>
#include <iostream>

void Dictionary::createDictionary(std::string filePath) {
    std::ifstream file(filePath);
    if (!file.is_open())
        throw std::runtime_error("couldn't open the file!\n");

    std::string line;
    while(getline(file, line)) {
        for (int i = 0; i < line.size(); i ++) {
            std::string aux = line;
            aux[i] = '*';
            dictionary[aux].push_back(line); // we add for each wildcard the corresponding word
        }
    }
}

ostream& operator<<(ostream& os, const Dictionary& _dictionary) {
    for (auto key: _dictionary.getDictionary()) {
        os << key.first << ": ";
        for (auto words: key.second)
            os << words << ' ';
        os << '\n';
    }
    return os;
}