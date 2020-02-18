/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Liam Brew
 * Date        : 02.17.2020
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cctype>
#include <iostream>
#include <sstream>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.

    char alphabet[27] = "abcdefghijklmnopqrstuvwxyz";

    for (unsigned int i = 0; i < s.length(); i++) {
        bool found = false;
        for (int k = 0; k < 27; k++) {
            if (alphabet[k] == s[i]) {
                found = true;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.

    int count = 0;
    for (unsigned int i = 0; i < s.length(); i++) {
        int index = s[i] - 'a';

        if (((1 << index) & count) > 0) {
            return false;
        }

        count = count | (1 << index);
    }

    return true;
}

int main(int argc, char *const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.

    if (argc == 1) {
        cerr << "Usage: ./unique <string>" << endl;
        return 1;
    }

    if (argc > 2) {
        cerr << "Usage: ./unique <string>" << endl;
        return 1;
    }

    string input_str = argv[1];

    if (!is_all_lowercase(input_str)) {
        cerr << "Error: String must contain only lowercase letters." << endl;
        return 1;
    }

    if (!all_unique_letters(input_str)) {
        cerr << "Duplicate letters found." << endl;
        return 1;
    }

    cout << "All letters are unique." << endl;
    return 0;
}
