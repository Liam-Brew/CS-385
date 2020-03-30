/*******************************************************************************
 * Name          : quickselect.cpp
 * Author        : Liam Brew
 * Pledge        : I pledge my honor that I have abided by the Stevens Honor System.
 * Date          : March 23rd, 2020
 * Description   : Implements the quickselect algorithm found on page 160 in
 *                 Algorithms, 3e by Anany Levitin.
 ******************************************************************************/
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

/*
    @Description
    Performs a Lomuto Partition on the inputted array. 

    @Parameters
    array: array to be partioned
    left: left bound
    right: right bound
*/
size_t lomuto_partition(int array[], size_t left, size_t right) {
    // Assignments.
    int pivot = array[left];
    size_t s = left;

    // For every index.
    for (size_t i = left + 1; i <= right; i++) {
        // If the current index is lies than the pivot swap it with the post-increment left marker.
        if (array[i] < pivot) swap(array[++s], array[i]);
    }

    swap(array[left], array[s]);

    return s;
}

/*
    @Description
    Preforms a quick select on the inputted array looking for the kth smallest element.

    @Parameters
    array: array to search through
    left: left bound
    right: right bound
    k: key to search for
*/
int quick_select(int array[], size_t left, size_t right, size_t k) {
    // Singleton list : only 1 option, breakout.
    if (left == right) return array[left];

    // Pivot assignment and breakout checking.
    size_t pivot = lomuto_partition(array, left, right);
    if (pivot == k - 1) return array[pivot];

    // Pivot is less than k ... somewhere in [Left, Pivot)
    if (pivot > k - 1) return quick_select(array, left, pivot - 1, k);

    // Pivot is more than k ... somewhere in (Pivot, Right]
    else
        return quick_select(array, pivot + 1, right, k);
}

/*
    @Description
    Wrapper function for quick_select().

    @Parameters
    array: array to search through
    length: length of array by which to derive left and right bounds
    k: key to search for
*/
int quick_select(int array[], const size_t length, size_t k) {
    return quick_select(array, 0, length - 1, k);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <k>" << endl;
        return 1;
    }

    int k;
    istringstream iss;
    iss.str(argv[1]);
    if (!(iss >> k) || k <= 0) {
        cerr << "Error: Invalid value '" << argv[1] << "' for k." << endl;
        return 1;
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    iss.clear();
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    int num_values = values.size();
    if (num_values == 0) {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }

    // Grammar work.
    if (k > num_values) {
        if (num_values == 1) {
            cerr << "Error: Cannot find smallest element " << k << " with only " << num_values << " value." << endl;
        } else {
            cerr << "Error: Cannot find smallest element " << k << " with only " << num_values << " values." << endl;
        }
        return 1;
    }

    // Selection invokation.
    int *vals = &values[0];  //vector => array to pass into function
    cout << "Smallest element " << k << ": " << quick_select(vals, num_values, k);
  
    return 0;
}
