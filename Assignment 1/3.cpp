// Program that plays Higher Lower The Same, a card game, using a custom player of cards - Comp Sci 30 S
// Evan Bartlett

/*
"___________\n"
"|         |\n"
"|  #, ,#  |\n"
"|   :#:   |\n"
"|  #^ ^#  |\n"
"|         |\n"
"^'^*^'^*^'^\n"

"_^*^_+_^*^_\n"
"|         |\n"
"|   %#&   |\n"
"|==#$@$#==|\n"
"|   ?#%   |\n"
"|         |\n"
"^'^*^'^*^'^\n"

"_^*^_+_^*^_\n"
"|         |\n"
"| %>---<& |\n"
"|#   |   #|\n"
"| ?>---<% |\n"
"|         |\n"
"^'^*^'^*^'^\n"

 "_^*^_+_^*^_\n"
 "|    |    |\n"
 "| ####### |\n"
 "|   |#|   |\n"
 "|   |#|   |\n"
"|   \\#/   |\n"
 "^'^*^'^*^'^\n"
*/

#include <iostream>
#include <random>
#include <string>
#include <cmath>
#include <vector>
#include <conio.h>
#include <format>

#define RED "\033[38;2;240;6;10m"
#define BLACK "\033[38;2;132;132;132m"
#define GREEN "\033[38;2;22;233;99m"
#define RESET "\033[0m"

using namespace std;

// given the index of a card in the array, returns the value of the card
// i - the index of the card to be converted to the index of its number
int cardRank(int i) {
    return i % 13;
}

// given the index of a card in the array, returns the suit of the card
// i - the index of the card to be converted to the index of its suit
int cardSuit(int i) {
    return (int)( floor(i / 13) ) % 4;
}

// generates the art for the cards and returns a vector of strings
vector<string> init_card_array() {

    vector<string> cards; // vector to hold the cards

    // Red: Paranormals, Hoaxes, Black: Cryptids, Myths
    string suits[4] = {"P", "H", "C", "M"};

    // 2-10, J, Q, K, A
    string nums[13] = { "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"};

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
                new_card.append("\n___________\n" "| ");
                new_card.append(nums[cardRank(i)]);
                new_card.append("       |\n" "|         |\n" "|  #, ,#  |\n" "|   :#:   |\n" "|  #^ ^#  |\n" "|         |\n" "|       ");
                new_card.append(nums[cardRank(i)]);
                new_card.append(" |\n" "^'^*^'^*^'^\n");
                break;
            }

            case 1: { // hoaxes
                new_card.append("\n___________\n" "| ");
                new_card.append(nums[cardRank(i)]);
                new_card.append("       |\n" "|         |\n" "|   %#&   |\n" "|==#$@$#==|\n" "|   ?#%   |\n" "|         |\n" "|       ");
                new_card.append(nums[cardRank(i)]);
                new_card.append(" |\n" "^'^*^'^*^'^\n");
                break;
            }

            case 2: { // cryptids
                new_card.append("\n___________\n" "| ");
                new_card.append(nums[cardRank(i)]);
                new_card.append("       |\n" "|         |\n" "| %>---<& |\n" "|#   |   #|\n" "| ?>---<% |\n" "|         |\n" "|       ");
                new_card.append(nums[cardRank(i)]);
                new_card.append(" |\n" "^'^*^'^*^'^\n");
                break;
            }

            case 3: { // myths
                new_card.append("\n___________\n" "| ");
                new_card.append(nums[cardRank(i)]);
                new_card.append("       |\n" "|    |    |\n" "| ####### |\n" "|   |#|   |\n" "|   |#|   |\n" "|   \\#/ ");
                new_card.append(nums[cardRank(i)]);
                new_card.append(" |\n" "^'^*^'^*^'^\n");
                break;
            }
        }
        new_card.append(RESET);
        cards.push_back(new_card);
    }
    return cards;
}

// seeds the random number generator using a non-deterministic random number generator
void seed_random() {
    random_device tempDevice;
    srand(tempDevice());
    for (int i = 0; i < tempDevice(); i++) {
        rand();
    }
}

// function to get the input from the user
// test_string is a string of characters that are valid for the user to input
// if the input is not in the test_string than it is discarded
// test_string - list of characters that are valid inputs
char get(const string& test_string) {
    while (true) {
        
        // get the inputted character
        char input = _getch();

        // checks if input matches anything in the test string, returns the char if it's the same
        for (char i: test_string) {
            if (i == input) {
                return input;
            }
        }


    }
}

// Gets a guess from the user, and using the indexes of the old and new card,
// returns a bool for whether they guess correctly
// old_card - the card already displayed
// new_card - the card the user is guessing
bool getGuess(int& old_card, int& new_card) { // old_card: old   index2: new

    // convert indexs to card values
    int old_card_value = old_card % 13;
    int new_card_value = new_card % 13;

    char guess = tolower( get("hlsHLS") ); // gets the user's guess and converts it to lowercase
    
    if (old_card_value == new_card_value && guess == 's') return true; // Cards are the same and user guesses that
    if (old_card_value > new_card_value && guess == 'l') return true; // The card is lower same and user guesses that
    if (old_card_value < new_card_value && guess == 'h') return true; // Cards is higher same and user guesses that
    
    return false; // user guesses wrong
}

