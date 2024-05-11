#include <iostream>
#include <conio.h>
#include <random>
#include <format>
#include <algorithm>

#include "bartlett.h"

using namespace std;

using vi = vector<int>;

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

void initArr(vi & arr, int boardSize) {
    for (int i = 0; i < boardSize; i++) {
        arr.push_back(i + 1);
    }
}

void printBoard(const vi & board) {
    const unsigned char top_left = 201;
    const unsigned char horizontal = 205;
    const unsigned char top_right = 187;
    const unsigned char vertical = 186;
    const unsigned char bottom_left = 200;
    const unsigned char bottom_right = 188;
    
    const int padding = 5;
    const int board_spaces = min(9, static_cast<int>(board.size()) - 1);
    const int space_size = 3;
    const int width = min(10, static_cast<int>(board.size())); // amount of numbers placed horizontally in the grid
    
    const int high_digits = max(ceil(log10(static_cast<double>(board.size()))), 1.0);
    
    // 3 space characters between each number at the bottom * 9 of these, + the width of the numbers at the bottom * 10 numbers + (totalSpaces * 4) - > dynamic amount of spaces added to each end of the numbers for aesthetics
    int numTop = (space_size * board_spaces + width * high_digits + padding * 2);

//    if (board.size() < width) {
//        numTop *= static_cast<int>(board.size()) / width;
//    }
//    else if (board.size() == width) {
//        numTop += 3;
//    }
    
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
        
        int currSpaces = high_digits - currDigits;
        
        if (i == -1) { // Sentry Value, Number was Already Picked
            
            cout << PURPLE;
            for (int j = 1; j <= currDigits; j++) { // Output 'x' for each of the digits in the taken number
                cout << "X";
            }
            cout << RESET;
        }
        else {
            cout << GREEN << i << RESET;
        }
        
        if (counter % width != 0) { // NOT END OF ROW
            for (int j = 1; j <= space_size + currSpaces; j++) {
                cout << " ";
            }
        }
        else { // **** END OF ROW ****
            
            if (counter == board.size() && floor(log10(board.size() - 1)) < floor(log10(board.size())) && board.size() != 1) { // not last num
                for (int j = 1; j <= padding - 1; j++) {
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

bool validate(const vi & board, int pick) {
    return ranges::any_of(board, [pick](int i) { return pick == i; });
}

int main() {
    vi board;
    vi giveAway;
    int boardSize;
    
    int pick;
    
    int p1Score = 0;
    int p2Score = 0;
    
    int currPlayer = 1;
    
    cout << "WELCOME TO THE FACTOR GAME!!!\nPlease enter the size of the board... ";
    boardSize = getNum(1, 100);
    cout << '\n';
    
    int p1ScoreInc = 0;
    int p2ScoreInc = 0;
    
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
        if (currPlayer == 1) {
            p1ScoreInc += pick;
            for (const int i: factor(pick)) {
                if (i != pick) {
                    for (int & j: board) {
                        if (i == j) {
                            p2ScoreInc += i;
                            j = -1;
                            break;
                        }
                    }
                }
            }
            currPlayer = 2;
        }
        else { // currPlayer == 2
            p2ScoreInc += pick;
            for (const int i: factor(pick)) {
                if (i != pick) {
                    for (int & j: board) {
                        if (i == j) {
                            p1ScoreInc += i;
                            j = -1;
                            break;
                        }
                    }
                }
            }
            currPlayer = 1;
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
        
        for (int i: board) {
            if (i != -1) {
                flag = true;
            }
        }
    }
    
    _getch();
    return 0;
    
}