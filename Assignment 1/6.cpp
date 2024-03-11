#include <conio.h>
#include <format>
#include <iostream>
#include <string>
#include <random>
#include <thread>

using namespace std;

// seeds the random number generator using a non-deterministic random number generator
void seed_random() {
    random_device tempDevice;
    srand(tempDevice());
    for (int i = 0; i < tempDevice(); i++) {
        rand();
    }
}

bool coin_toss() {
    return rand() % 2;
}

void play_end(int end, bool hammer, int &score1, int &score2) {
    int outcome = rand() % 100;
    bool winner;
    int gain;
    if (outcome < 15) { // 15 %
        winner = 0;
        gain = 0;
    }
    else if (outcome < 35) { // 20
        winner = hammer;
        gain = 1;
    }
    else if (outcome < 50) { // 15
        winner = hammer;
        gain = 2;
    }
    else if (outcome < 60) { // 10
        winner = hammer;
        gain = 3;
    }
    else if (outcome < 65) { // 5
        winner = hammer;
        gain = 4;
    }
    else if (outcome < 84) { // 19
        winner = !hammer;
        gain = 1;
    }
    else if (outcome < 94) { // 10
        winner = !hammer;
        gain = 2;
    }
    else if (outcome < 99) { // 5
        winner = !hammer;
        gain = 3;
    }
    else if (outcome < 100) { // 1
        winner = !hammer;
        gain = 4;
    }
    if (winner) {
        score1 += gain;
        cout << gain;
        for (int j = 0; j < 15; j++) {
            cout << " ";
        }
        cout << "0";
    }
    else {
        score2 += gain;
        cout << "0";
        for (int j = 0; j < 15; j++) {
            cout << " ";
        }
        cout << gain;
    }
}

int main() {

    seed_random();

    int score1 = 0;
    int score2 = 0;

    int end;

    cout << "END          TEAM 30S        TEAM 40S\n";

    for (end = 0; end < 10 || score1 == score2; end++) {
        cout << " " << end + 1;
        for (int j = 0; j < 14; j++) {
            cout << " ";
        }
        if (floor((end + 1)/10) == 0) {
            cout << " ";
        }
        play_end(end, coin_toss(), score1, score2);
        cout << endl;
    }

    cout << "FINAL SCORE      " << score1;
    for (int j = 0; j < 15; j++) {
        cout << " ";
    }
    if (floor(score1/10) > 0) {
        cout << " ";
    }
    cout << score2;

    _getch();
}