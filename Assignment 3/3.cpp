#include <algorithm>
#include <iostream>
#include <conio.h>
#include <random>
#include <format>
#include "bartlett.h"

#define ASCII_CONST 64

using namespace std;

int value(vector<char> str);

void print(const vector<char> & str);

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
    for (auto iter = str.begin(); iter != str.end() - 1; ++iter) {
        cout << static_cast<int>(*iter) - ASCII_CONST << " + ";
        sum += static_cast<int>(*iter) - ASCII_CONST;
    }
    cout << static_cast<int>(str.back()) - ASCII_CONST;
    sum += static_cast<int>(str.back()) - ASCII_CONST;
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
