// Higher lower the same

/*
 * example card:
"\n___________\n"
"|         |\n"
"|         |\n"
"|         |\n"
"|_________|\n"
 */

#include <iostream>
#include <random>
#include <string>
#include <cmath>
#include <vector>
#include <conio.h>
#include <algorithm>
#include <unordered_map>


using namespace std;

void init_card_array(vector<string> &cards) {
    string suits[4] = {"S", "H", "C", "D"}; // Spade, Heart, Club, Diamond
    // ace to king
    string nums[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K"};
    for (int i = 0; i < 52; i++) {
        string new_card = "";
        new_card.append("\n___________\n| ");
        new_card.append(nums[ (int) i % 13 ]);
        new_card.append(suits[ (int) floor(i / 13) % 4 ]);
        new_card.append(      "      |\n"
                             "|         |\n"
                             "|         |\n"
                             "|_________|\n");
        cards.push_back(new_card);
    }
}

// HIGHER LOWER SAME
// checks if two cards are the same based on their index in the card array, -1 for low, 0 for same, 1 for high
int hls(int old_card, int new_card) { // old_card: old   index2: new
    // convert index to card value
    old_card %= 13;
    new_card %= 13;
    
    if (old_card == new_card) return 0;
    if (old_card < new_card) return 1;
    if (old_card > new_card) return -1;
}

// seeds the random number generator using a non-deterministic random number generator
random_device seed_random() {
    random_device rd;
    srand(rd());
    for (int i = 0; i < rd(); i++) {
        rand();
    }
}


char get(string test_string) {
    while (true) {
        
        // get the inputted character
        char input = getch();
        
        // for each character in the string, check if the input is the same, if a match is found input is returned, otherwise it waits for another input
        if (std::any_of(test_string.begin(), test_string.end(), [input](char current_char) { return current_char == input; })) {
            cout << input << "\n";
            return input;
        }
    }
}

void printCardFace(int index, vector<string> cards) {
    cout << cards[index] << endl;
}

void printName(int index, vector<string> names[2]) {
    cout << names[0][ (int) index % 13 ] << " of " << names[1][(int) floor(index / 13) % 4];
}

void printCard(int new_card, vector<string> names[2], vector<string> cards) {
    printName(new_card, names);
    cout << "!";
    printCardFace(new_card, cards);
}

int main() {
    
    seed_random();
    
    int score = 0;
    
    vector<string> cards; // stores ascii art cards
    int new_card = rand() % 52;
    int old_card = 0;
    
    unordered_map<char, int> key = {
            {'h',1},
            {'l', -1},
            {'s', 0},
            {'H',1},
            {'L', -1},
            {'S', 0}
    };
    
    // vector 1 contains ace to king, vector 2 contains the 4 suits
    vector<string> names[2] = {
            {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"},
            {"Spades", "Hearts", "Clubs", "Diamonds"}
    };
    
    init_card_array(cards); // generate all the art for the cards
    
    
    bool start = true;
    bool flag = true;
    while (flag) {
        
         if (start) {
             cout << "Welcome to Higher Lower Or The Same!\nThe first card is the " ;
             printCard(new_card, names, cards);
             start = false;
         }
         
        old_card = new_card;
        new_card = rand() % 52;
        
        cout << "Do think the next card will be (H)igher, (L)ower, or the (S)ame? --> ";
        
        if(key[get("hlsHLS")] != hls(old_card, new_card)) {
            cout << "\n\nThe next card is..........\nThe ";
            printCard(new_card, names, cards);
            cout << "OUCH! YOU WERE WRONG. TRY AGAIN NEXT TIME!\n\n";
            cout << "FINAL SCORE: " << score << endl;
            score = 0;
    
            cout << "Would you like to (C)ontinue, or E(x)it? --> ";
            switch(get("cCxX")) {
        
                case 'x':
                case 'X': {
                    flag = false;
                    break;
                }
                case 'c':
                case 'C': {
                    cout << "\n\n\n\n\n\n";
                    start = true;
                    break;
                }
        
            }
            
        }
        else {
            cout << "The next card is..........\nThe ";
            printCard(new_card, names, cards);
            score++;
            cout << "Correct!\nYour new score is: " << score << "\n\n\n";
        }
        
    }
    
    return 0;
}

