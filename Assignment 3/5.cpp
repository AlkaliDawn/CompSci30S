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

void getString(vector<char> & str);

void addFreq(vector<char> & str, vector<int> & freq);

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