// Generic functions that are used in most of my programs

#ifndef BARTLETT_H
#define BARTLETT_H

#endif //BARTLETT_H

#include <iostream>
#include <conio.h>
#include <random>

using namespace std;

#define RED "\033[38;2;240;6;10m"
#define BLACK "\033[38;2;132;132;132m"
#define BOLD "\033[1m"
#define RESET "\033[0m"
#define GREEN "\033[38;2;0;153;51m"
#define PURPLE "\033[38;2;204;0;255m"

// seeds the random number generator using a non-deterministic random number generator
void seed_random() {
    random_device tempDevice;
    srand(tempDevice());
    for (int i = 0; i < tempDevice(); i++) {
        rand();
    }
}

template <typename T>
concept Arithmetic = is_arithmetic_v<T>;

template <Arithmetic T>
T getNum() {
    T num;
    while (!(cin >> num)) {
        cout << "Please enter numbers only." << endl;
        cin.clear();
        cin.ignore(10000,'\n');
    }
    cin.ignore(10000,'\n');
    return num;
} // VOID GETNUM<T>()

template <Arithmetic T>
T getNum(T low, T high) {
    T num;
    while (true) {
        while (!(cin >> num)) {
            cout << "Please enter numbers only." << endl;
            cin.clear();
            cin.ignore(10000,'\n');
        }
        cin.ignore(10000,'\n');
        if (num < low) {
            cout << "Input must not be less than " << low << endl;
            continue;
        }
        if (num > high) {
            cout << "Input must not be more than " << high << endl;
            continue;
        }
        break;
    }
    return num;
} // T GETNUM(T, T)

template <Arithmetic T>
T getNum(T low) {
    T num;
    while (true) {
        while (!(cin >> num)) {
            cout << "Please enter numbers only." << endl;
            cin.clear();
            cin.ignore(10000,'\n');
        }
        cin.ignore(10000,'\n');
        if (num < low) {
            cout << "Input must not be less than " << low << endl;
            continue;
        }
        break;
    }
    return num;
} // T GETNUM(T)

char get(const string& test_string) {
    while (true) {

        // get the inputted character
        char input = tolower(_getch());
        
        // checks if input matches anything in the test string, returns the char if it's the same
        for (const char i: test_string) {
            if (i == input) {
                cout << input << '\n';
                return input;
            }
        }
    }
} // CHAR GET(STRING&)

string sget() {
    string str;
    while (true) {
        getline(cin, str);
        if (!str.empty()) {
            break;
        }
    }
    return str;
} // STRING GET()
