#include <iostream>
#include <conio.h>
#include <random>
#include <format>

using namespace std;

void seedRandom() {
    random_device tempDevice;
    srand(tempDevice());
    for (int i = 0; i < tempDevice(); i++) {
        rand();
    }
}

bool isVowel(char letter);

void replace(vector<char> & phrase);

const array<char, 6> vowels = {'A', 'E', 'I', 'O', 'U', 'Y'};

const array<char, 20> consonants = {'B', 'C', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'X', 'Z'};

int main() {
    
    seedRandom();
    int numReplacements;
    vector<char> phrase;
    char input;
    cout << "Enter String: ";
    while (true) {
        input = toupper(_getche());
        if (input == '\n' || input == '\r') {
            break;
        }
        phrase.push_back(input);
    }
    cout << endl;
    cout << "How many replacements? > ";
    cin >> numReplacements;
    for (int i = 1; i <= numReplacements; i++) {
        replace(phrase);
    }
    cout << "The final string is: ";
    for (char i: phrase) {
        cout << i;
    }
    cout << endl;
    cout << "Press any key to exit...";
    _getch();
    return 0;
}

bool isVowel(char letter) {
    for (char i: vowels) {
        if (i == letter) {
            return true;
        }
    }
    return false;
}

void replace(vector<char> & phrase) {
    int change;
    while (true) {
        int randomSpot = rand() % phrase.size();
        if (phrase.at(randomSpot) == ' ') {
            continue;
        }
        if (isVowel(phrase.at(randomSpot))) {
            change = rand() % 6;
            cout << format("{} was replaced with {}\n", phrase.at(randomSpot), vowels.at(change));
            phrase.at(randomSpot) = vowels.at(change);
        }
        else {
            change = rand() % 20;
            cout << format("{} was replaced with {}\n", phrase.at(randomSpot), consonants.at(change));
            phrase.at(randomSpot) = consonants.at(change);
        }
        break;
    }
}