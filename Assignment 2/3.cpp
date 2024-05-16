
#include <iostream>
#include <conio.h>
#include <random>
#include <format>
#include <algorithm>
#include <thread>

#include "bartlett.h"

using namespace std;

/**
 * @brief fills seated order with array indexes to players in the player array
 * @param seatedOrder will be filled with indexes corresponding to players
 * @param players list of players still in the running
 */
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
/**
 *
 * @param players array of players to initialize
 * @param numPlayers the numbers of players playing musical chairs
 */
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
    
    int money = rand() % 500 + 501; // starting amount of money for the user
    int bet = 0; // user's current bet
    int guess = 0; // player the user thinks will win
    vector<int> seatedOrder; // array to store the order that players manage to sit down in
    vector<int> players; // list of players in the running
    vector<string> colors = {LIME, PASTEL_BLUE, YELLOW, ORANGE, PINK, TEAL, PURPLE, BLUE};
    
    cout << "Welcome to DMC! (Digital Musical Chairs)\n";
    cout << "How many players are playing (from 2 - 8)?  > ";
    
    const int num_chairs = getNum(2, 8);
    
    while (true) {
        init(players, num_chairs);
        cout << format("You have ${} - how much do you want to bet ($1 to ${})?  > $", money, money);
        bet = getNum(1, money);
        
        cout << format("Which player do you think will win (1 to {})?  > ", num_chairs);
        guess = getNum(1, num_chairs);
        
        for (int i = 1; i < num_chairs; i++) { // play out a number of rounds one less than the number of players playing in total, as one player survives at the end
            makeOrder(seatedOrder, players); // find the order players sit down in
            cout << format("Round {}:\n", i);
            cout << "Players Seated  ";
            for (int j = 0; j < seatedOrder.size() - 1; j++) { // each player is outputted
                cout << colors[players[seatedOrder[j]] - 1];
                cout << players[seatedOrder[j]] << "    ";
                cout << RESET;
                this_thread::sleep_for(550ms);
            }
            // one player is eliminated
            cout << format("So player {}{}" RESET " is eliminated!\n", colors[seatedOrder.back()], players[seatedOrder.back()]);
            players.erase(players.begin() + seatedOrder.back());
            cout << "Press any key to continue...\n";
            _getch();
        }
        if (guess == players.front()) { // user guessed right
            money += bet * (num_chairs - 1);
            cout << format(GREEN BOLD "PLAYER {} WAS THE WINNER, so you win ${} ( ${} * ( {} - 1 ) ) and now have ${}.\n" RESET, players.front(), bet * (num_chairs - 1), bet, num_chairs, money);
        }
        else { // user guessed wrong
            money -= bet;
            cout << format(RED BOLD "PLAYER {} WAS THE WINNER, so you lose ${} and now have ${}.\n" RESET, players.front(), bet, money);
        }
        if (money < 1) { // user went bankrupt
            cout << "YOU WENT BANKRUPT!! THANKS FOR PLAYING.";
            return 0;
        }
        cout << "Do you want to play again? (Y/N) > ";
        if (get("yn") == 'n') {
            return 0;
        }
    }
    return 0;
}