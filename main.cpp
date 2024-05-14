#include <iostream>
#include <algorithm>
#include "game_simulation.h"
#include "automatic_simulation.h"
#include "analytics.h"

int main() {

    while (true) {
        try {
            std::cout << "Would you like to try the automatic mode to see some examples? [y/n]";

            std::string option1;
            std::cin >> option1;
            std::transform(option1.begin(), option1.end(), option1.begin(), tolower);

            if (option1 == "y" || option1 == "yes") {
                autoPlay();

            } else if (option1 == "n" || option1 == "no") {
                std::cout << '\n';
                std::cout << "Would you like to enter the game mode? :D [y/n]";

                std::string option2;
                std::cin >> option2;
                std::transform(option2.begin(), option2.end(), option2.begin(), tolower);

                if (option2 == "y" || option2 == "n" || option2 == "yes" || option2 == "no") {
                    if (option2 == "y" || option2 == "yes") {
                        playGame();

                    } else if (option2 == "n" || option2 == "no") {
                        std::cout << '\n';
                        std::cout << "Would you like to exit the game? [y/n]";

                        std::string option3;
                        std::cin >> option3;
                        std::transform(option3.begin(), option3.end(), option3.begin(), tolower);

                        if (option3 == "y" || option3 == "yes") {
                            std::cout << '\n';
                            std::cout << "Would you like to see the data about a certain user? [y/n]";

                            std::string option4;
                            std::cin >> option4;
                            std::transform(option4.begin(), option4.end(), option4.begin(), tolower);
                            if (option4 == "y" || option4 == "yes") {
                                std::cout << "What's the name of the user you would like to see?\n";
                                std::string userName;
                                std::cin>> userName;
                                auto usedWords = loadData(userName);

                                std::cout << "Number of unique words used: " << numberUniqueWords(usedWords) << "\n";
                            }
                            else {
                                std::cout << "Have a great day!";
                                break;
                            }
                        }

                    }
                }
            }
        }
        catch (std::runtime_error(e)){
            std::cout << e.what();
        }
    }

    return 0;
}
