#include <algorithm>
#include <iostream>
#include <conio.h>
#include <cstdio>
#include <random>
#include <format>
#include "bartlett.h"

using dataType = long int;
using namespace std;

using SortAlg = enum {
    Insert, Bubble, Quick
};

using SortDirection = enum {
    Ascending, Descending
};

enum SearchAlg : uint8_t {
    Binary, Linear
};

void enterData(vector<dataType> & data);
bool isSorted(const vector<dataType> & data, SortDirection & direction);

void invert(vector<dataType> & data);

bool sort(vector<dataType> & data, SortAlg sortType, SortDirection direction);

optional<size_t> search(vector<dataType> & data, SearchAlg searchType);

void print(const vector<dataType> & data, bool sorted);

size_t binarySearch(const vector<dataType> & data, dataType key);
size_t linearSearch(const vector<dataType> & data, dataType key);

void bubbleSort(vector<dataType> & data);
void insertionSort(vector<dataType> & data);
void quickSort(vector<dataType> & data, size_t left, size_t right);

void quickSort(std::vector<dataType> & data);

int main() {
    
    vector<dataType> data;
    bool sorted = true;
    
    char input;
    SortAlg sortType;
    SortDirection direction = Ascending;
    SearchAlg searchType;
    
    while (true) {
        printf("There are currently %zu %s data points, Do you want to (S)earch, (O)rder, or (E)nter Data? > ", data.size(), (sorted ? "sorted" : "unsorted"));
        input = get("soe");
        switch (input) {
            case 'o':
                cout << "Do you want to use (I)nsertion, (B)ubble, or (Q)uick Sort? > ";
                input = get("ibq");
                switch (input) {
                    case 'i':
                        sortType = Insert;
                    case 'b':
                        sortType = Bubble;
                    case 'q':
                        sortType = Quick;
                }
                cout << "Do you want to sort (A)scending or (D)escending? > ";
                input = get("ad");
                switch (input) {
                    case 'a':
                        direction = Ascending;
                    case 'd':
                        direction = Descending;
                }
                sort(data, sortType, direction);
                sorted = true;
            case 's':
                cout << "Do you want to use (B)inary, or (L)inear search? > ";
                input = get("bl");
                switch (input) {
                    case 'b':
                    
                }
            case 'e':
                enterData(data);
                sorted = isSorted(data, direction);
        }
        
        print(data, sorted);
    }
    cout << "Press any key to exit...";
    _getch();
    return 0;
}

bool isSorted(const vector<dataType> & data) {
    if (data.size() == 1) {
        return true;
    }
    
    bool sortedA = true;
    bool sortedD = true;
    
    // check every element in the array, if it is out of order for a sort direction, set the corresponding bool to false
    for (int i = 1; i < data.size(); ++i) {
        if (data[i - 1] > data[i]) {
            sortedA = false;
        }
        if (data[i - 1] < data[i]) {
            sortedD = false;
        }
    }
    
    // if the array is sorted in either asc or dec order, return true
    return sortedD || sortedA;
}

void invert(vector<dataType> & data) {
    if (data.size() < 2) { // array cannot be inverted
        return;
    }
    if (data.size() == 2) { // special case for size 2 for efficiency
        swap(data[0], data[1]);
        return;
    }
    auto low = data.begin();
    auto high = data.end();
    while (low <= high) { // start at each end and swap until the pointers cross
        swap(*low, *high);
        ++low;
        --high;
    }
}

optional<size_t> search(vector<dataType> & data, dataType key, SearchAlg searchType) {
    switch (searchType) {
        case Binary:
            if (!isSorted(data)) {
                return nullopt;
            }
            return binarySearch(data, key);
            break;
        case Linear:
            return linearSearch(data, key);
            break;
    }
}

bool sort(vector<dataType> & data, SortAlg sortType) {
    if (data.size() < 2) {
        return false;
    }
    switch (sortType) {
        case InsertA: {
            insertionSort(data);
            break;
        }
        case InsertD: {
            insertionSort(data);
            invert(data);
            break;
        }
        case BubbleA: {
            bubbleSort(data);
            break;
        }
        case BubbleD: {
            bubbleSort(data);
            invert(data);
            break;
        }
        case QuickA: {
            quickSort(data);
            break;
        }
        case QuickD: {
            quickSort(data);
            invert(data);
            break;
        }
    }
}

size_t binarySearch(const vector<dataType> & data, dataType key) {
    size_t low = 0;
    size_t high = data.size() - 1;
    size_t middle;
    while (low <= high) {
        middle = floor((low + high) / 2);
        if (data.at(middle) < key) {
            low = middle + 1;
            continue;
        }
        if (data.at(middle) > key) {
            high = middle - 1;
            continue;
        }
        return middle;
    }
    return -1;
}

size_t linearSearch(const vector<dataType> & data, dataType key) {
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i] == key) {
            cout << format("Num comparisons: {}\n", i + 1);
            return i;
        }
    }
    return -1;
}

void bubbleSort(vector<dataType> & data) {
    for (size_t i = 0; i < data.size(); ++i) {
        for (auto iter = data.begin(); iter < data.end() - i - 1; ++iter) {
            if (*iter > *(iter + 1)) {
                std::swap(*iter, *(iter + 1));
            }
        }
    }
}

// linear search needs an unordered list

void insertionSort(vector<dataType> & data) {
    for (size_t i = 1; i < data.size(); ++i) {
        for (size_t j = i; j > 0; --j) {
            auto left = j - 1;
            auto right = j;
            if (data[left] > data[right]) {
                std::swap(data[left], data[right]);
            }
            else {
                break;
            }
        }
    }
}

void quickSort(vector<dataType> & data, size_t left, size_t right) {
    dataType pivot = data[(left + right) / 2];
    
    size_t i = left;
    size_t j = right;
    
    while (i <= j) {
        while (data[i] < pivot) { ++i; }
        while (data[j] > pivot) { --j; }
        
        if (i <= j) {
            swap(data[i], data[j]);
            ++i;
            --j;
        }
    }
    
    if (left < j) {
        quickSort(data, left, j);
    }
    if (i < right) {
        quickSort(data, i, right);
    }
}

void quickSort(std::vector<dataType> & data) {
    if (data.size() == 2 && data[0] > data[1]) {
        swap(data[0], data[1]);
        return;
    }
    quickSort(data, 0, data.size() - 1);
}

void print(const vector<dataType> & data, bool sorted) {
#define RED "\033[38;2;240;6;10m"
#define GREEN "\033[38;2;0;153;51m"
    if (!sorted) {
        for (dataType datum: data) {
            cout << datum << ", ";
        }
        cout << endl;
    }
    else {
        for (size_t i = 0; i < data.size(); ++i) {
            int min = data.back();
            int max = data.front();
            const int rgb_max = 255;
            
            string color = "\033[38;2;";
            
            color.append(to_string(static_cast<int>(lerp(0, rgb_max, static_cast<double>(i) / static_cast<double>(data.size() - 1)))));
            color.append(";");
            color.append(to_string(static_cast<int>(lerp(rgb_max, 0, static_cast<double>(i) / static_cast<double>(data.size() - 1)))));
            color.append(";31m");
            cout << format("{}{}{},", color, data[i], RESET);
        }
    }
}

void enterData(vector<dataType> & data) {
    cout << format("Please enter the number of values to be inputted. There are currently {} values stored. -> ", data.size());
    size_t numValues = getNum<size_t>();
    cout << "\n";
    for (size_t i = 0; i < numValues; i++) {
        cout << format("Enter value #{}: ", i + 1);
        data.push_back(getNum<dataType>());
    }
}

