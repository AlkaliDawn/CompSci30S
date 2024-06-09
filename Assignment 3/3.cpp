#include <algorithm>
#include <iostream>
#include <conio.h>
#include <random>
#include <format>
#include "bartlett.h"

/**
 * @brief <b> Maps characters 'A' to 1, 'B' to 2, ..., 'Z' to 26.
 */
#define ASCII_CONST 64

using namespace std;

/**
 * @brief Calculates the value of a string based on ASCII values.
 *
 * This function calculates the sum of the ASCII values of the characters in the string,
 * subtracting the ASCII value of 64 from each character's ASCII value.
 *
 * @param str A vector of characters representing the string.
 * @return The sum of the ASCII values of the characters in the string.
 */
int value(vector<char> str);

/**
 * @brief Prints a string.
 *
 * This function iterates over a vector of characters and prints each character.
 *
 * @param str A vector of characters representing the string.
 */
void print(const vector<char> & str);

/**
* @brief Gets a string from the user.
*
* This function gets a string from the user, character by character, until the user presses enter, space, or a non-alphabet character. The string is stored in a vector of characters.
*
* @param str A reference to a vector of characters where the string will be stored.
*/
void getString(vector<char> & str);

int main() {
    
    vector<char> word = {};
    
    int wakandaValue;
    
    int numWords;
    
    cout << "How many strings are there?  > ";
    numWords = getNum(1);
    for (int counter = 1; counter <= numWords; ++counter) {
        cout << format("Enter word #{}: ", counter) << flush;
        getString(word);
        print(word);
        cout << " has a WAKANDA value of ";
        wakandaValue = value(word);
        cout << format(" = {}%.\n", wakandaValue);
        if (wakandaValue == 100) {
            cout << LIME BOLD "CONGRATULATIONS - You have discovered a 100% word - " RESET;
            print(word);
            cout << "!!!!!\n";
        }
    }
    
    cout << "Press any key to exit...";
    _getch();
    return 0;
}

int value(vector<char> str) {
    int sum = 0;
    for (const auto & letter: str) {
        cout << static_cast<int>(letter) - ASCII_CONST;
        if (letter != str.back()) {
            cout << " + ";
        }
        sum += static_cast<int>(letter) - ASCII_CONST;
    }
    return sum;
}

void print(const vector<char> & str) {
    for (const auto & character: str) {
        cout << character;
    }
}

void getString(vector<char> & str) {
    char input;
    str.clear();
    while (true) {
        input = _getch();
        if (input == '\r' || input == '\n' || input == ' ') {
            cout << endl;
            return;
        }
        if (toupper(input) < 'A' || toupper(input) > 'Z') {
            continue;
        }
        cout << input;
        str.push_back(toupper(input));
    }
}