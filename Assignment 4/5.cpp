#include <algorithm>
#include <iostream>
#include <conio.h>
#include <cmath>
#include <random>
#include <format>

#include "bartlett.h"

using namespace std;

#define NUM_CHARS 27 // 26 letters + 1 for space
#define ASCII_CONST 65 // converts ascii value to freq array index


constexpr string_view alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

/**
 * @brief This function gets a string of characters from the user.
 *
 * The function clears the existing string vector and then fills it with characters input by the user.
 * Each character represents a letter in the alphabet or a space. The function also handles invalid inputs by ignoring them.
 *
 * @param str A reference to a vector of characters that represents the user's input string.
 */
void getString(vector<char> & str);

/**
 * @brief This function calculates the frequency of each character in the user's input string.
 *
 * The function iterates over the user's input string. For each character in the string, it increments the corresponding index in the frequency vector. If the character is a space, it increments the last index of the frequency vector.
 *
 * @param str A vector of characters that represents the user's input string.
 * @param freq A vector of integers that represents the frequency of each character in the user's input string.
 */
void addFreq(vector<char> & str, vector<int> & freq);

/**
 * @brief This function prints the frequency of each character in the user's input string.
 *
 * The function iterates over the frequency vector. For each index in the vector, it prints the corresponding character and its frequency in the user's input string. If the index is the last index of the vector, it prints the frequency of spaces. The function also calculates and prints the percentage of the total characters that each character represents.
 *
 * @param freq A vector of integers that represents the frequency of each character in the user's input string.
 */
void print(vector<int> & freq);

int main() {
    
    vector<char> lines = {};
    vector<int> freq;
    
    for (int i = 0; i < 27; ++i) {
        freq.push_back(0);
    }
    
    int numLines;
    
    cout << "How many lines are there to read in?  > ";
    numLines = getNum(1);
    for (int counter = 1; counter <= numLines; ++counter) {
        cout << format("Enter line #{}: ", counter) << flush;
        getString(lines);
        addFreq(lines, freq);
    }
    print(freq);
    
    cout << "Press any key to exit...";
    _getch();
    return 0;
}

void getString(vector<char> & str) {
    char input;
    str.clear();
    while (true) {
        input = _getch();
        if (input == '\r' || input == '\n') {
            cout << endl;
            return;
        }
        if ((toupper(input) < 'A' || toupper(input) > 'Z') && input != ' ') {
            continue;
        }
        cout << input;
        str.push_back(toupper(input));
    }
}

void addFreq(vector<char> & str, vector<int> & freq) {
    for (const auto & item: str) {
        if (item != ' ') {
            // increment respective spot in freq array, using ascii const to convert from ascii value to array index. 'A' becomes 0, 'B' becomes 1, etc.
            freq.at(item - ASCII_CONST) += 1;
        }
        else {
            freq.back() += 1; // incrememnt last item, as that is space's freq
        }
    }
}

void print(vector<int> & freq) {
    int total = 0;
    for (const auto & item: freq) {
        total += item;
    }
    for (int i = 0; i < NUM_CHARS - 1; ++i) {
        cout << "  " << static_cast<char>(i + ASCII_CONST) << " > ";
        for (int j = 1; j <= freq.at(i); ++j) {
            cout << '=';
        }
        if (freq.at(i) != 0) {
            cout << format("   ({} chars, representing {}% of total)\n", freq.at(i), round((static_cast<double>(freq.at(i)) / total) * 100));
        }
        else {
            cout << '\n';
        }
    }
    // handle space
    cout << " ' '> ";
    for (int i = 0; i < freq.back(); ++i) {
        cout << '=';
    }
    if (freq.back() != 0) {
        cout << format("   ({} chars, representing {}% of total)\n", freq.back(), round((static_cast<double>(freq.back()) / total) * 100));
    }
    else {
        cout << '\n';
    }
}