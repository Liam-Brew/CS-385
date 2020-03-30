/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Liam Brew
 * Version     : 1.0
 * Date        : 03.30.2020
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    long count = 0;
    for (int i = 0; i < length - 1; i++) {
        for (int j = i + 1; j < length; j++) {
            if (array[i] > array[j]) {
                count++;
            }
        }
    }
    return count;
}

/**
  * Counts the number of inversions in an array in theta(n lg n) time.
  * 
  */
long count_inversions_fast(int array[], int length) {
    // Temporary array.
    int *scratch = new int[length];

    long result = mergesort(array, scratch, 0, length - 1);
    delete[] scratch;
    return result;
}

static long mergesort(int array[], int scratch[], int low, int high) {
    long count = 0;

    if (low < high) {
        int mid = low + (high - low) / 2;
        int L = low;
        int H = mid + 1;
        count += mergesort(array, scratch, low, mid);
        count += mergesort(array, scratch, mid + 1, high);

        // For every bounded index.
        for (int k = low; k < high + 1; k++) {
            if (L <= mid && (H > high || array[L] <= array[H])) {
                // If L is less than midpoint and H is greater than high or array[L] is less than or equal to array[H] (sorting).
                scratch[k] = array[L];
                L++;
            } else {
                scratch[k] = array[H];
                H++;

                // Out of order: increment inversion count.
                count += mid - L + 1;
            }
        }
        for (int k = low; k < high + 1; k++) {
            array[k] = scratch[k];
        }
    }
    return count;
}

int main(int argc, char *argv[]) {
    // Too many arguments.
    if (argc > 2) {
        cout << "Usage: ./inversioncounter [slow]" << endl;
        return 1;
    }

    // If there is an optional parameter, is it correct?
    if (argc == 2) {
        string s1 = argv[1];
        if (s1.compare("slow") != 0) {
            cout << "Error: Unrecognized option '" << s1 << "'." << endl;
            return 1;
        }
    }

    // Slow or fast based on parameters.
    bool slow = false;
    if (argc == 2) slow = true;

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
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

    int size = values.size();

    if (size == 0) {
        cout << "Error: Sequence of integers not received." << endl;
        return 1;
    }

    string print = "Number of inversions: ";

    // No inversions possible.
    if (size == 1) {
        cout << print << "0" << endl;
        return 0;
    }

    // Vector to array for counting.
    int *vals = &values[0];

    // Fast count
    if (!slow) {
        cout << print << count_inversions_fast(vals, size) << endl;
        return 0;
    }

    // Slow count.
    cout << print << count_inversions_slow(vals, size) << endl;
    return 0;
}
