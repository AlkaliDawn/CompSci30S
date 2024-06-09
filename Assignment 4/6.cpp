#include <algorithm>
#include <iostream>
#include <conio.h>
#include <cmath>
#include <random>
#include <format>
#include <map>
#include "bartlett.h"

using namespace std;

const std::map<char, string_view> colors = {
        {'G', LIME}, // GREEN
        {'B', PASTEL_BLUE}, // BLUE
        {'Y', YELLOW}, // YELLOW
        {'O', ORANGE}, // ORANGE
        {'R', PINK}, // RED
        {'P', PURPLE} // PINK
};

/**
 * @brief A constant string that contains the valid letters for the game.
 *
 * This string contains the letters that represent the valid colors in the game. Each character in the string represents a color:
 * 'G' for Green, 'B' for Blue, 'Y' for Yellow, 'O' for Orange, 'R' for Red, and 'P' for Pink.
 */
constexpr string_view letters = "GBYORP";

/**
 * @brief This function generates a random solution for the game.
 *
 * The function clears the existing solution vector and then fills it with four random characters from the 'letters' string.
 * Each character represents a color in the game.
 *
 * @param solution A reference to a vector of characters that represents the solution.
 */
void makeSolution(vector<char> & solution);

/**
 * @brief This function gets the user's guess for the game.
 *
 * The function clears the existing guess vector and then populates it with four characters input by the user.
 * Each character represents a color in the game. The function also handles invalid inputs by ignoring them.
 *
 * @param guess A reference to a vector of characters that represents the user's guess.
 */
void getGuess(vector<char> & guess);

/**
 * @brief This function compares the user's guess with the solution.
 *
 * @behavior If a character in the guess vector is the same as the character in the solution vector at the same index, it increments the 'exact' counter and marks that character as checked.
 * If a character in the guess vector is found anywhere in the solution vector (but not at the same index), it increments the 'near' counter and marks that character as checked.
 * The function then prints the number of 'exact' and 'near' matches.
 *
 * @param guess A vector of characters that represents the user's guess for the game.
 * @param solution A vector of characters that represents the solution for the game.
 * @return A boolean value indicating whether the guess is exactly the same as the solution.
 */
bool compare(vector<char> guess, vector<char> solution);

int main() {
    
    seedRandom();
    
    vector<char> solution = {'O', 'O', 'R', 'B'};
    vector<char> guess = {};
    
    char input = 'y';
    
    int lowestRound = INT16_MAX;
    int losses = 0;
    int wins = 0;
    
    int round = 1;
    
//    makeSolution(solution);
    
    cout << "Possible Code Colours: " PASTEL_BLUE "(B)lue, " RESET LIME "(G)reen, " RESET YELLOW "(Y)ellow, " RESET PURPLE "(P)urple, " RESET ORANGE "(O)range, " RESET "or " PINK "(R)ed" RESET "\n";
    
    while (input == 'y') {
        cout << format("Enter Guess #{}: ", round);
        getGuess(guess);
        if (compare(guess, solution)) {
            lowestRound = std::min(round, lowestRound);
            ++wins;
            makeSolution(solution);
            round = 1;
            cout << "Do you want to play another round (Y/N)? ";
            input = get("yn");
            round = 1;
            continue;
        }
        else if (round == 10) {
            ++losses;
            cout << "YOU LOST - The Correct Answer was ";
            for (const auto & letter: solution) {
                cout << colors.at(letter) << letter << RESET;
            }
            makeSolution(solution);
            cout << "!!!!\nPlay Again? (Y/N) > ";
            input = get("yn");
            round = 1;
            continue;
        }
        ++round;
    }
    
    cout << format("You played {} game(s) - {} Win(s) and {} Loss(es) for a winning percentage of {}%!\nYour best score was getting it in {} guesses!\n",
                   wins + losses, wins, losses, std::round((static_cast<float>(wins) / (wins + losses)) * 100), lowestRound);
    
    cout << "Press any key to exit...";
    _getch();
    return 0;
}

void makeSolution(vector<char> & solution) {
    solution.clear();
    for (int i = 0; i < 4; ++i) {
        solution.push_back(letters.at(rand() % letters.size()));
    }
}

void getGuess(vector<char> & guess) {
    char input;
    guess.clear();
    for (int i = 0; i < 4;) {
        input = toupper(_getch());
        if (!letters.contains(input)) {
            continue;
        }
        cout << colors.at(input) << input << RESET;
        ++i;
        guess.push_back(input);
    }
}

bool compare(vector<char> guess, vector<char> solution) {
    int exact = 0;
    int near = 0;
    for (int i = 0; i < 4; ++i) {
        if (solution.at(i) == guess.at(i)) {
            ++exact;
            guess.at(i) = 0;
            solution.at(i) = -1;
            continue;
        }
        for (int j = 0; j < 4; ++j) {
            if (solution.at(i) == guess.at(j) && solution.at(j) != guess.at(j)) {
                ++near;
                guess.at(j) = 0;
                solution.at(i) = -1;
                true;
            }
        }
    }
    if (exact == 4){
        cout << "  ====> YOU WIN!!!!!\n";
    }
    else {
        cout << format("  ====> {} Exact, {} Wrong Place\n", exact, near);
    }
    return exact == 4;
}
