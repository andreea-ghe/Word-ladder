#include "graph.h"
#include "dictionary.h"
#include "chrono"

void saveToCsv(std::string path, std::string firstWord, std::string secondWord, std::string time, int numberHints, std::vector<std::string>words, int numberMoves, int optimalSteps) {
    // open it in append mode
    std::ofstream myFile(path, std::ios::app);
    time.pop_back();
    myFile << firstWord << ';' << secondWord << ';' << time << ';' << numberHints << ';';
    for (auto word: words)
        myFile << word << ',';
    myFile << numberMoves << ';' << optimalSteps << std::endl;
    myFile.close();
}

void playGame() {
    std::cout << "What is your name? :)\n";
    std::string userName;
    std::cin >> userName;

    std::cout << "What's the number of letters for the words?\n";
    int nrLetters;
    std::cin >> nrLetters;

    std::vector<std::string> vertices;
    std::map<std::string, std::vector<std::string>> adjacencyList;
    Graph<std::string> g(vertices, adjacencyList);

    std::map<std::string, std::vector<std::string>> dict;
    Dictionary dictionary(dict);
    dictionary.createDictionary("dicts/" + std::to_string(nrLetters) + ".txt");

    dictionary.createGraph(g);

    std::vector<std::string>path;
    std::string firstRandomWord, secondRandomWord;
    while (path.empty()) {
        std::pair<std::string, std::string> p = g.generateRandomWords();
        g.findShortestPathBFS(p.first, p.second, path);
        firstRandomWord = p.first;
        secondRandomWord = p.second;
    }

    std::cout << "start from: " << firstRandomWord << " and get to: " << secondRandomWord << '\n';
    std::cout << "Good luck! :)\n";

    std::string aux = firstRandomWord;
    std::cout << "Write help! if you want a hint :)\n";

    std::vector<std::string>totalWords;
    totalWords.push_back(aux);
    std::vector<std::string>wordBucket;
    wordBucket.push_back(aux);
    int numberHints = 0;
    int numberMoves = 0;

    while (aux != secondRandomWord) {
        std::string userWord;
        std::cout << "next:";
        std::cin >> userWord;

        if (userWord == "help!") {
            numberHints ++;

            std::vector<std::string>vectorHint;
            g.findShortestPathBFS(wordBucket.back(), secondRandomWord, vectorHint);

            std::string wordHint = vectorHint.at(1);

            for (int i = 0; i < wordHint.size(); i ++) {
                if (wordBucket.back()[i] != wordHint[i])
                    std::cout << '(' << wordBucket.back()[i] << ')';
                else
                    std::cout << wordBucket.back()[i];
            }
            std::cout << '\n';
        }
        else if (userWord == "quit!") {
            std::cout << "You sure you want to quit? [y/n]";
            std::string option;
            std::cin >> option;
            std::transform(option.begin(), option.end(), option.begin(), tolower);
            if (option == "y" || option == "yes")
                break;
        }
        else
        if (g.checkWord(userWord)) {
            if (userWord.size() != aux.size())
                std::cout << "the words have to be of the same length!\n";
            else {
                int numberDiffLetters = 0;
                for (int i = 0; i < aux.size(); i ++)
                    if (userWord[i] != aux[i])
                        numberDiffLetters ++;

                if (numberDiffLetters != 1)
                    std::cout << "the words must differ by one letter\n";
                else {
                    aux = userWord;
                    wordBucket.push_back(userWord);
                }
            }
            totalWords.push_back(userWord);
        }
        else {
            totalWords.push_back(userWord);
            std::cout << "not a word!\n";
        }
        numberMoves ++;
    }
    std::cout << "Congratulations!:)\n";
    const auto now = std::chrono::system_clock::now();
    const std::time_t t_c = std::chrono::system_clock::to_time_t(now);

    if (aux == secondRandomWord)
        std::cout << "The word we started from: " << firstRandomWord << " and the word we reached: " << secondRandomWord << '\n';
    else
        std::cout << "The word we started from: " << firstRandomWord << " and the word we should have reached: " << secondRandomWord << '\n';
    std::cout << "Date and time of game: " << std::ctime(&t_c);
    std::cout << "Number of hints: " << numberHints << '\n';
    std::cout << "Words that were used: ";
    for (auto& word: totalWords)
        std::cout << word << ' ';
    std::cout << '\n';
    std::cout << "Total number of moves: " << numberMoves << '\n';

    std::vector<std::string>optimalSolution;
    g.findShortestPathBFS(firstRandomWord, secondRandomWord, optimalSolution);
    std::cout << "Best number of steps: " << optimalSolution.size() - 1 << '\n';
    std::cout << "Here is the optimal solution: ";
    for (auto& word: optimalSolution)
        std::cout << word << ' ';
    std::cout << '\n';

    saveToCsv(userName, firstRandomWord, secondRandomWord, std::ctime(&t_c), numberHints, totalWords, numberMoves, optimalSolution.size());
}