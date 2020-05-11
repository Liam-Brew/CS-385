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

map<unsigned int, vector<string>> words;  // Words imported from dictionary.

int word_count = 0;
unsigned int max_size = 0;          // Maximum word size.
unsigned int max_anagram_size = 0;  // Maximum anagram size.
bool anagram_found = false;

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
bool char_check(string str) {
    //TODO
    for (char &character : str) {  // Check for illegal characters.
        if (upper_case(character) || lower_case(character) || hyphen(character) || apostrophe(character))
            continue;
        else
            return false;
    }
    return true;
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
            if (char_check(line)) {
                if (words.find(line.size()) == words.end()) {  // There are no words of that size.
                    vector<string> temp;
                    temp.push_back(line);
                    words.insert({line.size(), temp});
                } else {
                    words[line.size()].push_back(line);
                }
                if (line.size() > max_size) max_size = line.size();  // Update max size.
                word_count++;
            }
        }
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << filename << "'.";
        return false;
    }

    return true;
}

// ###### Anagram Detection ######

/**
 * Determines the amount of each character present in a string.
*/
vector<int> break_down(string str) {
    //TODO
    vector<int> word;

    // Populates every subvector with 28 zeros (alphabet + 2 punctuation marks).
    for (int i = 0; i < 28; i++) {
        word.push_back(0);
    }

    for (auto character : str) {
        if (upper_case(character))
            word[character - 65] += 1;
        else if (lower_case(character))
            word[character - 97] += 1;
        else if (hyphen(character))
            word[26] += 1;
        else
            word[27] += 1;
    }
    return word;
}

bool end_early(string str) {
    for (auto set : results) {
        for (auto word : set) {
            if (word == str) return true;
        }
    }
    return false;
}

void find_anagrams() {
    //TODO

    for (unsigned int i = max_size; i >= 1; i--) {
        vector<vector<int>> current_size;
        for (auto word : words[i]) {  // Breaks down all words of this size.
            current_size.push_back(break_down(word));
        }

        for (unsigned int j = 0; j < current_size.size() - 1; j++) {
            bool set_found = false;
            vector<string> answer;

            if (end_early(words[i][j])) continue;

            for (unsigned int k = j + 1; k < current_size.size(); k++) {
                if (current_size[j] == current_size[k]) {
                    if (!(find(answer.begin(), answer.end(), words[i][k]) != answer.end())) {
                        set_found = true;
                        answer.push_back(words[i][k]);
                    }
                    anagram_found = true;
                    max_anagram_size = max_size;
                }
            }
            if (set_found) {
                answer.push_back(words[i][j]);
                results.push_back(answer);
                continue;
            }
        }

        if (results.size() > 0) return;
    }
    return;
}

void swap_word(vector<string> set, int a, int b) {
    //TODO
    string temp = set[a];
    set[a] = set[b];
    set[b] = temp;
}

void swap_set(int a, int b) {
    //TODO
    vector<string> temp = results[a];
    results[a] = results[b];
    results[b] = temp;
}

vector<string> alphabetize_set(vector<string> set) {
    sort(set.begin(), set.end());

    return set;
}

void alphabetize_results() {
    for (unsigned int i = 0; i < results.size() - 1; i++) {
        if (results[i][0][0] > results[i + 1][0][0]) swap_set(i, i + 1);
    }
}

void display_anagrams() {
    //TODO
    for (unsigned int i = 0; i < results.size(); i++) {
        results[i] = alphabetize_set(results[i]);
    }
    alphabetize_results();
    for (auto set : results) {
        for (auto str : set) {
            cout << str << endl;
        }
        cout << endl;
    }

    // // alphabetize_results();
    // for (auto set : results) {
    //     for (auto str : set) {
    //         cout << str << endl;
    //     }
    //     cout << endl;
    // }
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

    // cout << word_count << endl;
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

    return 0;
}