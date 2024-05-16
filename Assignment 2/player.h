#include <iostream>
#include <conio.h>
#include <random>
#include <array>
#include <memory>
#include <algorithm>

#ifndef COMPSCI30S_PLAYER_H
#define COMPSCI30S_PLAYER_H

#endif //COMPSCI30S_PLAYER_H

using namespace std;

class player {
public:
    explicit player(vector<string> cardsUI) {
        this->cardsUI = std::move(cardsUI); // recieve the card art
    }
    
    // makes two player objects and splits the deck randomly and evenly between them, then returns shared pointers to the players in a pair obj
    static pair<shared_ptr<player>,  shared_ptr<player>> deal2(vector<string> cardsUI);
    
    // plays the face of the card at the top of the pile (front of the array)
    // prints the card, returns the card played, and removes it from the pile
    int playCard();
    
    // same as playCard but without printing the card
    int takeCard();
    
    // returns the index of the last real card in the array (last non sentry value)
    int lastCard();
    
    // wrapper function, returns the card at the top of the deck and does no further operations
    int nextCard();
    
    // adds cards on to the bottom of the pile
    // replaces first -1 values with values of stack, then clears stack
    void addBottom(vector<int>&& stack);
    
    // returns the number of cards the player has
    int numCards();
    
    void shift();
    
private:
    vector<string> cardsUI;
    array<int, 52> cards{};
};

int player::numCards() {
    for (int i = 0; i < 52; i++) {
        if (this -> cards[i] == -1) {
            return i;
        }
    }
    return -1;
}

int player::lastCard() {
    for (int i = 0; i < 52; i++) {
        if (this -> cards[i] == -1) {
            return i - 1;
        }
    }
    return -1;
}

pair<shared_ptr<player>,  shared_ptr<player>> player::deal2(vector<string> cardsUI) {
    array<bool, 52> taken{};
    taken.fill(true);
    shared_ptr<player> player1 = make_shared<player>(cardsUI);
    shared_ptr<player> player2 = make_shared<player>(cardsUI);
    
    for (int i = 0; i < 52; i++) {
        player1->cards[i] = -1;
        player2->cards[i] = -1;
    }

    for (int i = 0; i < 52; ) {
        const int rand_num = rand() % 52;
        if (!taken[rand_num]) {
            continue;
        } else {
            i++;
            if (i % 2) {
                player1->cards[i / 2] = rand_num;
            } else {
                player2->cards[(i - 1) / 2] = rand_num;
            }
            taken[rand_num] = false;
        }
        if (std::none_of(taken.begin(), taken.end(), [](bool i) { return i; })) {
            break;
        }
    }
    return make_pair<shared_ptr<player>, shared_ptr<player>>(std::move(player1), std::move(player2));
}

int player::playCard() {
    int card = cards[0];
    cout << cardsUI[card];
    cards[0] = -1;
    shift();
    return card;
}

void player::shift() {
    if (cards[0] != -1) {
        return;
    }
    for (int i = 0; i < 51; i++) {
        if (i != 0 && cards[i] == -1) {
            return;
        }
        cards[i] = cards[i+1];
    }
}

void player::addBottom(vector<int>&& stack) {
    int first_empty = lastCard() + 1;
    for (int i = 0; i < stack.size(); i++) {
        cards[first_empty + i] = stack[i]; // stack will be placed from top to bottom on the bottom of the deck. Changing this will change the outcome of the game, but provides no advantage to either side as long as it is constant between the two players
    }
}

int player::nextCard() {
    return cards[0];
}

int player::takeCard() {
    int card = cards[0];
    cards[0] = -1;
    shift();
    return card;
}
