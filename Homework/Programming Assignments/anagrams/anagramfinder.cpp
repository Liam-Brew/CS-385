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
map<string, vector<string>> words;  // Collection of each word mapped to its lower-case letter compisition.
vector<vector<string>> anagrams;    // Collection of different sets of equal-length anagrams.

int word_count = 0;         // Number of legal words read from the file.
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
 * Determines if a word is legal. If so, the word is added to the map at a key representing the word's alphabetized letter components. 
*/
void char_check(string &str) {
    //TODO
    for (char &character : str) {  // Check for illegal characters.
        if (upper_case(character) || lower_case(character) || hyphen(character) || apostrophe(character)) {
            continue;
        } else {
            return;
        }
    }

    string sorted = str;
    transform(sorted.begin(), sorted.end(), sorted.begin(), ::tolower);  // Alphabetizes the word's letter components and translates them to
    sort(sorted.begin(), sorted.end());                                  // lower-case notation to ensure uniformity.

    if (words.find(sorted) == words.end()) {  // If a key for that component structure already exists,
        vector<string> temp = {str};          //append it to the vector already present.
        words.insert({sorted, temp});
    } else {  // If no key exists then create a new value vector there.
        words[sorted].push_back(str);
    }

    if (str.size() > max_size) {  // Keeps track of the maximum word size for later use.
        max_size = str.size();
    }

    word_count++;  // Keeps track of word count for use in edge-condition assessment.
    return;
}

// ###### File Reading ######

/**
 * Reads the words from the input file and determines if they are valid.
*/
bool load_words(const string &filename) {
    ifstream input_file(filename.c_str());
    if (!input_file) {
        cerr << "Error: File '" << filename << "' not found." << endl;
        return false;
    }
    input_file.exceptions(ifstream::badbit);
    string line;
    try {
        while (getline(input_file, line)) {
            char_check(line);  // Reads the word on every line.
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
 * Examines the map, starting with the largest word size for efficiency purposes, to determine if anagrams are present.
 * In this case an anagram represents a key which has two or more values associated with it (two or more words).
*/

void find_anagrams() {
    for (unsigned int i = max_size; i >= 0; i--) {  // Starts at the maximum size to reduce the number of iterations on average.
        for (auto const &pair : words) {
            unsigned int first = pair.first.size();
            vector<string> second = pair.second;

            if (first == i) {             // If the length of the key is equal to the length being searched for.
                if (second.size() > 1) {  // If there are multiple words for that key.
                    vector<string> set;
                    sort(second.begin(), second.end());  // Alphabetize the present words.

                    for (auto str : second) {
                        set.push_back(str);
                    }
                    anagrams.push_back(set);  // Store each set of related words in their own vector to assist in later ordering.
                    max_anagram_size = i;
                }
            }
        }
        return;
    }
}

/**
 * Alphabetizes the order of the sets of anagrams by comparing each of their first words (all sets themselves have already been alphabetized.)
 * Once finished, this order is displayed on the screen.
*/
void display_anagrams() {
    vector<string> results_headers;

    for (auto vect : anagrams) {  // Adds the first word (already alphabetized) of each set to a working vector.
        string str = vect[0];
        transform(str.begin(), str.end(), str.begin(), ::tolower);  // Translates word to lower-case to ensure uniformity.

        results_headers.push_back(str);
    }

    if (results_headers.size() > 1) sort(results_headers.begin(), results_headers.end());  // If there exists multiple headers alphabetize them.

    for (unsigned int i = 0; i < results_headers.size(); i++) {
        string tag = results_headers[i];
        sort(tag.begin(), tag.end());  // Alphabetizes the tag to bring it in-line to the map's key convention.

        sort(words[tag].begin(), words[tag].end());  // Ensures the values at that key are alphabetized.

        for (auto str : words[tag]) {  // Prints the values.
            cout << str << endl;
        }
        cout << endl;
    }
}

/**
 * Removes the map from memory.
*/
void clean_up() {
    words.clear();
}

int main(int argc, char *const argv[]) {
    if (argc != 2) {  // Invalid invocation.
        cerr << "Usage: " << argv[0] << " <dictionary file>" << endl;
        return 1;
    }
    string filename(argv[1]);
    if (!load_words(filename)) {  // Read file error.
        return 1;
    }

    if (word_count == 0)  // No words are present.
        cout << "No anagrams found." << endl;
    else {
        find_anagrams();

        if (max_anagram_size == 0)  // No anagrams are present.
            cout << "No anagrams found." << endl;
        else {
            cout << "Max anagram length: " << max_anagram_size << endl;
            display_anagrams();
        }
    }
    clean_up();
    return 0;
}
