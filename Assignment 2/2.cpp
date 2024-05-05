#include <iostream>
#include <conio.h>
#include <random>
#include <format>
#include <algorithm>

#include "bartlett.h"

using namespace std;

typedef vector<int> vi;

vi factor(const int num) {
    vi factors;
    for (int i = 1; i < num / 2; i++) {
        if ((num/i)*i==num) {
            if (i != 1 && i == factors[factors.size()-1]) { // prevent duplicating factors
                break;
            }
            if (i == num/i) {
                factors.push_back(i);
                break;
            } else {
                factors.push_back(i);
                factors.push_back(num/i);
            }
        }
    }
    return factors;
}

void init_arr(vi& arr, int board_size) {
    for (int i = 0; i < board_size; i++) {
        arr.push_back(i+1);
    }
}

void printBoard(const vi& board) {
    int total_spaces = ceil(log10(board.size()));
    
    // 3 space characters between each number at the bottom * 9 of these, + the width of the numbers at the bottom * 10 numbers + dynamic amount of spaces added to each end of the numbers for aesthetics
    int num_top = (3 * 9 + total_spaces * 10 + total_spaces * 4);
    
    if (board.size() < 10) {
        num_top *= static_cast<int>(board.size()) / 10;
    }
    else if (board.size() == 10) {
        num_top += 3;
    }

    cout << static_cast<unsigned char>(201); // ╔
    for (int i = 0; i < num_top; i++) {
        cout << static_cast<unsigned char>(205); // ═
    }
    cout << static_cast<unsigned char>(187); // ╗
    cout << endl;
    
    cout << static_cast<unsigned char>(186); // ║
    for (int j = 1; j <= num_top; j++) {
        cout << " ";
    }
    cout << static_cast<unsigned char>(186); // ║
    cout << endl;
    
    cout << static_cast<unsigned char>(186); // ║
    for (int j = 1; j <= total_spaces + 1; j++) {
        cout << " ";
    }

    for (int counter = 0; int i: board) {
        int curr_spaces = total_spaces - static_cast<int>(ceil(log10(counter + 2)));
        if (i == -1) {
            int num_digits = static_cast<int>(ceil(log10(counter + 2)));
            cout << PURPLE " ";
            for (int j = 1; j <= num_digits; j++) {
                cout << "X";
            }
            cout << " ";
            cout << RESET;
        }
        else {
            cout << GREEN " " << i << RESET " ";
        }
        for (int j = 1; j <= curr_spaces + 1; j++) {
            cout << " ";
        }
        if ((counter) % 10 == 9) { // END OF ROW
            for (int j = 1; j <= total_spaces + 1; j++) {
                cout << " ";
            }
            cout << static_cast<unsigned char>(186); // ║
            cout << endl;
            cout << static_cast<unsigned char>(186); // ║
            for (int j = 1; j <= num_top; j++) {
                cout << " ";
            }
            cout << static_cast<unsigned char>(186); // ║
            cout << endl;
            if (counter != board.size()-1) {
                cout << static_cast<unsigned char>(186); // ║
                for (int j = 1; j <= total_spaces + 1; j++) {
                    cout << " ";
                }
            }
            else { // print bottom
                cout << static_cast<unsigned char>(200); // ╚
                for (int j = 0; j < num_top; j++) {
                    cout << static_cast<unsigned char>(205); // ═
                }
                cout << static_cast<unsigned char>(188); // ╝
            }
            
        }
        counter++;
    }
    cout << endl;
}

bool validate(const vi& board, int pick) {
    return ranges::any_of(board, [pick](int i) {return pick == i;} );
}

int main() {
    vi board;
    vi give_away;
    int board_size;

    int pick;

    int p1score = 0;
    int p2score = 0;

    bool curr_player = true;

    cout << "WELCOME TO THE FACTOR GAME!!!\nPlease enter the size of the board... ";
    board_size = getNum(1);
    cout << endl;

    int p1score_inc = 0;
    int p2score_inc = 0;

    init_arr(board, board_size);

    bool flag = true;
    while (flag) {
        printBoard(board);
        cout << "Player " << !curr_player + 1 << ", Pick a number: ";
        pick = getNum<int>(1, board_size);
        while(!validate(board, pick)) {
            cout << "\nNumber must be on the board!!\n";
            pick = getNum<int>(1, board_size);
        }
        cout << endl;
        board[pick-1] = -1;
        if (curr_player) {
            p1score_inc += pick;
            for (const int i: factor(pick)) {
                if (i != pick) {
                    for (int& j: board) {
                        if (i == j) {
                            p2score_inc += i;
                            j = -1;
                            break;
                        }
                    }
                }
            }
        } else {
            p2score_inc += pick;
            for (const int i: factor(pick)) {
                if (i != pick) {
                    for (int& j: board) {
                        if (i == j) {
                            p1score_inc += i;
                            j = -1;
                            break;
                        }
                    }
                }
            }
        }

        cout << format("Player 1 Gained {} points!!\n", p1score_inc);
        cout << format("Player 2 Gained {} points!!\n\n", p2score_inc);

        p1score += p1score_inc;
        p2score += p2score_inc;

        p1score_inc = 0;
        p2score_inc = 0;

        cout << format("Player 1 now has {} points.\n", p1score);
        cout << format("Player 2 now has {} points.\n\n", p2score);

        curr_player = !curr_player;

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