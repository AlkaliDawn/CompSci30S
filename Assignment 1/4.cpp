
#include <conio.h>
#include <format>
#include <iostream>
#include <string>
#include <random>

using namespace std;

// seeds the random number generator using a non-deterministic random number generator
void seed_random() {
    random_device tempDevice;
    srand(tempDevice());
    for (int i = 0; i < tempDevice(); i++) {
        rand();
    }
}

// function to get the input from the user
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

// function to get the input from the user
// input must be greater than 0 and less than or equal to money
int askBet(int money) {
    int bet; // variable to store the bet
    while (true) { // loop until a valid bet is entered
        cout << "What will your bet be? ";
        cin >> bet;
        if (bet > money) {
            cout << "\nBet must not be more than money.\n\n";
            continue; // if the bet is more than the money, continue to the next iteration
        }
        if (bet <= 0) {
            cout << "Bet must be greater than 0.\n\n";
            continue; // if the bet is less than or equal to 0, continue to the next iteration
        }
        break;
    }
    return bet; // return the bet
}

// user bets on two numbers
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
            cout << "\nThe first number must be 1 to 36.\n\n";
            continue;
        }
        break;
    }
    while (true) { // loop until a valid second number is entered
        cout << "What is the second number are you betting on? ";
        cin >> secondNumber;
        if (secondNumber > 36 || secondNumber <= 0) {
            cout << "\nThe second number must be 1 to 36.\n\n";
            continue;
        }
        break;
    }

    // if the winning number is the same as the first or second number, the user wins
    if (winningNumber == firstNumber || winningNumber == secondNumber) {
        balanceChange = bet * returnRate;
        money += balanceChange;
        cout << format("Since you bet on {} and {}, and the winning number was {}, YOU WIN ${} and now have ${}\n",
            firstNumber, secondNumber, winningNumber, balanceChange, money);
        return balanceChange;
    }
    else { // if the winning number is not the same as the first or second number, the user loses
        balanceChange = bet;
        money -= balanceChange; //
        cout << format("Since you bet on {} and {}, and the winning number was {}, YOU LOSE ${}! You now have ${}\n",
            firstNumber, secondNumber, winningNumber, balanceChange, money);
        return -balanceChange;
    }
}

int singleBet(int money, int winningNumber) { // returns change in money

     int returnRate = 35;

    int balanceChange;

    int chosenNumber;

    int bet = askBet(money);

    while (true) {
        cout << "What number are you betting on? ";
        cin >> chosenNumber;
        if (chosenNumber > 36 || chosenNumber <= 0) {
            cout << "\nThe number must be 1 to 36.\n\n";
            continue;
        }
        break;
    }
    if (winningNumber == chosenNumber) {
        balanceChange = bet * returnRate;
        money += balanceChange;
        cout << format("Since you bet on {} and the winning number was {}, YOU WIN ${} and now have ${}\n",
            chosenNumber, winningNumber, balanceChange, money);
        return balanceChange;
    }
    else {
        balanceChange = bet;
        money -= balanceChange;
        cout << format("Since you bet on {} and the winning number was {}, YOU LOSE ${}! You now have ${}\n",
            chosenNumber, winningNumber, balanceChange, money);
        return -balanceChange;
    }
}

int evenBet(int money, int winningNumber) {

     int returnRate = 1;

    int balanceChange;

    int bet = askBet(money);

    if (winningNumber % 2 == 0) {
        balanceChange = bet * returnRate;
        money += balanceChange;
        cout << format("Since you bet on Even and the winning number ({}) is an Even number, YOU WIN ${} and now have ${}\n",
            winningNumber, balanceChange, money);
        return balanceChange;
    }
    else {
        balanceChange = bet;
        money -= balanceChange;
        cout << format("Since you bet on Even and the winning number ({}) is an Odd number, YOU LOSE ${}! You now have ${}\n",
          winningNumber, balanceChange, money);
        return -balanceChange;
    }
}

int oddBet(int money, int winningNumber) {

     int returnRate = 1;

    int balanceChange;

    int bet = askBet(money);

    if (winningNumber % 2 == 1) {
        balanceChange = bet * returnRate;
        money += balanceChange;
        cout << format("Since you bet on Odd and the winning number ({}) is an Odd number, YOU WIN ${} and now have ${}\n",
            winningNumber, balanceChange, money);
        return balanceChange;
    }
    else {
        balanceChange = bet;
        money -= balanceChange;
        cout << format("Since you bet on Odd and the winning number ({}) is an Even number, YOU LOSE ${}! You now have ${}\n",
            winningNumber, balanceChange, money);
        return -balanceChange;
    }
}

int primeBet(int money, int winningNumber) {
    int primes[11] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};

     int returnRate = 2;

    int balanceChange;

    int chosenNumber;

    int bet = askBet(money);

    while (true) {
        cout << "What number are you betting on? ";
        cin >> chosenNumber;
        if (chosenNumber > 36 || chosenNumber <= 0) {
            cout << "\nThe number must be 1 to 36.\n\n";
            continue;
        }
        break;
    }

    for (int i: primes) {
        if (chosenNumber == i && chosenNumber == winningNumber) {
            balanceChange = bet * returnRate;
            money += balanceChange;
            cout << format("Since you bet on Primes and the winning number wasn't a prime: {}, YOU WIN ${} and now have ${}\n",
                winningNumber, balanceChange, money);
            return balanceChange;
        }
    }
    balanceChange = bet;
    money -= balanceChange;
    cout << format("Since you bet on Primes and the winning number was a prime: {}, YOU LOSE ${}! You now have ${}\n",
        winningNumber, balanceChange, money);
    return -balanceChange;
}



int main() {

    seed_random();

    int money = rand() % 500 + 501;

    int winningNumber = rand() % 36 + 1;

     string TEST_STRING = "seodpx";

    bool flag = true;
    while (flag) {
        cout << "Welcome to the (Kanga-)Rou-lette Game! You have $" << money << " to start.\n";
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
            cout << "Uh oh! You've gone broke. One of our bouncers will now escort you out. Thanks for losi- Playing!!\n\n";
            flag = false;
        }

    }

    cout << "press any key to exit...";

    _getch();

    return 0;

}