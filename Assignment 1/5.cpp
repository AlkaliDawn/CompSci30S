
#include <conio.h>
#include <format>
#include <iostream>
#include <string>
#include <random>
#include <thread>

using namespace std;

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
void getNum(T &input) {
    while (!(cin >> input)) {
        cout << "Please enter numbers only." << endl;
        cin.clear();
        cin.ignore(10000,'\n');
    }
}

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

int askBet(int money) {
    int bet = 1;
    while (true) {
        cout << "What will your bet be? ";

        getNum(bet);

        if (bet > money) {
            cout << "\nBet must not be more than money.\n\n";
            continue;
        }
        if (bet <= 0) {
            cout << "Bet must be greater than 0.\n\n";
            continue;
        }
        break;
    }
    return bet;
}

bool twoSame(int a, int b, int c, float& times_two_same) { // abstract variable names as they don't matter
    if (a == b || b == c || c == a) {
        times_two_same++;
        return true;
    }
    return false;
}

bool threeSame(int a, int b, int c, float& times_three_same) { // abstract variable names as they don't matter
    if (a == b && b == c && a == c) {
        times_three_same++;
        return true;
    }
    return false;
}

int main() {

    seed_random();

    int money = rand() % 500 + 501;
    int startingMoney = money;

    int overallBalanceChange;

    int bet;

    int jackpot;

    float times_zero_same = 0;
    float times_two_same = 0;
    float times_three_same = 0;



    float totalGames = 0;

    string wonOrLost;
    string congratsOrNot;

    string symbols[3] = {"<! I CANT BELIEVE !>", "<! ITS NOT !>", "<! BUTTER :D !>" };

    int column1 = rand() % 3;
    int column2 = rand() % 3;
    int column3 = rand() % 3;

    const string TEST_STRING = "seodpx";

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
            cout << format("All three windows match, you win the ${} (7 * ${}) jackpot and now have ${}!!!\n", jackpot, bet, money);
        }
        else if (twoSame(column1, column2, column3, times_two_same)) {
            cout << format("Two windows match, so you keep your ${} and still have ${}\n", bet, money);
        }
        else {
            money -= bet;
            cout << format("There are no matches, so you lost ${} and now have ${}\n", bet, money);
            times_zero_same++;
        }

        totalGames++;

        if (money <= 0) {
            cout << "Uh oh! You've gone broke. One of our bouncers will now escort you out. Thanks for losi- Playing!!\n\n";
            flag = false;
        }

        cout << "Would you like to play another round? (Y/N) --> ";

        switch(get("yYnN")) { // get and validate input before swtich, no default case needed

            case 'n': case 'N': { // user wants to quit
                flag = false; // stop while loop
            }
            case 'y': case 'Y': { // user wants to play again
                cout << "\n";
            }
        }

    }

    cout << "You played " << totalGames << " game(s) of Slots, and your results were...\n";
    cout << format("3 matches happened {} time(s) ({}%)\n", times_three_same, round(times_three_same * 100 / totalGames));
    cout << format("2 matches happened {} time(s) ({}%)\n", times_two_same, round(times_two_same * 100 / totalGames));
    cout << format("No matches happened {} time(s) ({}%)\n", times_zero_same, round(times_zero_same * 100 / totalGames));

    overallBalanceChange = money - startingMoney;
    wonOrLost = (overallBalanceChange > 0 ? "won" : "lost");
    congratsOrNot = (overallBalanceChange > 0? "  - congrats!" : "");
    cout << format("You are leaving with ${}, which means you {} ${} since you started{}\n\n", money, wonOrLost, abs(overallBalanceChange), congratsOrNot);


    cout << "press any key to exit...";

    _getch();

    return 0;

}