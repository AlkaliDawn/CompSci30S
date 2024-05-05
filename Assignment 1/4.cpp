// Program to simulate a roulette wheel, lets the user bet in a variety of ways - Comp Sci 30 S
// Evan Bartlett

#include <conio.h>
#include <format>
#include <iostream>
#include <string>
#include <random>

using namespace std;

#define RED "\033[38;2;240;6;10m"
#define GREEN "\033[38;2;22;233;99m"
#define RESET "\033[0m"
#define PURPLE "\033[38;2;204;0;255m"

// seeds the random number generator using a non-deterministic random number generator
void seed_random() {
    random_device tempDevice;
    srand(tempDevice());
    for (int i = 0; i < tempDevice(); i++) {
        rand();
    }
}

// function to get the input from the user
// if the input is not in the test_string than it is discarded
// test_string - a string of characters that are valid for the user to input
char get(string test_string) {
    while (true) {

        // get the inputted character
        char input = tolower(_getch());

        // checks if input matches anything in the test string, returns the char if it's the same
        for (char i: test_string) {
            if (i == input) {
                cout << input << "\n";
                return input;
            }
        }
    }
}

// defines a concept to make sure the type is an arithmetic type
template <typename T>
concept Arithmetic = is_arithmetic_v<T>;

// gets a number from the user, scrubbing the input to make sure it is arithmetic
// input - the ref variable for the input to be stored in
template <Arithmetic T>
void getNum(T &input) {
    while (!(cin >> input)) {
        cout << "Please enter numbers only." << endl;
        cin.clear();
        cin.ignore(10000,'\n');
    }
}

// function to get the input from the user
// input must be greater than 0 and less than or equal to money
// money - amount of money the user currently has
int askBet(int money) {
    int bet; // variable to store the bet
    while (true) { // loop until a valid bet is entered
        cout << "What will your bet be? ";
        getNum(bet);
        if (bet > money) {
            cout << RED "\nBet must not be more than money.\n\n" RESET;
            continue; // if the bet is more than the money, continue to the shift iteration
        }
        if (bet <= 0) {
            cout << RED "Bet must be greater than 0.\n\n" RESET;
            continue; // if the bet is less than or equal to 0, continue to the shift iteration
        }
        break;
    }
    return bet; // return the bet
}

// user bets on two numbers
// money - amount of money the user currently has
// winningNumber - number rolled on the wheel
int doubleBet(int money, int winningNumber) {

    int returnRate = 17; // return rate for double bet
    int balanceChange; // variable to store the change in money
    int firstNumber; // variable to store the first number the user bets on
    int secondNumber; // variable to store the second number the user bets on

    int bet = askBet(money); // get the bet from the user

    while (true) { // loop until a valid first number is entered
        cout << "What is the first number are you betting on? ";
        cin >> firstNumber;
        if (firstNumber > 36 || firstNumber <= 0) {
            cout << RED "\nThe first number must be 1 to 36.\n\n" RESET;
            continue;
        }
        break;
    }
    while (true) { // loop until a valid second number is entered
        cout << "What is the second number are you betting on? ";
        cin >> secondNumber;
        if (secondNumber > 36 || secondNumber <= 0) {
            cout << RED "\nThe second number must be 1 to 36.\n\n" RESET;
            continue;
        }
        break;
    }

    // if the winning number is the same as the first or second number, the user wins
    if (winningNumber == firstNumber || winningNumber == secondNumber) {
        balanceChange = bet * returnRate;
        money += balanceChange;
        cout << format(GREEN "Since you bet on {} and {}, and the winning number was {}, YOU WIN ${} and now have ${}\n" RESET,
            firstNumber, secondNumber, winningNumber, balanceChange, money);
        return balanceChange;
    }
    else { // if the winning number is not the same as the first or second number, the user loses
        balanceChange = bet;
        money -= balanceChange; //
        cout << format(RED "Since you bet on {} and {}, and the winning number was {}, YOU LOSE ${}! You now have ${}\n" RESET,
            firstNumber, secondNumber, winningNumber, balanceChange, money);
        return -balanceChange;
    }
}

// money - amount of money the user currently has
// winningNumber - number rolled on the wheel
int singleBet(int money, int winningNumber) { // returns change in money

     int returnRate = 35; // return rate for single bet
    int balanceChange; // variable to store the change in money
    int chosenNumber; // variable to store the number the user bets on

    int bet = askBet(money); // get the bet from the user

    while (true) { // loop until a valid number is entered
        cout << "What number are you betting on? ";
        cin >> chosenNumber;
        if (chosenNumber > 36 || chosenNumber <= 0) {
            cout << "\nThe number must be 1 to 36.\n\n";
            continue;
        }
        break;
    }
    if (winningNumber == chosenNumber) { // if the winning number is the same as the chosen number, the user wins
        balanceChange = bet * returnRate;
        money += balanceChange; // add the bet times the return rate to the money
        cout << format(GREEN "Since you bet on {} and the winning number was {}, YOU WIN ${} and now have ${}\n" RESET,
            chosenNumber, winningNumber, balanceChange, money);
        return balanceChange;
    }
    else { // if the winning number is not the same as the chosen number, the user loses
        balanceChange = bet;
        money -= balanceChange; // subtract the bet from the money
        cout << format(RED "Since you bet on {} and the winning number was {}, YOU LOSE ${}! You now have ${}\n" RESET,
            chosenNumber, winningNumber, balanceChange, money);
        return -balanceChange;
    }
}

