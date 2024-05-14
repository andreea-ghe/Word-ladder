#pragma once
#include <string>
#include "graph.h"
#include "dictionary.h"

std::vector<std::string> loadData(std::string path);

int numberUniqueWords(std::vector<std::string>usedWords);