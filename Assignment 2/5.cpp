
#include <iostream>
#include <conio.h>
#include <cmath>
#include <random>
#include <format>
#include <algorithm>

#include "bartlett.h"

#define GOLD "\033[38;2;187;166;61m"


using namespace std;

constexpr array<string_view, 8> Colors = {LIME, PASTEL_BLUE, YELLOW, ORANGE, PINK, TEAL, PURPLE, BLUE};

constexpr int Num_Cases = 13;
constexpr array<int, Num_Cases> Values = {1, 5, 10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000};

int getCase(array<int, Num_Cases> & cases);

double getBankerOffer(int firstCaseValue, const array<int, Num_Cases> & cases);

int main() {
    seedRandom();
    
    array<int, Num_Cases> cases = {};
    
    int currentCase = 0;
    int firstCase = 0;
    int firstCaseValue = 0;
    double bankerOffer = 0.0;
    int num = 0;
    
    cases.fill(-1);
    
    for (int i = 0; i < Num_Cases;) {
        num = rand() % Num_Cases;
        
        // if the case has already been made, try again with a new number without iterating counter
        if (any_of(cases.begin(), cases.end(), [num](int val) { return val == num; })) {
            continue;
        }
        
        // add the case
        cases.at(i) = num;
        
        
        // iterate counter
        ++i;
        
    }
    
    for (int i = 0; i < Num_Cases; ++i) {
        cases.at(i) = Values.at(cases.at(i));
    }
    
    while (true) {
        cout << "Welcome to Dakota Deal or No Deal. What case do you want (1 - 13)?  ";
        firstCase = getCase(cases);
        firstCaseValue = cases.at(firstCase);
        cases.at(firstCase) = -1;
        for (int i = 0; i < 3; ++i) {
            cout << "OK - now you must pick 3 more cases - ";
            for (int j = 0; j < 3; ++j) {
                cout << "What case do you want?  ";
                currentCase = getCase(cases);
                cout << format("Case {} has ${}\n", currentCase + 1, cases.at(currentCase));
                cases.at(currentCase) = -1;
            }
            bankerOffer = getBankerOffer(firstCaseValue, cases);
            bankerOffer = round(bankerOffer * 100) / 100;
            cout << format("The banker is offering you ${} - Deal or No Deal (D/N)?  ", bankerOffer);
            if (get("dn") == 'd') {
                cout << format("You get ${0}, and your case (case {1}) contained... ${2}! You leave with ${0}.\n", bankerOffer, firstCase + 1, firstCaseValue);
                cout << "Here's what $$$ was in each case:\n";
                for (int i = 0; i < Num_Cases; ++i) { // for every
                    if (cases.at(i) != -1) {
                        cout << format("Case {} had ${}!\n", i + 1, cases.at(i));
                    }
                }
                _getch();
                return 0;
            }
            bankerOffer = 0;
        }
        for (int j = 0; j < 3; ++j) {
            cout << "What case do you want?  ";
            currentCase = getCase(cases);
            cout << format("Case {} has ${}\n", currentCase + 1, cases.at(currentCase));
            cases.at(currentCase) = -1;
        }
        cout << format("That means your case (case {0}) contains ${1}! You leave with ${1}\n", firstCase + 1, firstCaseValue);
        break;
    }
    _getch();
    return 0;
}

/**
 *
 * @param firstCaseValue value of the first case selected by user, as its value is already overwritten
 * @param cases the array of the values of the cases
 * @return the banker's current offer, ie the average of the unpicked cases
 */
double getBankerOffer(int firstCaseValue, const array<int, Num_Cases> & cases) {
    double sum = 0;
    int count = 1;
    for (const auto & item: cases) {
        if (item != -1) { // if case is not taken, add its value to the sum, and increment the counter
            sum += item;
            ++count;
        }
    }
    sum += firstCaseValue;
    sum /= count;
    return sum;
}

/**
 *
 * @param cases the array of the values of the cases
 * @return the index of the case the user chose
 */
int getCase(array<int, Num_Cases> & cases) {
    while (true) {
        int choice = getNum(1, Num_Cases) - 1; // get the case from the user and subtract 1 to turn it into an index
        if (cases.at(choice) != -1) { // as long the case hasn't been chosen, return it
            return choice;
        }
        cout << "That case is already chosen!\nWhat case do you want?  ";
    }
}