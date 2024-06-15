// Generic functions that are used in most of my programs
// @formatter:off

#ifndef BARTLETT_H
#define BARTLETT_H

#endif //BARTLETT_H

#include <iostream>
#include <conio.h>
#include <random>
#include <span>

using namespace std;

#define RESET "\033[0m"
#define BOLD "\033[1m"
#define GREEN "\033[38;2;0;153;51m"
#define RED "\033[38;2;240;6;10m"
#define BLACK "\033[38;2;132;132;132m"

#define LIME "\033[38;2;95;255;51m"
#define YELLOW "\033[38;2;241;255;38m"
#define ORANGE "\033[38;2;255;188;54m"
#define PURPLE "\033[38;2;204;0;255m"
#define PINK "\033[38;2;241;112;149m"
#define TEAL "\033[38;2;10;171;123m"
#define BLUE "\033[38;2;8;206;255m"
#define PASTEL_BLUE "\033[38;2;98;84;255m"

constexpr int Ignore_Value = 10000;

// seeds the random number generator using a non-deterministic random number
// generator
void seedRandom() {
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
        cout << "Please enter numbers only." << '\n';
        cin.clear();
        cin.ignore(Ignore_Value, '\n');
    }
    cin.ignore(Ignore_Value, '\n');
    return num;
} // VOID GETNUM<T>()


template <Arithmetic T>
T getNum(T low, T high) {
    T num;
    while (true) {
        while (!(cin >> num)) {
            cout << "Please enter numbers only." << '\n';
            cin.clear();
            
            cin.ignore(Ignore_Value, '\n');
        }
        cin.ignore(Ignore_Value, '\n');
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
            cin.ignore(10000, '\n');
        }
        if (num < low) {
            cout << "Input must not be less than " << low << endl;
            continue;
        }
        break;
    }
    return num;
} // T GETNUM(T)

char get(const string & testString) {
    while (true) {
        
        // get the inputted character
        char input = tolower(_getch());
        
        // checks if input matches anything in the test string, returns the char
        // if it's the same
        for (const char i: testString) {
            if (i == input) {
                cout << input << '\n';
                return input;
            }
        }
    }
} // CHAR GET(STRING&)

char getNot(const string & testString) {
    while (true) {
        
        // get the inputted character
        char input = tolower(_getch());
        
        // checks if input matches anything in the test string, returns the char
        // if it's the same
        if (none_of(testString.begin(), testString.end(), [input](char val){ return input == val; })) {
            cout << input << '\n';
            return input;
        }
    }
} // CHAR GET(STRING&)
//
//template <Arithmetic T>
//T binarySearch(vector<T> data, T value) {
//    int low = 0;
//    int high = data.size() - 1;
//    int middle;
//    while (low != high) {
//        middle = floor((low+high) / 2);
//        if (data.at(middle) < value) {
//            low = middle + 1;
//            continue;
//        }
//        if (data.at(middle) > value) {
//            high = middle - 1;
//            continue;
//        }
//        return middle;
//    }
//    return -1;
//}
//
//template <Arithmetic T>
//bool bubbleSort(vector<dataType> &data) {
//    int numRight = 0; // used to check if array is sorted when ascending
//    for (int i = 0; i < data.size(); ++i) {
//        for (auto iter = data.begin(); iter < data.end() - i - 1; ++iter) {
//            if (*iter > *(iter + 1)) {
//                std::swap(*iter, *(iter + 1));
//            }
//        }
//    }
//}
//
//// linear search needs an unordered list
//
//template <Arithmetic T>
//bool insertionSort(vector<T> & data) {
//    for (int i = 1; i < data.size(); ++i) {
//        for (auto j = data.begin() + i; j != data.begin(); --j) {
//            auto left = j - 1;
//            auto right = j;
//            if (*left > *right) {
//                std::swap(*left, *right);
//            }
//            else {
//                break;
//            }
//        }
//    }
//}