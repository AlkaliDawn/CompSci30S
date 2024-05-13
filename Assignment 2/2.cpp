#include <iostream>
#include <conio.h>
#include <random>
#include <format>
#include <algorithm>

#include "bartlett.h"

using namespace std;

using vi = vector<int>;

/**
 *
 * @param num the number to find the factors of
 * @return an array of all the unique factors of the input num
 */
vi factor(const int num) {
    vi factors;
    for (int i = 1; i < num / 2; i++) {
        if ((num / i) * i == num) {
            if (i != 1 && i == factors[factors.size() - 1]) { // prevent duplicating factors
                break;
            }
            if (i == num / i) {
                factors.push_back(i);
                break;
            }
            factors.push_back(i);
            factors.push_back(num / i);
            
        }
    }
    return factors;
}

/**
 *
 * @param arr the board array
 * @param boardSize the largest number to put the array
 */
void initArr(vi & arr, int boardSize) {
    for (int i = 0; i < boardSize; i++) {
        arr.push_back(i + 1);
    }
}

/**
 * @brief prints the main game board and a border around it
 * @param board the board to be printed
 */
void printBoard(const vi & board) {
    
    // ASCII VALUE CONSTANTS
    const unsigned char top_left = 201;
    const unsigned char horizontal = 205;
    const unsigned char top_right = 187;
    const unsigned char vertical = 186;
    const unsigned char bottom_left = 200;
    const unsigned char bottom_right = 188;
    
    const int padding = 5; // AMT OF PADDING ON RIGHT AND LEFT OF ROWS
    const int board_spaces = min(9, static_cast<int>(board.size()) - 1); // HOW MANY SPOTS THERE ENDS UP BEING BETWEEN TWO NUMBERS
    const int space_size = 3; // THE SIZE OF EACH BOARD SPACE
    const int width = min(10, static_cast<int>(board.size())); // AMT OF NUMS PLACED IN EACH ROW
    
    const int high_digits = max(ceil(log10(static_cast<double>(board.size()))), 1.0); // NUMBER OF DIGITS IN THE HIGHEST NUMBER IN THE GRID
    
    int numTop = (space_size * board_spaces + width * high_digits + padding * 2); // Number of characters at the top and bottom of the grid, and in empty rows
    
    // *** TOP ***
    cout << top_left; // ╔
    for (int i = 0; i < numTop; i++) {
        cout << horizontal; // ═
    }
    cout << top_right; // ╗
    cout << '\n';
    
    // ** EMPTY FIRST LINE **
    cout << vertical; // ║
    for (int j = 1; j <= numTop; j++) {
        cout << " ";
    }
    cout << vertical; // ║
    cout << '\n';
    
    // ** FIRST VERTICAL PIECE **
    cout << vertical; // ║
    for (int j = 1; j <= padding; j++) {
        cout << " ";
    }
    
    // **** MAIN PRINT LOOP ****
    for (int counter = 1; int i: board) {
        // num of digits in the current number
        int currDigits = static_cast<int>(ceil(log10(counter + 1)));
        
        // num of spaces to add after number to keep aligned with last row
        int currSpaces = high_digits - currDigits;
        
        if (i == -1) { // Sentry Value, Number was Already Picked
            
            cout << PURPLE;
            for (int j = 1; j <= currDigits; j++) { // Output 'x' for each of the digits in the taken number
                cout << "X";
            }
            cout << RESET;
        }
        else { // number not picked yet
            cout << GREEN << i << RESET;
        }
        
        if (counter % width != 0 && counter != board.size()) { // NOT END OF ROW
            for (int j = 1; j <= space_size + currSpaces; j++) {
                cout << " ";
            }
        }
        else { // **** END OF ROW ****
            // On last number of the board, and it is a magnitude greater than the number before it, meaning we need to print one less space
            if (counter == board.size() && floor(log10(board.size() - 1)) < floor(log10(board.size())) && board.size() != 1) {
                for (int j = 1; j <= padding - 1; j++) {
                    cout << " ";
                }
                cout << vertical; // ║
                cout << '\n';
            }
            else if (counter == board.size() && board.size() != width) { // On last number of board, but there's no change in magnitude
                for (int j = 0; j < (width - counter % width) * currDigits + (width - counter % width) * space_size; ++j) {
                    cout << " ";
                }
                for (int j = 1; j <= padding; j++) {
                    cout << " ";
                }
                cout << vertical; // ║
                cout << '\n';
            }
            else {
                for (int j = 1; j <= padding; j++) {
                    cout << " ";
                }
                cout << vertical; // ║
                cout << '\n';
            }
            
            // ** EMPTY ROW **
            cout << vertical; // ║
            for (int j = 1; j <= numTop; j++) {
                cout << " ";
            }
            cout << vertical; // ║
            cout << '\n';
            
            if (counter != board.size()) {
                cout << vertical; // ║
                for (int j = 1; j <= padding; j++) {
                    cout << " ";
                }
            }
            else { // print bottom
                cout << bottom_left; // ╚
                for (int j = 0; j < numTop; j++) {
                    cout << horizontal; // ═
                }
                cout << bottom_right; // ╝
            }
            
        }
        counter++;
    }
    cout << '\n';
}

