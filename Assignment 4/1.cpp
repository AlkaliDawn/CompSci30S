#include <algorithm>
#include <iostream>
#include <conio.h>
#include <cmath>
#include <random>
#include <format>
#include "bartlett.h"

using namespace std;

int main() {
    
    seedRandom();
    
    vector<int> numbers;
    
    for (int i = 0; i < 30; ++i) {
        numbers.push_back(rand() % 100 + 1);
    }
    
    insertionSort(numbers);
    
    for (const auto & number: numbers) {
        cout << number << ", ";
    }
    cout << '\n';
    
    for (int i = 0; i < 4; i++) {
        int num = getNum(1, 100);
        
        cout << binarySearch(numbers, num) + 1 << endl;
    }
    cout << "Press any key to exit...";
    _getch();
    return 0;
}