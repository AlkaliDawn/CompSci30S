#include <algorithm>
#include <iostream>
#include <conio.h>
#include <cstdio>
#include <random>
#include <format>
#include "bartlett.h"

using dataType = long int;
using namespace std;

enum SortAlg : uint8_t {
    InsertA, InsertD, BubbleA, BubbleD, QuickA, QuickD
};

enum SearchAlg : uint8_t {
    Binary, Linear
};

bool isSorted(const vector<dataType> & data);

void invert(vector<dataType> & data);

bool sort(vector<dataType> & data, SortAlg sortType);
optional<size_t> search(vector<dataType> & data, SearchAlg searchType);

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
    
    printf("There are currently {} {} data points,Do you want to (S)earch, (O)rder, or (E)nter Data?", data.size(), (sorted ? "sorted" : "unsorted"));
    input;
    
    
    cout << "Press any key to exit...";
    _getch();
    return 0;
}

bool isSorted(const vector<dataType> & data) {
    if (data.size() == 1) {
        return true;
    }
    
    for (int i = 1; i < data.size(); ++i) {
        if (data[i - 1] > data[i]) {
            return false;
        }
    }
    
    return true;
}

void invert(vector<dataType> & data) {
    if (data.size() < 2) {
        return;
    }
    if (data.size() == 2) {
        swap(data[0], data[1]);
        return;
    }
    auto low = data.begin();
    auto high = data.end();
    while (low <= high) {
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