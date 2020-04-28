/*******************************************************************************
 * Name        : maxsumdescent.cpp
 * Author      : Liam Brew
 * Version     : 1.0
 * Date        : 04.23.2020
 * Description : Dynamic programming solution to max sum descent problem.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

const char DELIMITER = ' ';
const int MAX_VAL_WIDTH = 2;  // Each number is a maximum of 2 digits.

int **values,  // This is your 2D array of values, read from the file.
    **sums;    // This is your 2D array of partial sums, used in DP.

int num_rows;  // num_rows tells you how many rows the 2D array has.
               // The first row has 1 column, the second row has 2 columns, and
               // so on...

int max_index;  // The index at of the last row at which the max sum is found.
                // Recorded for use in backtracking.

/**
 * Displays the 2D array of values read from the file in the format of a table.
 */
void display_table() {
    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < i + 1; j++) {
            if (j == i)  // Carriage return.
                cout << setw(MAX_VAL_WIDTH) << values[i][j] << endl;
            else  // Body value.
                cout << setw(MAX_VAL_WIDTH) << values[i][j] << DELIMITER;
        }
    }
}

/**
 * Returns the maximum sum possible in the triangle of values.
 * By starting at the top of the triangle and moving to adjacent numbers on the
 * row below, this function uses dynamic programming to build up another table
 * of partial sums.
 */
int compute_max_sum() {
    for (int i = 1; i < num_rows; i++) {
        // Builds the start & end of the row from the parent.
        sums[i][0] += sums[i - 1][0];
        sums[i][i] += sums[i - 1][i - 1];

        // Selects the maximum parent value to add to the current child.
        // Iterates through body of row (between start & end cols).
        for (int j = 1; j < i; j++) {
            sums[i][j] += max(sums[i - 1][j], sums[i - 1][j - 1]);
        }
    }

    int max = 0;  // Maximum sum.

    // Selects the maximum sum present in the final row.
    for (int k = 0; k < num_rows; k++) {
        if (sums[num_rows - 1][k] > max) {
            max = sums[num_rows - 1][k];
            max_index = k;
        }
    }

    return max;
}

/**
 * Returns a vector of ints with the values from the top to the bottom of the
 * triangle that comprise the maximum sum.
 */
vector<int> backtrack_solution() {
    vector<int> solution;

    if (num_rows == 1) {  // There is only 1 row => answer is the only present value.
        solution.push_back(values[num_rows - 1][max_index]);
        return solution;
    }

    int curr_index = max_index;
    for (int i = num_rows - 1; i >= 2; i--) {
        if (curr_index == i) {  // If its on the right-most edge.
            solution.insert(solution.begin(), values[i - 1][curr_index - 1]);
            curr_index--;
        } else if (sums[i - 1][curr_index] > sums[i - 1][curr_index - 1]) {  // Vertical shift.
            solution.insert(solution.begin(), values[i - 1][curr_index]);
        } else {  // Diagonal left shift.
            solution.insert(solution.begin(), values[i - 1][curr_index - 1]);
            curr_index--;
        }
    }
    if (num_rows > 0) {
        solution.push_back(values[num_rows - 1][max_index]);
        solution.insert(solution.begin(), values[0][0]);
    }

    return solution;
}

/**
 * Reads the contents of the file into the global 2D array 'values'. If
 * successful, the function also allocates memory for the 2D array 'sums'.
 */
bool load_values_from_file(const string &filename) {
    ifstream input_file(filename.c_str());
    if (!input_file) {
        cerr << "Error: Cannot open file '" << filename << "'." << endl;
        return false;
    }
    input_file.exceptions(ifstream::badbit);
    string line;
    vector<string> data;
    try {
        while (getline(input_file, line)) {
            data.push_back(line);
        }
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << filename << "'.";
        return false;
    }

    num_rows = data.size();  // Gets number of rows from the total lines (each line = 1 row needer).

    values = new int *[num_rows];  // Sizes values array.
    sums = new int *[num_rows];    // Sizes sums array.

    for (int i = 0; i < num_rows; i++) {
        // Integer parsing from read strings.
        stringstream ss(data[i]);

        string holder_string;
        vector<int> subvect;

        while (getline(ss, holder_string, DELIMITER)) {
            subvect.push_back(stoi(holder_string));
        }

        int *val_arr = new int[subvect.size()];  // Local values array.
        int *sum_arr = new int[subvect.size()];  // Local sums array.

        for (unsigned int x = 0; x < subvect.size(); x++) {
            // Writing of parsed integer to the values and sums array.
            val_arr[x] = subvect[x];
            sum_arr[x] = subvect[x];
        }

        values[i] = val_arr;
        sums[i] = sum_arr;
    }

    return true;
}

/**
 * Frees up the memory allocated for the 2D array of values and the 2D array of
 * partial sums.
 */
void cleanup() {
    for (int i = 0; i < num_rows; i++) {
        delete[] values[i];
        delete[] sums[i];
    }

    delete[] values;
    delete[] sums;
}

int main(int argc, char *const argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    string filename(argv[1]);
    if (!load_values_from_file(filename)) {
        return 1;
    }

    display_table();                                   // Table display.
    cout << "Max sum: " << compute_max_sum() << endl;  // Sum calculation.

    vector<int> solution = backtrack_solution();  // Backtracking.

    cout << "Values: [";
    for (unsigned int i = 0; i < solution.size(); i++) {  // Backtracking display.
        if (i == solution.size() - 1) {
            cout << solution[i];
        } else {
            cout << solution[i] << ", ";
        }
    }
    cout << "]" << endl;

    cleanup();  // Storage freeing.

    return 0;
}
