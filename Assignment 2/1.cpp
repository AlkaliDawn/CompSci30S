#include <iostream>
#include <conio.h>
#include <random>
#include <format>
#include "bartlett.h"

using namespace std;

typedef vector<float> vf;

void enterData(vf& data) {
    int num_values = 0;
    cout << format("Please enter the number of values to be inputted. There are currently {} values stored. -> ", data.size());
    num_values = getNum<int>();
    cout << "\n";
    for (int i = 0; i < num_values; i++) {
        cout << format("Enter value #{}: ", i+1);
        data.push_back(getNum<float>());
    }
}

float high(const vf& data) {
    float currHigh = data[0];
    for (int i = 1; i < data.size(); i++) {
        if (currHigh < data[i]) {
            currHigh = data[i];
        }
    }
    return currHigh;
}

float low(const vf& data) {
    float currLow = data[0];
    for (int i = 1; i < data.size(); i++) {
        if (currLow > data[i]) {
            currLow = data[i];
        }
    }
    return currLow;
}

float range(const vf& data) {
    return abs(high(data)-low(data));
}

int positive(const vf& data) {
    int num = 0;
    for (float i : data) {
        if (i > 0) {
            num++;
        }
    }
    return num;
}

int negative(const vf& data) {
    int num = 0;
    for (float i : data) {
        if (i < 0) {
            num++;
        }
    }
    return num;
}

int zero(const vf& data) {
    int num = 0;
    for (float i : data) {
        if (i == 0) {
            num++;
        }
    }
    return num;
}

float avg(const vf& data) {
    float sum = 0;
    float num_val = data.size();
    for (float i: data) {
        sum += i/num_val;
    }
    return sum;
}

pair<float,float> mode(const vf& data) {
    array<float, 2> val_freq = {0,0}; // 0: value, 1: freq
    vf freq;
    for (int i = 0; i < data.size(); i++) {
        freq.push_back(0);
        for (int j = i; j < data.size(); j++) {
            if (i != j) {
                if (data[i] == data[j]) {
                    freq[i]++;
                }
            }
        }
    }

    float high_val = 0;
    int high_freq = 0;

    for (int i = 0; i < freq.size(); i++) {
        if (high_freq < freq[i]) {
            high_freq = freq[i];
            high_val = data[i];
        }
    }

    high_freq++; // include first instance of number

    return make_pair(high_val, high_freq);
}

float variance(const vf& data) {
    float sum;
    const float mean = avg(data);
    const float bessel_correction = data.size() - 1;
    for (float x : data) {
        float temp = ( x - mean );
        sum += (temp * temp) /  bessel_correction;
    }
    return sum;
}

float deviation(const vf& data) {
    float sum;
    const float mean = avg(data);
    const float bessel_correction = data.size() - 1;
    for (float x : data) {
        float temp = ( x - mean );
        sum += (temp * temp) /  bessel_correction;
    }
    sum = sqrt(sum);
    return sum;
}


int main() {

    pair<float,float> modeR; // mode return value

    const string VALID_INPUTS = "ehlrpnzamvsqd";
    vf data = {};// vector<float> to store all the data
    char input;

    cout << "Welcome to your personal numerical secretarial program, or PNSP for short. \n\n"
         << "--- Main Menu ---\n";

    bool flag = true;
    while (flag) {
        if (input != 'd') {
            cout << "\n(E)nter Data, (H)ighest, (L)owest, (R)ange, \n(P)ositive, (N)egative, (Z)ero, \n(A)verage, (M)ode, (V)ariance, (S)tandard Deviation, \n(Q)uit, (D)etailed - Print a more detailed directory\n\n"
                 << "Please select an input: ";
        }
        input = get(VALID_INPUTS);

        // Check that selected operation is valid based on nuber of data points
        if (data.empty()) {
            // allow enterdata, high, low, range, pos, neg, zero, avg, mode,
            if (input != 'e' && input != 'q' && input != 'd' && input != 'p' && input != 'n' && input != 'z') {
                cout << "You must enter AT LEAST 1 data point before doing that!!\n";
                continue;
            }
        } else if (input == 'v' || input == 's') {
            if (data.size() < 2) {
                cout << "You must enter at least 2 data points before doing that!!\n";
                continue;
            }
        }

        cout << endl;
        switch (input) {
            case 'e': {
                enterData(data);
                break;
            }
            case 'h': {
                cout << format(BOLD "The highest number found in the data is {}.\n" RESET, high(data));
                break;
            }
            case 'l': {
                cout << format(BOLD "The lowest number found in the data is {}.\n" RESET, low(data));
                break;
            }
            case 'r': {
                cout << format(BOLD "The the range in the data is {}.\n" RESET, range(data));
                break;
            }
            case 'p': {
                cout << format(BOLD "There are {} positive values in the data.\n" RESET, positive(data));
                break;
            }
            case 'n': {
                cout << format(BOLD "There are {} negative values in the data.\n" RESET, negative(data));
                break;
            }
            case 'z': {
                cout << format(BOLD "There are {} zero values in the data.\n" RESET, zero(data));
                break;
            }
            case 'a': {
                cout << format(BOLD "The mean of the data is {}.\n" RESET, avg(data));
                break;
            }
            case 'm': {
                modeR = mode(data);
                cout << format(BOLD "The mode of the data is {}, appearing {} times.\n" RESET, modeR.first, modeR.second);
                break;
            }
            case 'v': {
                cout << format(BOLD "The variance of the data is {}.\n" RESET, variance(data));
                break;
            }
            case 's': {
                cout << format(BOLD "The standard deviation in the data is {}.\n" RESET, deviation(data));
                break;
            }
            case 'q': {
                cout << "Thank you for using the PNSP\n";
                flag = false;
                break;
            }
            case 'd': {
                cout << "(E)nter Data - Enter data into the program\n"
                        "(H)ighest - Find the highest value\n"
                        "(L)owest - Find the lowest value\n"
                        "(R)ange - Find the range of the data\n"
                        "(P)ositive - Find how many data points are positive\n"
                        "(N)egative - Find how many data points are negative\n"
                        "(Z)ero - Find how many data points are equal to zero\n"
                        "(A)verage - Calculate the Mean of the data\n"
                        "(M)ode - Calculate the Mode of the data\n"
                        "(V)ariance - Calculate the Variance of the data\n"
                        "(S)tandard Deviation - Calculate the Standard Deviation of the data\n"
                        "(Q)uit - End the program\n"
                        "(D)etailed - Print this detailed help menu\n\n";

                cout << "Please select an input: ";
            }
        }
    }
    cout << "Press any key to exit...";
    _getch();
}