/**
 *
 * @param board the main game board
 * @param pick the number the user picked
 * @return true if the number has not already been picked, and false otherwise
 */
bool validate(const vi & board, int pick) {
    return ranges::any_of(board, [pick](int i) { return pick == i; });
}

int main() {
    vi board; // the main board of the game
    vi giveAway; // the factors of the number picked that are given to the opponent
    int boardSize; // the size of the board, the highest number on the board
    
    int pick; // the number the current player picks
    
    int p1Score = 0; // player 1's score
    int p2Score = 0; // player 2's score
    
    int currPlayer = 1; // int representing the current player
    
    cout << "WELCOME TO THE FACTOR GAME!!!\nPlease enter the size of the board... ";
    boardSize = getNum(1, 100);
    cout << '\n';
    
    int p1ScoreInc = 0; // the amount of score player 1 got from that round
    int p2ScoreInc = 0; // the amount of score player 2 got from that round
    
    initArr(board, boardSize);
    
    bool flag = true;
    while (flag) {
        printBoard(board);
        if (currPlayer == 1) {
            cout << PINK;
        }
        else { // currPlayer == 2
            cout << TEAL;
        }
        cout << "Player " << currPlayer << RESET ", Pick a number: ";
        pick = getNum<int>(1, boardSize);
        while (!validate(board, pick)) {
            cout << "\nNumber must be on the board!!\n";
            pick = getNum<int>(1, boardSize);
        }
        cout << '\n';
        board[pick - 1] = -1;
        if (currPlayer == 1) { // player 1 gets to pick
            p1ScoreInc += pick;
            for (const int i: factor(pick)) { // for every factor
                if (i != pick) { // as long as the factor isnt the pick itself
                    for (int & j: board) { // for every number on the board
                        if (i == j) { // if the factor is on the board, give player 2 the points, and remove the number from the board
                            p2ScoreInc += i;
                            j = -1;
                            break;
                        }
                    }
                }
            }
            currPlayer = 2; // swap current player
        }
        else { // player 2 gets to pick
            p2ScoreInc += pick;
            for (const int i: factor(pick)) { // for every factor
                if (i != pick) { // as long as the factor isnt the pick itself
                    for (int & j: board) { // for every number on the board
                        if (i == j) { // if the factor is on the board, give player 1 the points, and remove the number from the board
                            p1ScoreInc += i;
                            j = -1;
                            break;
                        }
                    }
                }
            }
            currPlayer = 1; // swap current player
        }
        
        cout << format(PINK "Player 1" RESET " Gained {} points!!\n", p1ScoreInc);
        cout << format(TEAL "Player 2" RESET " Gained {} points!!\n\n", p2ScoreInc);
        
        p1Score += p1ScoreInc;
        p2Score += p2ScoreInc;
        
        p1ScoreInc = 0;
        p2ScoreInc = 0;
        
        cout << format(PINK "Player 1" RESET " now has {} points.\n", p1Score);
        cout << format(TEAL "Player 2" RESET " now has {} points.\n\n", p2Score);
        
        flag = false;
        
        for (int i: board) { // if all numbers are taken, exit
            if (i != -1) {
                flag = true;
            }
        }
    }
    
    cout << format(PINK "Player 1" RESET " ended with {} points!!!\n", p1Score);
    cout << format(TEAL "Player 2" RESET " ended with {} points!!!\n\n", p2Score);
    
    if (p1Score > p2Score) {
        cout << format(PINK "Player 1 " RESET "got more points than " TEAL "player 2 " RESET "by {}! Congrats on your win!!\n", p2Score - p1Score);
    }
    else if (p1Score < p2Score) {
        cout << format(TEAL "Player 2 " RESET "got more points than " PINK "player 1 " RESET "by {}! Congrats on your win!!\n", p1Score - p2Score);
    }
    else {
        cout << PINK "Player 1 " RESET "got the same amount of points as " TEAL "player 2" RESET "!! Impressive!!!!\n";
    }
    
    _getch();
    return 0;
    
}