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

/*
    @Description
    Determines if all characters in the string are lowercase letters in the English alphabet.
    Analyzes the ASCII values of each char of the string to see if they fall within the set of lowercase letters.

    @Parameters
    const string &s: the string to analyze 

    @Return
    Boolean indicating if all chars of the string are lowercase letters. 

*/
bool is_all_lowercase(const string &s) {
    for (auto &letter : s) {
        // For every char of the string.
        if (letter < 'a' || letter > 'z') {
            // Is the char outside the range of lowercase letters?
            return false;
        }
    }
    return true;
}

/*
    @Description
    Determines if all chars in the string are unique (no duplicates). 
        *Assumes that all chars are lowercase English letters.
        *Examines each char of the string. Performs left shifts on 1 equal to the difference of that char and a.
        *If the bitwise AND of the result of those shifts and the original set of bits is true, then that char already exists.
        *Otherwise, the set of bits is updated to be the bitwise OR of itself and the result of the shifts on the char.

    @Parameters
    const string &s: the string to analyze

    @Return
    Boolean indicating if all chars of the string are unique.

*/
bool all_unique_letters(const string &s) {
    // The original set of 32 bits.
    unsigned int set = 0;

    for (char const &c : s) {
        // For every char in the string. 

        int setter;
        // Result of bitshifts. 
        setter = 1 << (c - 'a');

        if (setter & set) {
            // Is the bitwise AND of the result of the bitshifts and the set of bits true? 
            return false;
        }

        // Set of bits update.
        set |= setter;
    }
    return true;
}

int main(int argc, char *const argv[]) {

    if (argc == 1) {
        // Is the argument missing?
        cerr << "Usage: ./unique <string>" << endl;
        return 1;
    }

    if (argc > 2) {
        // Are there too many arguments?
        cerr << "Usage: ./unique <string>" << endl;
        return 1;
    }

    // Assignment for ease of use. 
    string input_str = argv[1];

    if (!is_all_lowercase(input_str)) {
        // Are all chars of the string lowercase?
        cerr << "Error: String must contain only lowercase letters." << endl;
        return 1;
    }

    if (!all_unique_letters(input_str)) {
        // Are all chars of the string unique?
        cerr << "Duplicate letters found." << endl;
        return 1;
    }

    cout << "All letters are unique." << endl;
    return 0;
}