// money - amount of money the user currently has
// winningNumber - number rolled on the wheel
int evenBet(int money, int winningNumber) {

     int returnRate = 1; // return rate for even bet
    int balanceChange; // variable to store the change in money

    int bet = askBet(money); // get the bet from the user

    if (winningNumber % 2 == 0) { // if the winning number is even, the user wins
        balanceChange = bet * returnRate;
        money += balanceChange;
        cout << format(GREEN "Since you bet on Even and the winning number ({}) is an Even number, YOU WIN ${} and now have ${}\n" RESET,
            winningNumber, balanceChange, money);
        return balanceChange;
    }
    else { // if the winning number is odd, the user loses
        balanceChange = bet;
        money -= balanceChange;
        cout << format(RED "Since you bet on Even and the winning number ({}) is an Odd number, YOU LOSE ${}! You now have ${}\n" RESET,
          winningNumber, balanceChange, money);
        return -balanceChange;
    }
}

// money - amount of money the user currently has
// winningNumber - number rolled on the wheel
int oddBet(int money, int winningNumber) {

     int returnRate = 1; // return rate for odd bet
    int balanceChange; // variable to store the change in money

    int bet = askBet(money); // get the bet from the user

    if (winningNumber % 2 == 1) { // if the winning number is odd, the user wins
        balanceChange = bet * returnRate;
        money += balanceChange;
        cout << format(GREEN "Since you bet on Odd and the winning number ({}) is an Odd number, YOU WIN ${} and now have ${}\n" RESET,
            winningNumber, balanceChange, money);
        return balanceChange;
    }
    else { // if the winning number is even, the user loses
        balanceChange = bet;
        money -= balanceChange;
        cout << format(RED "Since you bet on Odd and the winning number ({}) is an Even number, YOU LOSE ${}! You now have ${}\n" RESET,
            winningNumber, balanceChange, money);
        return -balanceChange;
    }
}

// money - amount of money the user currently has
// winningNumber - number rolled on the wheel
int primeBet(int money, int winningNumber) {

    int primes[11] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31}; // array of prime numbers
    int returnRate = 2; // return rate for prime bet
    int balanceChange; // variable to store the change in money

    int bet = askBet(money); // get the bet from the user

    for (int i: primes) { // for every prime number
        if (i == winningNumber) {
            balanceChange = bet * returnRate;
            money += balanceChange;
            cout << format(GREEN "Since you bet on Primes and the winning number was a prime: {}, YOU WIN ${} and now have ${}\n" RESET,
                winningNumber, balanceChange, money);
            return balanceChange;
        }
    }
    balanceChange = bet;
    money -= balanceChange;
    cout << format(RED "Since you bet on Primes and the winning number wasn't a prime: {}, YOU LOSE ${}! You now have ${}\n" RESET,
        winningNumber, balanceChange, money);
    return -balanceChange;
}



int main() {

    seed_random();

    int money = rand() % 500 + 501; // how much money the user has
    int winningNumber = rand() % 36 + 1; // the number rolled on the wheel
    string TEST_STRING = "seodpx"; // string of possible user inputs

    bool flag = true;
    while (flag) {
        cout << PURPLE "Welcome to Evan's Fantasitcal Roulette! You have $" << money << " to start." RESET "\n";
        cout << "Do you want to play (S)ingle, (E)ven, (O)dd, (D)ouble numbers, (P)rime, or e(X)it? ";
        switch (get(TEST_STRING)) {
            case 's': {
                money += singleBet(money, winningNumber);
                break;
            }
            case 'e': {
                money += evenBet(money, winningNumber);
                break;
            }
            case 'o': {
                money += oddBet(money, winningNumber);
                break;
            }
            case 'd': {
                money += doubleBet(money, winningNumber);
                break;
            }
            case 'p': {
                money += primeBet(money, winningNumber);
                break;
            }
            case 'x': {
                flag = false;
                break;
            }
        }

        winningNumber = rand() % 36 + 1;

        if (money <= 0) {
            cout << RED "Uh oh! You've gone broke. One of our bouncers will now escort you out. Thanks for losi- Playing!!\n\n" RESET;
            flag = false;
        }

    }

    cout << "press any key to exit...";

    _getch();

    return 0;

}