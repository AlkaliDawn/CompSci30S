#include <iostream>
#include <format>
#include <conio.h>

using namespace std;

int main() {
    char input[20];
    
    cin >> input;
    cout << input << endl;
    cin.getline(input, 20, '\n');
    cout << input << endl;
    
    
    _getch();
    return 0;
}