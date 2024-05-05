// Most Popular Pirate - This program simulates an election for a Pirate Captain - To do this, it
// randomly assigns votes to pirates and tells who won at the end. Pirate numbers start at 0!
// FUNCTION PROTOTYPES
#include <iostream>
#include <random>
#include <conio.h>

void initialize_and_vote(int pirates[100] , int &num_pirates);
int most_popular(const int pirates[100], int num_pirates);

using namespace std;

int main(void) {
    int pirates[100];                   // the array containing the votes for each pirate - this is zero-based
    int num_pirates; // The number of pirates (maximum is 100)
    random_device tempDevice;
    srand(tempDevice());
    initialize_and_vote(pirates, num_pirates);   // Call function to initialize and vote
    // Call function to find out who won and tell how many votes they got 2
    int winner = most_popular(pirates, num_pirates);
    cout << "The pirate with the most votes was #" << winner << ", who got " << pirates[winner] << " votes "<< endl;
    _getch();
    return 0;
}

void initialize_and_vote(int pirates[100], int& num_pirates) // Set all to 0 and do random votes
{
    int count;                     // Loop counter;
    int how_many;              // How many votes to simulate
    cout << "How many pirates are running? ";
    cin >> num_pirates;   // You can Assume <=100!
    cout << "How many votes do you want to simulate?";
    cin >> how_many;
    for (count = 0; count < num_pirates; count++)   // Initialize so all pirates start with 0 votes
        pirates[count] = 0;
    for (count = 1; count <= how_many; count++) // Run random trials, updating correct spot each time
        pirates[rand() % num_pirates]++;
}

int most_popular(const int pirates[100], int num_pirates)    // Return spot # of pirate with most votes
{
    int most;              // most found so far
    int count;            // Loop counter
    most = 0;               // Set most to first element in array
    for (count = 0; count < num_pirates; count++)            // Loop through rest of pirates
    {
        if (pirates[count] > pirates[most]) {
            most = count;
        }
    }
    return most;                // Return spot of pirate with most votes (zero based)
}


