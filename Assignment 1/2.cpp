#include <iostream>
#include <string>
#include <cmath>
#include <conio.h>
#include <format>

using namespace std;

// function to raise a base to an exponent
// if the base is 0 and the exponent is not 0, returns 0
// if the exponent is 0, returns 1
// multiplies the base by itself exponent times
// if the exponent is negative, reciprocate the result
constexpr float power(float base, int exponent) {
    float result = 1;
    if (base == 0 && exponent != 0) { // if the base is 0 and the exponent is not 0, return 0
        return 0;
    }
    if (exponent == 0) { // if the exponent is 0, return 1
        return 1;
    }
    for (int i = 0; i < abs(exponent); i++ ) { // multiply the base by itself exponent times
        result *= base;
    }
    if (exponent < 0) {
        result = 1/result; // if exponent is negative, reciprocate result
    }
    return result;
}

// function to validate the input
// prevents power function from being called with a base of 0 and an exponent of 0
bool validate(float base, int exponent) {
    if (base == 0 && exponent == 0) {
        return false;
    }
    return true;
}

// function to print the result of the power function
void printResult(float base, int exponent) {
    cout << base << " raised to the power of " << exponent << " is " << power(base, exponent) << endl;
}

// function to get the input from the user
void getInput(float &base, int &exponent) {
    cout << "Enter a Base: ";
    cin >> base;
    cout << "Enter an Exponent: ";
    cin >> exponent;
}

// function to get the second input from the user in part two
void getSecondInput(float &base, int &exponent) {
    cout << "Enter a Second Base: ";
    cin >> base;
    cout << "Enter an Second Exponent: ";
    cin >> exponent;
}

int main() {
    float base = 0; // base to raise to a power
    int exponent = 0; // exponent to raise the base to
    float base2 = 0; // second base to raise to a power
    int exponent2 = 0; // second exponent to raise the second base to

    cout << "PART ONE\n"; // print the header for part one

    int count = 3; // number of times to get a base and exponent from the user and print the result
    while (count > 0) {

        getInput(base, exponent); // get the base and exponent from the user

        // if the base and exponent are both 0, print an error message and continue to the next iteration
        if(!validate(base, exponent)) {
            cout << "Invalid Input! Base and Exponent CANNOT both be zero. Please try again...\n\n";
            continue;
        }

        printResult(base, exponent); // print the result of the power function
        count--; // decrement the count
    }
    cout << "PART TWO\n"; // print the header for part two

    while (true) {
        getInput(base, exponent); // get the base and exponent from the user
        if(!validate(base, exponent)) { // if the base and exponent are both 0, print an error message and continue to the next iteration
            cout << "Invalid Input! Base and Exponent CANNOT both be zero. Please try again...\n\n";
            continue;
        }
        break;
    }
    while (true) {
        getSecondInput(base2, exponent2); // get the second base and exponent from the user
        if(!validate(base2, exponent2)) { // if the second base and exponent are both 0 continue to the next iteration
            cout << "Invalid Input! The Second Base and Second Exponent CANNOT both be zero. Please try again...\n\n";
            continue;
        }
        if(exponent2 < 0) { // if the second exponent is negative continue to the next iteration
            cout << "Invalid Input!The Second Exponent MUST be greater than zero. Please try again...\n\n";
            continue;
        }
        break;
    }

    // example math
    // (2 ^ 3) + (3 ^ 1) - (2 ^ 1) + (3 ^ 3)
    // 1)   (Base1Power1 + Base2Power2 ) - Base1Power2 + Base2Power1  and
    // 2) (Base1Power1 ) to the power of ( Base2Power2 )

    // (Base1Power1) + (Base2Power2) - (Base1Power2) + (Base2Power1)
    cout << format("({} ^ {}) + ({} ^ {}) - ({} ^ {}) + ({} ^ {}) is ",
        base, exponent, base2, exponent2, base, exponent2, base2, exponent
    ) << power(base, exponent) + power(base2, exponent2) - power(base, exponent2) + power(base2, exponent);

    cout << "\n";

    // (Base1Power1) to the power of (Base2Power2)
    cout << format("({} to the power of {}) to the power of ({} to the power of {}) is ",
       base, exponent, base2, exponent2
    ) << power(power(base, exponent), power(base2, exponent2));


    _getch(); // wait for a key press before exiting
}