#include <algorithm>
#include <iostream>
#include <conio.h>
#include <cmath>
#include <random>
#include <format>
#include "bartlett.h"

using namespace std;

/**
 * @brief Generates a password of a given length.
 *
 * This function generates a password of a given length by randomly selecting characters from an array of symbols.
 *
 * @param str A reference to a vector of characters where the password will be stored.
 * @param passLen The length of the password to be generated.
 */
void makePassword(vector<char> & str, int passLen);

/**
 * @brief Gets a password from the user.
 *
 * This function gets a password from the user.
 * The password is stored in a vector of characters.
 *
 * @param str A reference to a vector of characters where the password will be stored.
 */
void typePassword(vector<char> & str);

/**
 * @brief Compares two passwords.
 *
 * This function compares two passwords stored in vectors of characters. It returns true if the passwords match and false otherwise.
 *
 * @param str1 A vector of characters representing the first password.
 * @param str2 A vector of characters representing the second password.
 * @param str3 A vector of characters representing the third password.
 * @return A boolean value indicating whether the passwords match.
 */
bool compare(vector<char> str1, vector<char> str2, vector<char> str3);

constexpr string_view symbols = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*()[]|/?.>,<;:'\"";
constexpr int Num_Symbols = 75;

int main() {
    
    seedRandom();
    
    vector<char> password = {};
    vector<char> typed1 = {};
    vector<char> typed2 = {};
    
    int passLen = 0;
    
    cout << "What length of password do you want (max = 24)?  > ";
    passLen = getNum(1, 24);
    makePassword(password, passLen);
    cout << "Your new pass word is ";
    for (const auto & item: password) {
        cout << item;
    }
    cout << endl;
    while (true) {
        cout << "Type your new password: ";
        typePassword(typed1);
        cout << "Confirm your new password by re-typing it: ";
        typePassword(typed2);
        if (compare(typed1, typed2, password)) {
            break;
        }
        cout << "Passwords dont match - ";
    }
    
    cout << "Password reset!\n";
    
    cout << "Press any key to exit...";
    _getch();
    return 0;
}



void makePassword(vector<char> & str, int passLen) {
    for (int i = 0; i < passLen; ++i) {
        str.push_back(symbols.at(rand() % Num_Symbols));
    }
}

void typePassword(vector<char> & str) {
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


bool compare(vector<char> str1, vector<char> str2, vector<char> str3) {
    if (str1.size() != str2.size()) {
        return false;
    }
    for (int i = 0; i < str1.size(); ++i) {
        if (str1.at(i) != str2.at(i) || str1.at(i) != str3.at(i)) {
            return false;
        }
    }
    return true;
}
