/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Liam Brew
 * Date        : February 24th, 2020
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int numStairs;

/*
    @Description
    Calculates the different combinations of ways to climb num_stairs. Stairs can be climbed either 1, 2 
    or 3 steps at a time.

    @Parameters
    int num_stairs : the number of stairs to climb

    @Return
    A vector of integer vectors that detail the steps of each possible solution.
*/
vector<vector<int>> get_ways(int num_stairs) {
    // Solution set.
    vector<vector<int>> result;

    if (num_stairs <= 0) {
        // Recursive base case.
        result.push_back(vector<int>());
    } else {
        // For every possible step jump (1 to 3).
        for (int i = 1; i < 4; i++) {
            if (num_stairs >= i) {
                // If top of stairs cannot be reached in this call.

                // Recursive call.
                vector<vector<int>> answer = get_ways(num_stairs - i);

                // For every sub-vector within the recursive call's vector.
                for (auto &index : answer) {
                    // Adds the current jump value to the vector.
                    index.insert(index.begin(), i);
                }
                // Combines the recursive call vector with the solution set.
                result.insert(result.end(), answer.begin(), answer.end());
            }
        }
    }
    return result;
}

/*
    @Description
    Calculates the amount of digits that are in a number by dividing it by 10 until the resultant is 0.
    Every successful division represents an additional digit.

    @Parameters
    int num : the number to analyze
*/
int num_digits(int num) {
    int count = 1;

    while (num / 10 != 0) {
        count++;
        num = num / 10;
    }
    return count;
}

/*
    @Description
    Prints the solution list in an easy to read format. Iterates through the input vector, and for each sub-vector 
    labels that solution and prints its steps on its own line.

    @Parameters
    const vector<vector<int>> &ways : the address of the solution step (returned from get_ways())
*/
void display_ways(const vector<vector<int>> &ways) {
    int solutions = ways.size();
    int max_width = num_digits(solutions);

    // Determines summary statement to ensure correct grammar.
    if (solutions > 1) {
        cout << solutions << " ways to climb " << numStairs << " stairs." << endl;
    } else {
        cout << solutions << " way to climb " << numStairs << " stair." << endl;
    }

    // Solution label.
    int i = 1;

    // For each solution of the solution set
    for (auto &shallow : ways) {
        // Right aligns label to the width of the largest label.
        cout << right << setw(max_width) << i++;
        cout << ". [";

        // Prints the steps of the solution
        for (unsigned int deep = 0; deep < shallow.size() - 1; deep++) {
            cout << shallow[deep] << ", ";
        }
        cout << shallow[shallow.size() - 1];
        cout << "]" << endl;
    }
}

int main(int argc, char *const argv[]) {
    // If there are an incorrect number of arguments.
    if (argc != 2) {
        cout << "Usage: ./stairclimber <number of stairs>" << endl;
        return 1;
    }
    istringstream iss(argv[1]);

    // If the argument is not a valid integer
    if (!(iss >> numStairs) || numStairs < 1) {
        cout << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }

    display_ways(get_ways(numStairs));
    return 0;
}
