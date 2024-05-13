#include <iostream>
#include <random>
#include <format>
#include "bartlett.h"
#include "player.h"

using namespace std;

int evalCards(const shared_ptr<player>& p1, const shared_ptr<player>& p2, pair<int, int> playedCards);

int main() {
    
    int roundsPlayed = 1; // keeps track of how many rounds were played
    int maxRounds = 0; // how many rounds to play in auto mode
    pair<int, int> playedCards = {}; // stores played cards
    bool inInputMode; // determines whether certain parts of the code are silent or have delays based on whether user plays in input or auto mode
    
    const vector<string> card_art = initCardArray();
    
    pair<shared_ptr<player>, shared_ptr<player>> deal2 = player::deal2(card_art); // split deck between two players
    
    const shared_ptr<player> player1 = std::move(deal2.first); // get the player object for player 1
    const shared_ptr<player> player2 = std::move(deal2.second);// get the player object for player 2
    
    seedRandom();
    
    cout << "Welcome to War!!! Would you like to play in (I)nput mode or (A)utomatic mode?  > ";
    
    inInputMode = get("ia") == 'i';
    
    if (!inInputMode) {
        cout << "How many rounds do you want to play?  ";
        maxRounds = getNum(1);
    }
    
    cout << PURPLE "\n\nThe battle begins.\n\n" RESET;
    
    while (true) {
        if (inInputMode) {
            cout << "Round " << roundsPlayed << ": \n";
        }
        else {
            if (roundsPlayed > maxRounds) { // if past the max number of rounds, exit the loop
                cout << format("After {} rounds, Player one has {} cards, and Player two has {} cards!!\n",
                               maxRounds, player1->numCards(), player2->numCards());
                break;
            }
        }
        
        if (player1->numCards() == 52) {
            cout << "Player 1 Got all 52 cards, and wins!!\n";
            break;
        }
        
        if (player2->numCards() == 52) {
            cout << "Player 2 Got all 52 cards, and wins!!\n";
            break;
        }
        
        roundsPlayed++;
        
        if (inInputMode) { // add decorative delays to simulate people actually playing the game
            sleep(300);
            for (int i = 3; i > 0; i--) {
                cout << i << ", ";
                sleep(300);
            }
            
            cout << "Flip!\n";
            sleep((rand() % 350));// random delay from 0 to 350 ms
            cout << "\nPlayer one plays a " << cardRank(player1->nextCard()) << "..."; // player1 plays a card
            playedCards.first = player1->playCard();
            sleep((rand() % 350)); // random delay from 0 to 350 ms
            cout << "\nPlayer two plays a " << cardRank(player2->nextCard()) << "..."; // player2 plays a card
            playedCards.second = player2->playCard();
            sleep(300);
        }
        else { // remove delay
            cout << "\nPlayer one plays a " << cardRank(player1->nextCard()) << "...";
            playedCards.first = player1->playCard();
            cout << "\nPlayer two plays a " << cardRank(player2->nextCard()) << "...";
            playedCards.second = player2->playCard();
        }
        
        if (inInputMode) { // output results and update user on each players card counts
            switch (evalCards(player1, player2, playedCards)) {
                case 1: { // player 1 wins
                    cout << format("Player one wins the round! Their {0} is higher than player two's {1}.\n\n",
                                   cardRank(playedCards.first), cardRank(playedCards.second));
                    break;
                }
                case 2: { // player 2 wins
                    cout << format("Player two wins the round! Their {1} is higher than player one's {0}.\n\n",
                                   cardRank(playedCards.first), cardRank(playedCards.second));
                    break;
                }
                case 0: { // tie
                    cout << format("And it's a tie!! Both players flipped a {}! They both get their card back.\n",
                                   cardRank(playedCards.first));
                    break;
                }
            }
            cout << format("Player one now has {} cards.\nPlayer two now has {} cards.\n",
                           player1->numCards(), player2->numCards());
        }
        else { // eval cards silently
            evalCards(player1, player2, playedCards);
        }
        
        if (inInputMode) { // prompt user if they want to continue
            cout << "\nPress 'C' continue or press 'Q' to quit!\n";
            if (get("cq") == 'q') {
                break; // while
            }
        }
    }
    
    cout << "Thank you for playing!";
    
    _getch();
    return 0;
} // MAIN END


/**
 * @brief main logic of the battles, finds who wins and gives them both cards, or in the case of war, gives each player their card back
 *
 * @param p1 player object containing player1's hand
 * @param p2 player object containing player2's hand
 * @param playedCards the cards both players just played
 * @return 0 if it is a tie, 1 if player 1 wins, 2 if player 2 wins
 */
int evalCards(const shared_ptr<player>& p1, const shared_ptr<player>& p2, pair<int, int> playedCards) {
    if (cardRank(playedCards.first) > cardRank(playedCards.second)) { // player 1 wins
        p1->addBottom({playedCards.first, playedCards.second}); // give player 1 both cards
        return 1;
    }
    else if (cardRank(playedCards.first) < cardRank(playedCards.second)) { // player 2 wins
        p2->addBottom({playedCards.first, playedCards.second}); // give player 2 both cards
        return 2;
    }
    else { // tie, return cards to each player
        p1->addBottom({playedCards.first});
        p2->addBottom({playedCards.second});
        return 0;
    }
}
