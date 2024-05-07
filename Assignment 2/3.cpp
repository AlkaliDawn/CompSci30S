
#include <iostream>
#include <conio.h>
#include <random>
#include <format>
#include <algorithm>
#include <thread>

#include "bartlett.h"

using namespace std;

#define RED "\033[38;2;240;6;10m"
#define BLACK "\033[38;2;132;132;132m"
#define BOLD "\033[1m"
#define RESET "\033[0m"
#define GREEN "\033[38;2;0;153;51m"
#define PURPLE "\033[38;2;204;0;255m"

void makeOrder(vector<int>& seated_order, vector<int>& elim_players, int num_players) {
    int num = 0;
    seated_order.clear();
    for (int i = 0; i < num_players;) {
        num = rand() % num_players + 1;
        if (any_of(seated_order.begin(), seated_order.end(), [num](int val) {return val==num;})) {
            continue;
        }
        i++;
        seated_order.push_back(num);
    }
}

int main() {
    seedRandom();

    int numChairs = 0;
    int money = rand() % 500 + 501;
    int bet = 0;
    int guess = 0;
    int num_players = 0;
    int curr_players = 0;
    vector<int> seated_order;
    vector<int> elim_players;


    cout << "Welcome to DMC! (Digital Musical Chairs)\n";
    cout << "How many players are playing (from 2 - 8)?  > ";
    
    numChairs = getNum(2, 8);

    while (true) {
        cout << format("You have ${} - how much do you want 1to bet ($1 to ${})?  > ", money, money);
        bet = getNum(1, money);

        cout << format("Which player do you think will win (1 to {})?  > ", numChairs);
        guess = getNum(1, numChairs);

        for (int i = 1; i < numChairs; i++) {
            curr_players = numChairs - i + 1; // add one to include player that loses
            makeOrder(seated_order, curr_players);
            cout << format("Round {}:\n", i);
            cout << "Players Seated  ";
            for (int j = 0; j < curr_players-1; j++) {
                cout << seated_order[j] << "  ";
                this_thread::sleep_for(850ms);
            }
            cout << format("So player {} is eliminated!\n", seated_order[curr_players-1]);
            cout << "Press any key to continue...\n";
            _getch();
        }
        
        cout << "Do you want to play again?  > ";
        if (get("yn") == 'n') {
            break;
        }
    }
}