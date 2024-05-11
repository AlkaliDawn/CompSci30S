
#include <iostream>
#include <conio.h>
#include <random>
#include <format>
#include <algorithm>
#include <thread>

#include "bartlett.h"

using namespace std;
// fills seated order with array indexes to players in the player array
// seatedOrder will be filled with indexes corresponding to players
// players is the list of players still in the running
void makeOrder(vector<int> & seatedOrder, vector<int> & players) {
    int num = 0;
    seatedOrder.clear();
    for (int i = 0; i < players.size();) {
        num = rand() % players.size();
        
        // if the num is already in seated order, generate a new one
        if (any_of(seatedOrder.begin(), seatedOrder.end(), [num](int val) { return val == num; })) {
            continue;
        }
        
        // only iterate if num is new and not yet in seated order
        i++;
        
        // add the num to seated order
        seatedOrder.push_back(num);
    }
}

void init(vector<int> & players, int numPlayers) {
    if (!players.empty()) {
        players.clear();
    }
    for (int i = 1; i <= numPlayers; i++) {
        players.push_back(i);
    }
}

int main() {
    seedRandom();
    
    int numChairs = 0;
    int money = rand() % 500 + 501;
    int bet = 0;
    int guess = 0;
    vector<int> seatedOrder;
    vector<int> players;
    vector<string> colors = {LIME, PASTEL_BLUE, YELLOW, ORANGE, PINK, TEAL, PURPLE, BLUE};
    
    cout << "Welcome to DMC! (Digital Musical Chairs)\n";
    cout << "How many players are playing (from 2 - 8)?  > ";
    
    numChairs = getNum(2, 8);
    
    init(players, numChairs);
    
    while (true) {
        cout << format("You have ${} - how much do you want to bet ($1 to ${})?  > $", money, money);
        bet = getNum(1, money);
        
        cout << format("Which player do you think will win (1 to {})?  > ", numChairs);
        guess = getNum(1, numChairs);
        
        for (int i = 1; i < numChairs; i++) {
            makeOrder(seatedOrder, players);
            cout << format("Round {}:\n", i);
            cout << "Players Seated  ";
            for (int j = 0; j < seatedOrder.size() - 1; j++) {
                cout << colors[players[seatedOrder[j]] - 1];
                cout << players[seatedOrder[j]] << "    ";
                cout << RESET;
                this_thread::sleep_for(550ms);
            }
            cout << format("So player {}{}" RESET " is eliminated!\n", colors[seatedOrder.back()], players[seatedOrder.back()]);
            players.erase(players.begin() + seatedOrder.back());
            cout << "Press any key to continue...\n";
            _getch();
        }
        if (guess == players.front()) {
            money += bet * (numChairs - 1);
            cout << format(GREEN BOLD "PLAYER {} WAS THE WINNER, so you win ${} ( ${} * ( {} - 1 ) ) and now have ${}.\n" RESET, players.front(), bet * (numChairs - 1), bet, numChairs, money);
        }
        else {
            money -= bet;
            cout << format(RED BOLD "PLAYER {} WAS THE WINNER, so you lose ${} and now have ${}.\n" RESET, players.front(), bet, money);
        }
        if (money < 1) {
            cout << "YOU WENT BANKRUPT!! THANKS FOR PLAYING.";
            return 0;
        }
        cout << "Do you want to play again? (Y/N) > ";
        if (get("yn") == 'n') {
            return 0;
        }
        init(players, numChairs);
    }
    return 0;
}