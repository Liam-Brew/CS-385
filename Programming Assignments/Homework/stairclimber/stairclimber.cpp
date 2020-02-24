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

vector<vector<int>> get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.

    vector<vector<int>> result = {};

    if (num_stairs <= 0) {
        result.push_back({});
    } else {
        for (int i = 1; i < 4; i++) {
            if (num_stairs >= i) {
                vector<vector<int>> answer = get_ways(num_stairs - 1);
                for (auto index : answer) {
                    index.push_back(i);
                }
                result.insert(result.begin(), answer.begin(), answer.end());
            }
        }
    }
    return result;
}

void display_ways(const vector<vector<int>> &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.

    for (vector<int> shallow : ways) {
        cout << "[";
        for (int deep : shallow) {
            cout << deep << ", ";
        }
    }
}

int main(int argc, char *const argv[]) {
}
