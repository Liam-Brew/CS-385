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
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Data Fields.
vector<vector<string>> results;

map<string, vector<string>> new_method;
vector<string> new_results;

int word_count = 0;
unsigned int max_size = 0;  // Maximum word size.
int max_anagram_size = 0;   // Maximum anagram size.

// Functions.

// ###### Character Validation ######

/**
 * Returns a boolean indicating if a character is upper case.
*/
bool upper_case(char character) {
    return (character >= 'A') && (character <= 'Z');
}

/**
 * Returns a boolean indicating if a character is lower case.
*/
bool lower_case(char character) {
    return (character >= 'a') && (character <= 'z');
}

/**
 * Returns a boolean indicating if a character is a hyphen.
*/
bool hyphen(char character) {
    return character == '-';
}

/**
 * Returns a boolean indicating if a character is an apostrophe.
*/
bool apostrophe(char character) {
    return character == '\'';
}

/**
 * Returns a boolean indicating if every character of the input string valid.
*/
void char_check(string &str) {
    //TODO
    for (char &character : str) {  // Check for illegal characters.
        if (upper_case(character)) {
            continue;
        } else if (lower_case(character)) {
            continue;
        } else if (hyphen(character)) {
            continue;
        } else if (apostrophe(character)) {
            continue;
        } else {
            return;
        }
    }
    string sorted = str;
    transform(sorted.begin(), sorted.end(), sorted.begin(), ::tolower);

    sort(sorted.begin(), sorted.end());
    if (new_method.find(sorted) == new_method.end()) {
        vector<string> temp = {str};
        new_method.insert({sorted, temp});
    } else {
        new_method[sorted].push_back(str);
    }

    if (str.size() > max_size) {
        max_size = str.size();
    }

    word_count++;
    return;
}

// ###### File Reading ######

/**
 * Reads the words from the input file and determines if they are valid.
*/
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
            char_check(line);
        }
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << filename << "'.";
        return false;
    }

    return true;
}

// ###### Anagram Detection ######

bool end_early(string str) {
    for (auto word : new_results) {
        if (word == str) return true;
    }

    return false;
}

void find_anagrams() {
    //TODO

    for (unsigned int i = max_size; i >= 0; i--) {
        for (auto const &pair : new_method) {
            unsigned int first = pair.first.size();
            vector<string> second = pair.second;
            if (first == i) {
                if (second.size() > 1) {
                    sort(second.begin(), second.end());

                    for (auto str : second) {
                        new_results.push_back(str);
                    }
                    max_anagram_size = i;
                }
            }
        }
        return;
    }
}

void display_anagrams() {
    // TODO
    for (unsigned int i = 1; i < new_results.size(); i++) {
        string curr_str = new_results[i];
        string prev_str = new_results[i - 1];

        if (i == 1) {
            cout << prev_str << endl;
        }

        string curr_sort = curr_str;
        string prev_sort = prev_str;

        transform(curr_sort.begin(), curr_sort.end(), curr_sort.begin(), ::tolower);
        transform(prev_sort.begin(), prev_sort.end(), prev_sort.begin(), ::tolower);

        sort(curr_sort.begin(), curr_sort.end());
        sort(prev_sort.begin(), prev_sort.end());

        if (curr_sort != prev_sort) {
            cout << endl;
            cout << curr_str << endl;
        } else {
            cout << curr_str << endl;
        }
    }
}

void clean_up() {
    new_method.clear();
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

    if (word_count == 0)
        cout << "No anagrams found." << endl;
    else {
        find_anagrams();

        if (max_anagram_size == 0)
            cout << "No anagrams found." << endl;
        else {
            cout << "Max anagram length: " << max_anagram_size << endl;
            display_anagrams();
        }
    }
    clean_up();
    return 0;
}
