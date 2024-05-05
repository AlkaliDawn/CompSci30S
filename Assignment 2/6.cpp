#include <iostream>
#include <random>
#include <format>
#include <thread>
#include "bartlett.h"
#include "player.h"

using namespace std;

void nbGetch(std::atomic<bool>& run)
{
    char buffer;
    
    while (run.load())
    {
        buffer = static_cast<char>(tolower(_getch()));
        if (buffer == 'q') {
            run.store(false);
            return;
        }
    }
}

void sleep(int time) {
    std::this_thread::sleep_for(chrono::duration<int, milli>(time));
}

// given the index of a card in the array, returns the value of the card
string cardRank(int i) {
    string nums[13] = { "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"};
    return nums[i % 13];
}

// given the index of a card in the array, returns the suit of the card
int cardSuit(int i) {
    return (int)( floor(i / 13) ) % 4;
}

int evalCards(const shared_ptr<player>&, const shared_ptr<player>&, pair<int, int>);

vector<string> init_card_array();

int main() {
    
    // Start Initialization
    seed_random();
    
    int roundsPlayed = 1;
    
    char input;
    
    vector<string> card_art = init_card_array();
    
    pair<shared_ptr<player>, shared_ptr<player>> deal2 = player::deal2(card_art);
    
    shared_ptr<player> player1;
    shared_ptr<player> player2;
    
    player1 = std::move(deal2.first);
    player2 = std::move(deal2.second);
    
    vector<int> stack = {};
    pair<int, int> played_cards = {};
    
    bool inInputMode;
    
    cout << "Welcome to War!!! Would you like to play in (I)nput mode or (A)utomatic mode?  > ";
    
    std::atomic<bool> run(true);
    std::thread quitThread;
    
    if (get("ia") == 'i') {
        inInputMode = true;
    } else {
        inInputMode = false;
        quitThread = std::thread(nbGetch, std::ref(run));
    }
    
    cout << PURPLE "\n\nThe battle begins.\n\n" RESET;
    
    while (true) {
        if (!inInputMode) {
            if (!run.load()) {
                quitThread.join();
                break; // while
            }
        }
        
        if (stack.empty()) {// not warring
            cout << "Round " << roundsPlayed << ": \n";
            roundsPlayed++;
        }
        
        if (inInputMode) {
            sleep(300);
            for (int i = 3; i > 0; i--) {
                cout << i << ", ";
                sleep(300);
            }
            
            cout << "Flip!\n";
             // random delay from 0 to 750 ms
            cout << "\nPlayer one plays a " << cardRank(player1->nextCard()) << "...";
            played_cards.first = player1->playCard();
            sleep((rand() % 350)); // random delay from 0 to 750 ms
            cout << "\nPlayer two plays a " << cardRank(player2->nextCard()) << "...";
            played_cards.second = player2->playCard();
            sleep(300);
        }
        else {
            played_cards.first = player1->playCard();
            played_cards.second = player2->playCard();
        }
        
        
        switch (evalCards(player1, player2, played_cards)) {
            case 1: { // player 1 wins
                cout << format("Player one wins the round! Their {0} is higher than player two's {1}.\n\n",
                               cardRank(played_cards.first), cardRank(played_cards.second));
                cout << format("Player one now has {} cards.\nPlayer two now has {} cards.\n",
                               player1->numCards(), player2->numCards());
                break;
            }
            case 2: {
                cout << format("Player two wins the round! Their {1} is higher than player one's {0}.\n\n",
                               cardRank(played_cards.first), cardRank(played_cards.second));
                cout << format("Player one now has {} cards.\nPlayer two now has {} cards.\n",
                               player1->numCards(), player2->numCards());
                break;
            }
            case 0: {
                cout << format(
                        "And it's a tie!! Both players flipped a {}! They both get their card back.\n",
                        cardRank(played_cards.first));
                break;
            }
        }
        if (inInputMode) {
            cout << "\nPress 'C' continue or press 'Q' to quit!\n";
            if (get("cq") == 'q') {
                cout << "Thanks for playing!";
                break; // while
            }
        } else {
            cout << "\nPress 'Q' at anytime to quit!\n";
            sleep(1050);
        }
    }
    
    cout << "Thank you for playing!";
    
    _getch();
    return 0;
} // MAIN END


int evalCards(const shared_ptr<player>& p1, const shared_ptr<player>& p2, pair<int, int> played_cards) {
    if (cardRank(played_cards.first) > cardRank(played_cards.second)) { // player 1 wins
        p1->addBottom({played_cards.first, played_cards.second});
        return 1;
    }
    else if (cardRank(played_cards.first) < cardRank(played_cards.second)) { // player 2 wins
        p2->addBottom({played_cards.first, played_cards.second});
        return 2;
    }
    else {
        p1->addBottom({played_cards.first});
        p2->addBottom({played_cards.second});
        return 0;
    }
}

// INIT CARD ARRAY BEGIN ----------------------------------------------------------------------------------------------
vector<string> init_card_array() {

    vector<string> cards; // vector to hold the cards

    for (int i = 0; i < 52; i++) { // for every card in the player

        string new_card; // temporary string to hold the card

        if (cardSuit(i) < 2 ) { // if the suit is a paranormal or a hoax, make the card red
            new_card.append(RED);
        }

        else { // if the suit is a cryptid or a myth, make the card black
            new_card.append(BLACK);
        }

        switch (cardSuit(i)) { // switch on the suit of the card
            case 0: { // paranormals
                new_card.append(format(
                        "\n,,,,,,,,,,,\n"
                        "| {0}       |\n"
                        "|         |\n"
                        "|  #, ,#  |\n"
                        "|   :#:   |\n"
                        "|  #^ ^#  |\n"
                        "|         |\n"
                        "|       {0} |\n"
                        "'''''''''''\n", cardRank(i)));
                break;
            }
            
            case 1: { // hoaxes
                new_card.append(format(
                        "\n,,,,,,,,,,,\n"
                        "| {0}       |\n"
                        "|         |\n"
                        "|   %#&   |\n"
                        "|==#$@$#==|\n"
                        "|   ?#%   |\n"
                        "|         |\n"
                        "|       {0} |\n"
                        "'''''''''''\n", cardRank(i)));
                break;
            }
            
            case 2: { // cryptids
                new_card.append(format(
                        "\n,,,,,,,,,,,\n"
                        "| {0}       |\n"
                        "|         |\n"
                        "| %>---<& |\n"
                        "|#   |   #|\n"
                        "| ?>---<% |\n"
                        "|         |\n"
                        "|       {0} |\n"
                        "'''''''''''\n", cardRank(i)));
                break;
            }
            
            case 3: { // myths
                new_card.append(format(
                         "\n,,,,,,,,,,,\n"
                           "| {0}       |\n"
                           "|    |    |\n"
                           "| ####### |\n"
                           "|   |#|   |\n"
                           "|   |#|   |\n"
                          "|   \\#/   |\n"
                           "|       {0} |\n"
                           "'''''''''''\n", cardRank(i)));
                break;
            }
        }
        new_card.append(RESET);
        cards.push_back(new_card);
    }
    return cards;
} // INIT CARD ARRAY()