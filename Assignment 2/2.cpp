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
    const int top_left = 201;
    const int horizontal = 205;
    const int top_right = 187;
    const int vertical = 186;
    const int bottom_left = 200;
    const int bottom_right = 188;
    
    const int board_spaces = 9;
    const int space_size = 3;
    const int width = 10; // amount of numbers placed horizontally in the grid
    
    int totalSpaces = ceil(log10(board.size()));
    
    // 3 space characters between each number at the bottom * 9 of these, + the width of the numbers at the bottom * 10 numbers + (totalSpaces * 4) - > dynamic amount of spaces added to each end of the numbers for aesthetics
    int numTop = (space_size * board_spaces + totalSpaces * width + totalSpaces * 4);
    
    if (board.size() < width) {
        numTop *= static_cast<int>(board.size()) / width;
    }
    else if (board.size() == width) {
        numTop += 3;
    }
    
    // *** TOP ***
    cout << static_cast<unsigned char>(top_left); // ╔
    for (int i = 0; i < numTop; i++) {
        cout << static_cast<unsigned char>(horizontal); // ═
    }
    cout << static_cast<unsigned char>(top_right); // ╗
    cout << '\n';
    
    // ** EMPTY FIRST LINE **
    cout << static_cast<unsigned char>(vertical); // ║
    for (int j = 1; j <= numTop; j++) {
        cout << " ";
    }
    cout << static_cast<unsigned char>(vertical); // ║
    cout << '\n';
    
    // ** FIRST VERTICAL PIECE **
    cout << static_cast<unsigned char>(vertical); // ║
    for (int j = 1; j <= totalSpaces + 1; j++) {
        cout << " ";
    }
    
    // **** MAIN PRINT LOOP ****
    for (int counter = 0; int i: board) {
        // num of digits in the current number
        int numDigits = static_cast<int>(ceil(log10(counter + 2)));
        // current spaces is the totalSpaces
        int currSpaces = totalSpaces - static_cast<int>(ceil(log10(counter + 2)));
        
        if (i == -1) {
            
            cout << PURPLE << " ";
            for (int j = 1; j <= numDigits; j++) {
                cout << "X";
            }
            cout << " " << RESET;
        }
        
        else {
            cout << GREEN << " " << i << RESET << " ";
        }
        
        for (int j = 1; j <= currSpaces + 1; j++) {
            cout << " ";
        }
        // **** END OF ROW ****
        if (counter % width == width - 1) {
            for (int j = 1; j <= totalSpaces; j++) {
                cout << " ";
            }
            cout << static_cast<unsigned char>(vertical); // ║
            cout << '\n';
            
            cout << static_cast<unsigned char>(vertical); // ║
            for (int j = 1; j <= numTop; j++) {
                cout << " ";
            }
            cout << static_cast<unsigned char>(vertical); // ║
            cout << '\n';
            if (counter != board.size() - 1) {
                cout << static_cast<unsigned char>(vertical); // ║
                for (int j = 1; j <= totalSpaces + 1; j++) {
                    cout << " ";
                }
            }
            else { // print bottom
                cout << static_cast<unsigned char>(bottom_left); // ╚
                for (int j = 0; j < numTop; j++) {
                    cout << static_cast<unsigned char>(horizontal); // ═
                }
                cout << static_cast<unsigned char>(bottom_right); // ╝
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
    int boardSize = 0;
    
    int pick = 0;
    
    int p1Score = 0;
    int p2Score = 0;
    
    bool currPlayer = true;
    
    cout << "WELCOME TO THE FACTOR GAME!!!\nPlease enter the size of the board... ";
    boardSize = getNum(1);
    cout << '\n';
    
    int p1ScoreInc = 0;
    int p2ScoreInc = 0;
    
    initArr(board, boardSize);
    
    bool flag = true;
    while (flag) {
        printBoard(board);
        cout << "Player " << currPlayer + 1 << ", Pick a number: ";
        pick = getNum<int>(1, boardSize);
        while (!validate(board, pick)) {
            cout << "\nNumber must be on the board!!\n";
            pick = getNum<int>(1, boardSize);
        }
        cout << '\n';
        board[pick - 1] = -1;
        if (currPlayer) {
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
        }
        else {
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
        }
        
        cout << format("Player 1 Gained {} points!!\n", p1ScoreInc);
        cout << format("Player 2 Gained {} points!!\n\n", p2ScoreInc);
        
        p1Score += p1ScoreInc;
        p2Score += p2ScoreInc;
        
        p1ScoreInc = 0;
        p2ScoreInc = 0;
        
        cout << format("Player 1 now has {} points.\n", p1Score);
        cout << format("Player 2 now has {} points.\n\n", p2Score);
        
        currPlayer = !currPlayer;
        
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