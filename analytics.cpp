#include "analytics.h"
#include <set>

std::vector<std::string> loadData(std::string path) {
    std::ifstream myFile(path);

    std::vector<std::string>usedWords;
    std::string line;
    while(std::getline(myFile, line)) {
        int i = 0;
        int cntColumn = 0;
        std::string aux;

        while (i < line.size()) {

            if (line[i] != ';')
                aux += line[i];
            else {

                cntColumn ++;
                if (cntColumn == 1)
                    std::cout << "Starting word: " << aux << '\n';
                else if (cntColumn == 2)
                    std::cout << "Ending word: " << aux << '\n';
                else if (cntColumn == 3)
                    std::cout << "Time: " << aux << '\n';
                else if (cntColumn == 4)
                    std::cout << "Number of hints: " << aux << '\n';
                else if (cntColumn == 5){
                    std::cout << "Words used: ";
                    std::string smallAux = "";
                    int j = 0;
                    while (j < aux.size()) {
                        if (aux[j] != ',')
                            smallAux += aux[j];
                        else {
                            std::cout << smallAux << ' ';
                            usedWords.push_back(smallAux);
                            smallAux = "";
                        }
                        j ++;
                    }
                    std::cout << '\n';
                    std::cout << "Number of moves: " << smallAux << '\n';
                    i++;
                    std::string numberMoves;
                    while (i < line.size()) {
                        numberMoves += line[i];
                        i++;
                    }
                    std::cout << "Number of optimal steps: " << numberMoves << "\n\n";
                }
                aux = "";
            }

            i ++;
        }
    }
    return usedWords;
    myFile.close();
};

int numberUniqueWords(std::vector<std::string>usedWords) {
    std::set<std::string>uniqueWords;
    for (auto word: usedWords)
        uniqueWords.insert(word);

    return uniqueWords.size();
}