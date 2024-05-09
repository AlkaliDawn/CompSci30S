// A slot machine!! more like a not machine, cus it's a program not a machine, im such a silly goose - Comp Sci 30 S
// Evan Bartlett

#include <conio.h>
#include <format>
#include <iostream>
#include <string>
#include <random>
#include <thread>

#define RED "\033[38;2;240;6;10m"
#define GREEN "\033[38;2;22;233;99m"
#define RESET "\033[0m"

using namespace std;

// seeds the random number generator using a non-deterministic random number generator
void seedRandom() {
    random_device tempDevice;
    srand(tempDevice());
    for (int i = 0; i < tempDevice(); i++) {
        rand();
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
// if the input is not in the test_string than it is discarded
// test_string - a string of characters that are valid for the user to input
char get(const string& test_string) {
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
// money - amount of money the user currently has
int askBet(int money) {
    int bet = 1;
    while (true) {
        cout << "What will your bet be? ";

        getNum(bet); // get the user's potential bet

        if (bet > money) {
            cout << "\nBet must not be more than money.\n\n";
            continue;
        }
        if (bet <= 0) {
            cout << "Bet must be greater than 0.\n\n";
            continue;
        }

        // bet is valid

        break;
    }
    return bet;
}

// a, b, and c are abritrary ints representing window states, returns true if two ints are the same
bool twoSame(int a, int b, int c, float& times_two_same) {
    if (a == b || b == c || c == a) {
        times_two_same++;
        return true;
    }
    return false;
}

// a, b, and c are abritrary ints representing window states, returns true if all 3 ints are the same
bool threeSame(int a, int b, int c, float& times_three_same) {
    if (a == b && b == c && a == c) {
        times_three_same++;
        return true;
    }
    return false;
}

int main() {

    seedRandom();

    int money = rand() % 500 + 501; // the amount of money the user has
    int startingMoney = money; // money at the start of the game for telling the user how much they gained / lost
    int overallBalanceChange; // var to calculate change in money from the start
    int bet; // amount the user wants to bet
    int jackpot; // var to calculate the jackpot if they win
    float times_zero_same = 0; // num of times all of the windows were different
    float times_two_same = 0; // number of time two of the three windows were the same
    float times_three_same = 0; // number of time three windows were the same
    float totalGames = 0; // number of games the user played
    string symbols[3] = {"<! I CANT BELIEVE !>", "<! ITS NOT !>", "<! BUTTER :D !>" }; // possible values for the windows
    int column1; // window 1
    int column2; // window 2
    int column3; // window 3
    const string TEST_STRING = "seodpx"; // allowed inputs by the user

    bool flag = true;
    while (flag) {

        column1 = rand() % 3;
        column2 = rand() % 3;
        column3 = rand() % 3;

        cout << "Welcome to the the Scott Machine!! You have $" << money << " to start.\n";

        bet = askBet(money);

        this_thread::sleep_for(std::chrono::milliseconds(1500));

        cout << symbols[column1];

        this_thread::sleep_for(std::chrono::milliseconds(1500));

        cout << symbols[column2];

        this_thread::sleep_for(std::chrono::milliseconds(1500));

        cout << symbols[column3] << endl;

        if (threeSame(column1, column2, column3, times_three_same)) {
            jackpot = bet * 7;
            money += jackpot;
            cout << format(GREEN "All three windows match, you win the ${} (7 * ${}) jackpot and now have ${}!!!\n" RESET, jackpot, bet, money);
        }
        else if (twoSame(column1, column2, column3, times_two_same)) {
            cout << format(GREEN "Two windows match, so you keep your ${} and still have ${}\n" RESET, bet, money);
        }
        else {
            money -= bet;
            cout << format(RED "There are no matches, so you lost ${} and now have ${}\n" RESET, bet, money);
            times_zero_same++;
        }

        totalGames++; // increment number of games played

        if (money <= 0) {
            cout << RED "Uh oh! You've gone broke. One of our bouncers will now escort you out. Thanks for losi- Playing!!\n\n" RESET;
            break;
        }

        cout << "Would you like to play another round? (Y/N) --> ";

        switch(get("yYnN")) { // get and validate input before swtich, no default case needed

            case 'n': case 'N': { // user wants to quit
                flag = false; // stop while loop
                break;
            }
            case 'y': case 'Y': { // user wants to play again
                cout << "\n";
                break;
            }
        }

    }


    // Print final output telling the user their results

    cout << "You played " << totalGames << " game(s) of Slots, and your results were...\n";
    cout << format("3 matches happened {} time(s) ({}%)\n", times_three_same, round(times_three_same * 100 / totalGames));
    cout << format("2 matches happened {} time(s) ({}%)\n", times_two_same, round(times_two_same * 100 / totalGames));
    cout << format("No matches happened {} time(s) ({}%)\n", times_zero_same, round(times_zero_same * 100 / totalGames));

    overallBalanceChange = money - startingMoney; // calculate the change in the users money since they started playing

    if (overallBalanceChange > 0) {
    cout << format("You are leaving with ${}, which means you won ${} since you started - congrats!\n\n", money, abs(overallBalanceChange));
    }
    else if (overallBalanceChange == 0) {
        cout << format("You are leaving with ${}, which means you have not gained or lost any money.\n\n", money, abs(overallBalanceChange));
    }
    else {
        cout << format("You are leaving with ${}, which means you lost ${} since you started - ouch!\n\n", money, abs(overallBalanceChange));
    }

    cout << "press any key to exit...";

    _getch();

    return 0;

}