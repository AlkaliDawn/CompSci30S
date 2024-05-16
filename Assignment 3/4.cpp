#include <algorithm>
#include <iostream>
#include <conio.h>
#include <cmath>
#include <random>
#include <format>
#include "bartlett.h"

using namespace std;

void makeCombo(vector<char> & str);

void getGuess(vector<char> & str);

void getRank(int round);

bool compare(const vector<char> & guess, const vector<char> & combo);

int main() {
    
    seedRandom();
    
    vector<char> combo = {};
    vector<char> guess = {};
    
    char input = 'y';
    
    int lowestRound = INT16_MAX;
    int totalRounds = 0;
    int wins = 0;
    
    int round = 1;
    
    makeCombo(combo);
    
    while (input == 'y') {
        cout << format("Try #{}: Guess the 3-letter combo: ", round);
        getGuess(guess);
        if (compare(guess, combo)) {
            cout << '\n';
            cout << format("YOU GOT IT IN {} TRIES - YOUR RATING IS... ", round);
            getRank(round);
            lowestRound = std::min(round, lowestRound);
            totalRounds += round;
            ++wins;
            makeCombo(combo);
            round = 1;
            cout << "Do you want to play another round (Y/N)? ";
            input = get("yn");
        }
        else {
            cout << '\n';
            ++round;
        }
    }
    
    cout << format("You played {} time(s), and it took you an average of {} tries to solve each one! Your best score was {} tries!\n",
                   wins, std::round((static_cast<float>(totalRounds) / wins) * 100) / 100, lowestRound);
    
    cout << "Press any key to exit...";
    _getch();
    return 0;
}



void makeCombo(vector<char> & str) {
    str.clear();
    for (int i = 0; i < 3; ++i) {
        str.push_back(rand() % 26 + 65);
    }
}

void getGuess(vector<char> & str) {
    char input;
    str.clear();
    for (int i = 0; i < 3;) {
        input = _getch();
        if (toupper(input) < 'A' || toupper(input) > 'Z') {
            continue;
        }
        ++i;
        cout << input;
        str.push_back(toupper(input));
    }
}

void getRank(int round){
    if (round < 9) {
        cout << "GOD LIKE!!!!!!!!!";
    }
    else if (round < 11) {
        cout << "MIRACLE PERFORMER!!!!!!!!";
    }
    else if (round < 13) {
        cout << "PHD IN QUANTUM LETTER PHYSICS!!!!!";
    }
    else if (round < 16) {
        cout << "WORD CONNOISSEUR!!";
    }
    else if (round < 19) {
        cout << "Letter Master!";
    }
    else if (round < 22) {
        cout << "Average Joe.";
    }
    else if (round < 26) {
        cout << "A Bit Rusty.";
    }
    else if (round < 30) {
        cout << "Not doin' too hot.";
    }
    else if (round < 35) {
        cout << "Wow, that's, pretty bad.";
    }
    else {
        cout << "Actually, you know what, just give up.";
    }
    cout << '\n';
}

bool compare(const vector<char> & guess, const vector<char> & combo) {
    for (int i = 0; i < 3; ++i) {
        if (guess.at(i) < combo.at(i)) {
            cout << " - TOO LOW";
            return false;
        }
        if (guess.at(i) > combo.at(i)) {
            cout << " - TOO HIGH";
            return false;
        }
    }
    return true;
}