// prints the face of the card at the given index
// index - index of the card in the array
// cards - card art to use to display the card
void printCardFace(int index, const vector<string>& cards) {
    cout << cards[index] << endl;
}

// prints the name of the card at the given index
// index - index of the card in the array
// nums - array of card values
// suits - array of card suits
void printName(int index, vector<string> nums, vector<string> suits) {
    if (cardSuit(index) < 2) { cout << RED; } else { cout << BLACK; }

    int number = cardRank(index);
    int suit = cardSuit(index);

    cout << nums[number] << " of " << suits[suit] << RESET;
}

// prints the name of the card at the given index, followed by the face of the card
// new_card - card to be displayed
// nums - array of card values
// suits - array of card suits
// cards - array of card art
void printCard(int new_card, vector<string> nums, vector<string> suits, const vector<string>& cards) {
    printName(new_card, nums, suits);
    cout << "!";
    printCardFace(new_card, cards);
}

// outputs a welcome message and the first card
// new_card - card to be displayed
// nums - array of card values
// suits - array of card suits
// cards - array of card art
void start(int new_card, vector<string> nums, vector<string> suits, const vector<string>& cards) {
    cout << "Welcome to Higher, Lower, or the Same!!!!!!\n Your very first card is..... ";
    printCard(new_card, nums, suits, cards);
}

// asks user if they want to restart, returns a bool for whether they want to restart
// new_card - card to be displayed
// nums - array of card values
// suits - array of card suits
// cards - array of card art
bool askRestart(int new_card, vector<string> nums, vector<string> suits, const vector<string>& cards) {
    cout << "Would you like to play another round? (Y/N) --> ";
    switch(get("yYnN")) { // get and validate input before swtich, no default case needed
        case 'n': case 'N': { // user wants to quit
            return false; // stop while loop
        }
        case 'y': case 'Y': { // user wants to play again
            cout << "\n\n";
            start(new_card, nums, suits, cards);
            return true;
        }
        default:
            return false;
    }
}

// cycles the cards, setting the old card to the new card and generating a new card
// new_card - card to be cycled
// old_card - card to be replaced with the previous new card
void cycleCards(int& new_card, int &old_card) {
    old_card = new_card;
    new_card = rand() % 52;
}

// calculates the average of the total right and the number of rounds
// total_right - number of times the used guessed correctly
// rounds - number of times the user played a round
float calcAvg(float total_right, float rounds) {
    return total_right/rounds;
}

int main() {

    seed_random(); // seed the random number generator

    int score = 0; // current number of correct guesses in a row
    int high_score = 0; // highest streak of correct guesses in a row
    int total_right = 0; // number of times user was correct
    int rounds = 0; // number of rounds played
    int new_card = rand() % 52; // the card the user is guessing
    int old_card = 0; // card displayed on screen when user guesses
    // array 1 contains ace to king, array 2 contains the 4 suits
    vector<string> nums = { "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};
    vector<string> suits = {"Paranormals", "Hoaxes", "Cryptids", "Myths"};

    vector<string> cards = init_card_array(); // generate all the art for the cards
    start(new_card, nums, suits, cards); // output the welcome message and the first card

    bool flag = true; // declare bool variable shift to relavant loop for readability, see: https://google.github.io/styleguide/cppguide.html#Local_Variables
    while (flag) {
        cycleCards(new_card, old_card); // cycle the cards
        cout << "Do think the shift card will be (H)igher, (L)ower, or the (S)ame? --> ";

        if(!getGuess(old_card, new_card)) { // if the user guesses wrong

            cout << "\n\nThe shift card is..........\nThe ";
            printCard(new_card, nums, suits, cards); // print the new card
            cout << RED "OUCH! YOU WERE WRONG. TRY AGAIN NEXT TIME!\n\n" RESET;
            cout << GREEN "FINAL SCORE: " << score << RESET << endl;

            if (score > high_score) { // if the score is higher than the high score, set the high score to the score
                high_score = score;
            }

            total_right += score; // add the score to the total right
            rounds++; // increment the number of rounds
            score = 0; // reset the score
            cycleCards(new_card, old_card); // cycle the cards
            flag = askRestart(new_card, nums, suits, cards); // ask the user if they want to restart
        }
        else { // if the user guesses right

            cout << "\n\nThe shift card is..........\nThe ";
            printCard(new_card, nums, suits, cards); // print the shift card
            score++; // increment the score
            cout << GREEN "Correct!\nYou have gotten " << score << " correct in a row!!\n\n\n" RESET;
        }
        
    }

    cout << "\n\n";

    // output the number of rounds, the average, and the high score
    cout << format(
        GREEN "You played {} rounds, with an average of {} correct answers per round. Your highest score was {} in a row!" RESET,
        rounds, calcAvg(total_right, rounds), high_score
    );

    _getch(); // wait for user input before closing the program
    
    return 0;
}

