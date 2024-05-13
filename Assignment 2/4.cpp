
#include <iostream>
#include <conio.h>
#include <random>
#include <format>
#include <algorithm>
#include <thread>

#include "bartlett.h"

#define GOLD "\033[38;2;187;166;61m"


using namespace std;

int simDraw();

bool playWeek(int & whiteDrawn, int week, int & jackpot);

constexpr array<string_view, 8> Colors = {LIME, PASTEL_BLUE, YELLOW, ORANGE, PINK, TEAL, PURPLE, BLUE};
const int Total_Balls = 30;

int main() {
    int whiteDrawn = 0; // number of white balls drawn
    float sum = 0; // used in part 2 to avg num of weeks over trials
    int jackpot = 10; // stores current jackpot, represents value in millions
    
    seedRandom();
    
    cout << "Part 1:\n";
    
    for (int trial = 1; trial <= 3; trial++) {
        cout << "Trial #" << trial << ":\n";
        for (int week = 1; week <= Total_Balls; week++) {
            if (playWeek(whiteDrawn, week, jackpot)) {
                break;
            }
        }
    }
    
    
    // PART 2
    cout << "Part 2:\n";
    
    // 5 Draws
    for (int trial = 1; trial <= 5; ++trial) {
        sum += simDraw();
    }
    sum /= 5;
    cout << format("For 5 draws, it took an average of {} weeks to win\n", sum);
    sum = 0;
    
    // 50 Draws
    for (int trial = 1; trial <= 50; ++trial) {
        sum += simDraw();
    }
    sum /= 50;
    cout << format("For 50 draws, it took an average of {} weeks to win\n", sum);
    sum = 0;
    
    // 500 Draws
    for (int trial = 1; trial <= 500; ++trial) {
        sum += simDraw();
    }
    sum /= 500;
    cout << format("For 500 draws, it took an average of {} weeks to win\n", sum);
    sum = 0;
    
    return 0;
}

/**
 * @param whiteDrawn number of white balls that were drawn already from past weeks
 * @param week current week being simulated
 * @param jackpot current jackpot to to be won with a gold ball
 *
 * @return true if a gold ball is won, and false if a white ball is won
 *
 * @brief Plays out one week of the lottery
 */
bool playWeek(int & whiteDrawn, int week, int & jackpot) {
    if (rand() % (Total_Balls - whiteDrawn) == 0) {
        cout << format("Gold Ball Draw Week {} - " GOLD BOLD "A Gold ball was chosen" RESET " - {} ${} million Jackpot was won!!!\n" RESET,
                week, Colors.at(rand() % Colors.size()), jackpot);
        jackpot = 10;
        whiteDrawn = 0;
        this_thread::sleep_for(250ms);
        cout << "Press any key to continue... ";
        _getche();
        cout << '\n';
        return true;
    }
    jackpot += 2;
    cout << format("Gold Ball Draw Week {} -" BOLD " A White ball was chosen " RESET "- Jackpot Next Week = ${} million\n",
            week, jackpot);
    whiteDrawn++;
    this_thread::sleep_for(550ms);
    return false;
    
}

/**
 *
 * @return the number of weeks it took to draw a gold ball
 *
 * @brief Simulates one trial of the lottery
 */
int simDraw() {
    int whiteDrawn = 0;
    for (int week = 1; week <= Total_Balls; week++) {
        if (rand() % (Total_Balls - whiteDrawn) == 0) {
            return week;
        }
        whiteDrawn++;
    }
    return 0;
}