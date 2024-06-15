// REPLACER 9000 -

#include <algorithm>
#include <iostream>
#include <conio.h>
#include <cmath>
#include <random>
#include <format>
#include "bartlett.h"

using namespace std;

int replace(vector<char> & str, char from, char to);

void getString(vector<char> & str);

int main() {
    
    vector<char> replacement = {};
    
    char from;
    char to;
    
    char input = 'y';
    
    int numReplacements = 0;
    
    int numStrings = 0;
    
    cout << "How many strings are there?  > ";
    numStrings = getNum(1);
    for (int counter = 1; counter <= numStrings; ++counter) {
        cout << format("Enter string #{}: ", counter) << flush;
        getString(replacement);
        while (input == 'y') {
            cout << "Enter character to replace: ";
            from = getNot("\n\r");
            cout << format("What should '{}' be replaced with? ", from);
            to = getNot("\n\r");
            numReplacements += replace(replacement, from, to);
            cout << "Do you want to another replacement (Y/N)? ";
            input = get("yn");
        }
        cout << format("After a total of {} replacements, the final string is:\n", numReplacements);
        for (const auto & item: replacement) {
            cout << item;
        }
        cout << endl;
    }
    
    cout << "Press any key to exit...";
    _getch();
    return 0;
}

int replace(vector<char> & str, char from, char to) {
    int num = 0;
    for (char & i: str) {
        if (i == from) {
            i = to;
            ++num;
        }
    }
    return num;
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
        cout << '*';
        str.push_back(input);
    }
}
