// Higher lower the same

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

// #include statements: random for generating cards, string for visuals, cmath for floor
// vector for names, suites, and cards, conio for getch, algorithm for input
#include <iostream>
#include <random>
#include <string>
#include <cmath>
#include <vector>
#include <conio.h>
#include <algorithm>

#define RED "\033[38;2;240;6;10m"
#define BLACK "\033[38;2;132;132;132m"
#define RESET "\033[0m"

using namespace std;

int numFromIndex(auto i) {
    return i % 13;
}

/** @param i  The card index to be used
 * @return  Index to the card's suit in the array of suits
 *
 *  Function that given a card index, returns the index to the index to its suit in the array of suits
 */
int suitFromIndex(const int i) {
    return static_cast<int>( floor(i / 13) ) % 4;
}

constexpr void init_card_array(vector<string> &cards) {

    // Red: Paranormals, Hoaxes, Black: Cryptids, Myths
    const string suits[4] = {"P", "H", "C", "M"};

    // ace to king
    const string nums[13] = { "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K", "A"};

    for (int i = 0; i < 52; i++) {

        string new_card; // temporary string to hold the card

        if (suitFromIndex(i) < 2 ) {
            new_card.append(RED);
        }

        else {
            new_card.append(BLACK);
        }

        switch (suitFromIndex(i)) {
            case 0: { // paranormals
                new_card.append("\n___________\n" "| ");
                new_card.append(nums[numFromIndex(i)]);
                new_card.append("       |\n" "|         |\n" "|  #, ,#  |\n" "|   :#:   |\n" "|  #^ ^#  |\n" "|         |\n" "|       ");
                new_card.append(nums[numFromIndex(i)]);
                new_card.append(" |\n" "^'^*^'^*^'^\n");
                break;
            }

            case 1: { // hoaxes
                new_card.append("\n___________\n" "| ");
                new_card.append(nums[numFromIndex(i)]);
                new_card.append("       |\n" "|         |\n" "|   %#&   |\n" "|==#$@$#==|\n" "|   ?#%   |\n" "|         |\n" "|       ");
                new_card.append(nums[numFromIndex(i)]);
                new_card.append(" |\n" "^'^*^'^*^'^\n");
                break;
            }

            case 2: { // cryptids
                new_card.append("\n___________\n" "| ");
                new_card.append(nums[numFromIndex(i)]);
                new_card.append("       |\n" "|         |\n" "| %>---<& |\n" "|#   |   #|\n" "| ?>---<% |\n" "|         |\n" "|       ");
                new_card.append(nums[numFromIndex(i)]);
                new_card.append(" |\n" "^'^*^'^*^'^\n");
                break;
            }

            case 3: { // myths
                new_card.append("\n___________\n" "| ");
                new_card.append(nums[numFromIndex(i)]);
                new_card.append("       |\n" "|    |    |\n" "| ####### |\n" "|   |#|   |\n" "|   |#|   |\n" "|   \\#/ ");
                new_card.append(nums[numFromIndex(i)]);
                new_card.append(" |\n" "^'^*^'^*^'^\n");
                break;
            }

            default:
                {

                }
        }
        new_card.append(RESET);
        cards.push_back(new_card);
    }
}

// seeds the random number generator using a non-deterministic random number generator
void seed_random() {
    random_device rd;
    srand(rd());
    for (int i = 0; i < rd(); i++) {
        rand();
    }
}


char get(const string& test_string) {
    while (true) {
        
        // get the inputted character
        char input = _getch();

        auto test_func = [input](const char current_char) { return current_char == input; };

        // for each character in the string, check if the input is the same, if a match is found input is returned, otherwise it waits for another input
        if (ranges::any_of(test_string.begin(), test_string.end(), test_func)) {
            cout << input << "\n";
            return input;
        }
    }
}

// GET GUESS
// Gets a guess from the user, and using the indexes of the old and new card,
// return a bool for whether they guess correctly
bool getGuess(const int& old_card, const int& new_card) { // old_card: old   index2: new
    // convert index to card value
    const int old_card_value = old_card % 13;
    const int new_card_value = new_card % 13;

    const char guess = tolower( get("hlsHLS") );
    
    if (old_card_value == new_card_value && guess == 's') return true; // Cards are the same and user guesses that
    if (old_card_value < new_card_value && guess == 'l') return true; // The card is lower same and user guesses that
    if (old_card_value > new_card_value && guess == 'h') return true; // Cards is higher same and user guesses that
    
    return false;
}

void printCardFace(const int index, const vector<string>& cards) {
    cout << cards[index] << endl;
}

void printName(const int index, vector<string> names[2]) {
    if (numFromIndex(index) < 2) { cout << RED; } else { cout << BLACK; }
    cout << names[0][numFromIndex(index)] << " of " << names[1][suitFromIndex(index)] << RESET;
}

void printCard(const int new_card, vector<string> names[2], const vector<string>& cards) {
    printName(new_card, names);
    cout << "!";
    printCardFace(new_card, cards);
}

void start(const int new_card, vector<string> names[2], const vector<string>& cards) {
    cout << "Welcome to Higher, Lower, or the Same!!!!!!\n Your very first card is..... ";
    printCard(new_card, names, cards);
}

// asks user if they want to restart, sets boolean flags accordingly
bool askRestart(const int new_card, vector<string> names[2], const vector<string>& cards) {
    
    cout << "Would you like to play another round? (Y/N) --> ";
    
    switch(get("yYnN")) { // get and validate input before swtich, no default case needed
        
        case 'n': case 'N': { // user wants to quit
            return false; // stop while loop
        }
        case 'y': case 'Y': { // user wants to play again
            cout << "\n\n\n";
            start(new_card, names, cards);
            return true;
        }
        default:
            return false;
    }
}

void printLoss(int &score) {
    cout << "OUCH! YOU WERE WRONG. TRY AGAIN NEXT TIME!\n\n";
    cout << "FINAL SCORE: " << score << endl;
    score = 0;
}

void cycleCards(int& new_card, int &old_card) {
    old_card = new_card;
    new_card = rand() % 52;
}

void nextCard() {
    cout << "\n\nThe next card is..........\nThe ";
}

int main() {
    
    seed_random();
    
    int score = 0;
    
    vector<string> cards; // stores ascii art cards

    int new_card = rand() % 52;
    int old_card = 0;
    
    // vector 1 contains ace to king, vector 2 contains the 4 suits
    vector<string> names[2] = {
            { "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"},
            {"Paranormals", "Hoaxes", "Cryptids", "Myths"}
    };
    
    init_card_array(cards); // generate all the art for the cards
    
    start(new_card, names, cards);
    
    bool flag = true; // declare bool variable next to relavant loop for readability
    while (flag) {
        
        cycleCards(new_card, old_card);
        
        cout << "Do think the next card will be (H)igher, (L)ower, or the (S)ame? --> ";
        
        if(getGuess(old_card, new_card)) {
            nextCard();
            printCard(new_card, names, cards);
            printLoss(score);
            flag = askRestart(new_card, names, cards);
        }
        else {
            nextCard();
            printCard(new_card, names, cards);
            score++;
            cout << "Correct!\nYou have gotten " << score << " correct in a row!!\n\n\n";
        }
        
    }
    
    return 0;
}

