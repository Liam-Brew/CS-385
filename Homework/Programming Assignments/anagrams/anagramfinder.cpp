/*******************************************************************************
 * Name        : anagramfinder.cpp
 * Author      : Liam Brew
 * Version     : 1.0
 * Date        : 05.06.2020
 * Description : Scans a text file of words and finds the longest words that have one or more anagrams present.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Data Fields.
vector<string> words;

// Functions.

/**
 * Returns a boolean indicating if every character of the input string is either an upper or lower case letter, a hyphen or an apostrophe.
*/
bool char_check(string str) {
    for (char &character : str) {                                    // Check for illegal characters.
        bool upper_case = (character >= 'a') && (character <= 'z');  // If character is uppercase.
        bool lower_case = (character >= 'A') && (character <= 'Z');  // If character is lowercase.
        bool hyphen = character == '-';                              // If character is a hyphen.
        bool apostrophe = character == '\'';                         // If character is an apostrophe.

        if (!(upper_case || lower_case || hyphen || apostrophe))
            return false;
    }
    return true;
}

bool load_words(const string &filename) {
    //TODO
    ifstream input_file(filename.c_str());
    if (!input_file) {
        cerr << "Error: File '" << filename << "' not found." << endl;
        return false;
    }
    input_file.exceptions(ifstream::badbit);
    string line;
    try {
        while (getline(input_file, line)) {
            if (char_check(line)) words.push_back(line);
        }
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << filename << "'.";
        return false;
    }

    return true;
}

void clean_up() {
    //TODO
}

int main(int argc, char *const argv[]) {
    //TODO
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <dictionary file>" << endl;
        return 1;
    }
    string filename(argv[1]);
    if (!load_words(filename)) {
        return 1;
    }
    for (string &str : words) {
        cout << str << endl;
    }

    return 0;
}