#include <iostream>
#include <conio.h>
#include <math.h>
#include <random>
#include <format>
#include "bartlett.h"

using namespace std;

using vf = vector<float>;

/**
 * 
 * @param data main data array of the program.
 * Allows the user to enter data into the program
 */
void enterData(vf & data) {
    cout << format("Please enter the number of values to be inputted. There are currently {} values stored. -> ", data.size());
    int numValues = getNum<int>();
    cout << "\n";
    for (int i = 0; i < numValues; i++) {
        cout << format("Enter value #{}: ", i + 1);
        data.push_back(getNum<float>());
    }
}

/**
 * 
 * @param data main data array of the program.
 * @return the highest value in the array
 */
float high(const vf & data) {
    float currHigh = data[0];
    for (int i = 1; i < data.size(); i++) {
        currHigh = std::max(currHigh, data[i]);
    }
    return currHigh;
}

/**
 * 
 * @param data main data array of the program.
 * @return the lowest value in the array
 */
float low(const vf & data) {
    float currLow = data[0];
    for (int i = 1; i < data.size(); i++) {
        currLow = std::min(currLow, data[i]);
    }
    return currLow;
}

/**
 * 
 * @param data main data array of the program.
 * @return the absolute difference between the largest and smallest value in the array
 */
float range(const vf & data) {
    return abs(high(data) - low(data));
}

/**
 *
 * @param data main data array of the function.
 * @return the number of positive values in the array
 */
int positive(const vf & data) {
    int num = 0;
    for (float i: data) {
        if (i > 0) {
            num++;
        }
    }
    return num;
}

/**
 *
 * @param data main data array of the function.
 * @return the number of negative values in the array
 */
int negative(const vf & data) {
    int num = 0;
    for (float i: data) {
        if (i < 0) {
            num++;
        }
    }
    return num;
}

/**
 *
 * @param data main data array of the function.
 * @return the number of zeroes in the array
 */
int zero(const vf & data) {
    int num = 0;
    for (float i: data) {
        if (i == 0) {
            num++;
        }
    }
    return num;
}

/**
 *
 * @param data main data array of the function.
 * @return the mean of the values in the data
 */
float avg(const vf & data) {
    float sum = 0;
    float numVal = data.size();
    for (float i: data) {
        sum += i / numVal;
    }
    return sum;
}

/**
 *
 * @param data main data array of the function.
 * @return a pair of floats, with the first being the value of the mode, and the second being the count of the mode
 */
pair<float, float> mode(const vf & data) {
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
    
    float highVal = 0;
    int highFreq = 0;
    
    for (int i = 0; i < freq.size(); i++) {
        if (highFreq < freq[i]) {
            highFreq = freq[i];
            highVal = data[i];
        }
    }
    
    highFreq++; // include first instance of number
    
    return make_pair(highVal, highFreq);
}

/**
 *
 * @param data main data array of the function.
 * @return the variance of the data
 */
float variance(const vf & data) {
    float sum = 0;
    const float mean = avg(data);
    const float bessel_correction = data.size() - 1;
    for (float x: data) {
        float temp = (x - mean);
        sum += (temp * temp) / bessel_correction;
    }
    return sum;
}

/**
 *
 * @param data main data array of the function.
 * @return the sqrt of the variance, aka the standard deviation of the data
 */
float deviation(const vf & data) {
    float sum = 0;
    const float mean = avg(data);
    const float bessel_correction = data.size() - 1;
    for (float x: data) {
        float temp = (x - mean);
        sum += (temp * temp) / bessel_correction;
    }
    sum = sqrt(sum);
    return sum;
}

int main() {
    
    pair<float, float> modeReturn; // Variable to store output of mode func
    
    const string valid_inputs = "ehlrpnzamvsqd"; // string containing valid input chars
    vf data = {}; // vector<float> to store all the data
    char input = 0; // char to store user input
    
    cout << "Welcome to your personal numerical secretarial program, or PNSP for short. \n\n"
         << "--- Main Menu ---\n";
    
    bool flag = true;
    while (flag) {
        if (input != 'd') {
            cout << "\n(E)nter Data, (H)ighest, (L)owest, (R)ange, \n(P)ositive, (N)egative, (Z)ero, \n(A)verage, (M)ode, (V)ariance, (S)tandard Deviation, \n(Q)uit, (D)etailed - Print a more detailed directory\n\n"
                 << "Please select an input: ";
        }
        
        input = get(valid_inputs); // get the user's input
        
        // Check that selected operation is valid based on number of data points
        // some operations work with no datapoints and just return 0
        // enterdata, quit, detailed, pos, neg, and zero are allowed for no datapoints
        // high, low, range, avg, and mode are allowed for 1 datapoint
        // std dev and variance need 2 or more datapoints
        if (data.empty()) { // if there are no data points
            
            if (input != 'e' && input != 'q' && input != 'd' && input != 'p' && input != 'n' && input != 'z') {
                cout << "You must enter AT LEAST 1 data point before doing that!!\n";
                continue;
            }
        }
        else if (input == 'v' || input == 's') { // if user requested variance or std dev, there must be 2 or more points
            if (data.size() < 2) {
                cout << "You must enter at least 2 data points before doing that!!\n";
                continue;
            }
        }
        
        cout << '\n';
        
        switch (input) { // main directory tree
            case 'e': { // enter data
                enterData(data);
                break;
            }
            case 'h': { // highest
                cout << format(BOLD "The highest number found in the data is {}.\n" RESET, high(data));
                break;
            }
            case 'l': { // lowest
                cout << format(BOLD "The lowest number found in the data is {}.\n" RESET, low(data));
                break;
            }
            case 'r': { // range
                cout << format(BOLD "The the range in the data is {}.\n" RESET, range(data));
                break;
            }
            case 'p': { // # of positive
                cout << format(BOLD "There are {} positive values in the data.\n" RESET, positive(data));
                break;
            }
            case 'n': { // # of negative
                cout << format(BOLD "There are {} negative values in the data.\n" RESET, negative(data));
                break;
            }
            case 'z': { // # of zeroes
                cout << format(BOLD "There are {} zero values in the data.\n" RESET, zero(data));
                break;
            }
            case 'a': { // avg
                cout << format(BOLD "The mean of the data is {}.\n" RESET, avg(data));
                break;
            }
            case 'm': { // mode
                modeReturn = mode(data);
                cout << format(BOLD "The mode of the data is {}, appearing {} times.\n" RESET, modeReturn.first, modeReturn.second);
                break;
            }
            case 'v': { // variance
                cout << format(BOLD "The variance of the data is {}.\n" RESET, variance(data));
                break;
            }
            case 's': { // std dev
                cout << format(BOLD "The standard deviation in the data is {}.\n" RESET, deviation(data));
                break;
            }
            case 'q': { // quit
                cout << "Thank you for using the PNSP\n";
                flag = false;
                break;
            }
            case 'd': { // detailed directory
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