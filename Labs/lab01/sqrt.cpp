/*******************************************************************************
 * Name    : sqrt.cpp
 * Author  : Liam Brew
 * Version : 1.0
 * Date    : January 28, 2020
 * Description : Computes the square root of a command-line argument using Newton's method.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

using namespace std;

double sqrt(double num, double epsilon) {
    if (num < 0) {
        return numeric_limits<double>::quiet_NaN();
    } else if ((num == 0) | (num == 1)) {
        return num;
    } else {
        double last_guess = num;
        double next_guess = (last_guess + (num / last_guess)) / 2;
        while (abs(last_guess - next_guess) > epsilon) {
            last_guess = next_guess;
            next_guess = (last_guess + (num / last_guess)) / 2;
        }
        return next_guess;
    }
}

int main(int argc, char* argv[]) {
    double num = 0, epsilon = 1e-7;
    istringstream iss;

    if (argc != 2) {
        if (argc == 3) {
            iss.str(argv[2]);
            if (!(iss >> epsilon)) {
                cout << "Error: Epsilon argument must be a positive double." << endl;
                return 1;
            }
            iss.clear();
            if (epsilon <= 0) {
                cout << "Error: Epsilon argument must be a positive double." << endl;
                return 1;
            }
        } else {
            cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
            return 1;
        }
    }

    iss.str(argv[1]);
    if (!(iss >> num)) {
        cout << "Error: Value argument must be a double." << endl;
        return 1;
    }
    iss.clear();

    cout << fixed << setprecision(8) << sqrt(num, epsilon) << endl;
}
