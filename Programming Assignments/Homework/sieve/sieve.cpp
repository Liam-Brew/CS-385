/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Liam Brew
 * Date        : February 6, 2020
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

/*
    @Description
    Uses the Sieve of Eratosthenes mathematical algorithm to determine and list the number of primes up to a number.

    @Parameters
    int limit: the number up to which the algorithm will evaluate
*/
class PrimesSieve {
   public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete[] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

   private:
    // Instance variables
    bool* const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) : is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

/*
    @Description
    Prints the results of the sieve calculation in the specific format.
        --If the results fit on one line then there is a uniform format of one space between values.
        --If the results require multiple lines then this distance is based on the width of the largest prime.
        There are a maximum of 80 characters per line.
*/
void PrimesSieve::display_primes() const {
    // Determines the maximum prime width and thereby the maximum number of primes per row.
    const int max_prime_width = num_digits(max_prime_);
    const int primes_per_row = 80 / (max_prime_width + 1);

    // Labels.
    cout << endl;
    cout << "Number of primes found: " << num_primes() << endl;
    cout << "Primes up to " << limit_ << ":" << endl;

    // Keeps track of the number of columns (indicating when to perform a carriage return).
    int col = 0;

    for (int i = 2; i < limit_ + 1; i++) {
        // Starts at index 2.

        if (col == primes_per_row) {
            // Last space reached: perform a carriage return.
            cout << endl;
            col = 0;
        }

        if (is_prime_[i] == true) {
            // If this number is prime and therefore is to be printed.

            if (col != 0) {
                // Single-space padding for single-line output.
                cout << " ";
            }
            if (num_primes() > primes_per_row) {
                // Scales the distance based on the width of the largest prime.
                cout << setw(max_prime_width) << i;
            } else {
                // Prints the value of that index (the prime number).
                cout << i;
            }
            col++;
        }
    }
    cout << endl;
}

/*
    @Description
    Calculates the number of primes by performing an iterative search over the array for true values. 
*/
int PrimesSieve::count_num_primes() const {
    int count = 0;
    for (int i = 2; i < limit_ + 1; i++) {
        // Starts at index 2.
        if (is_prime_[i] == true) {
            // True = prime has been pre-determined by the sieve() method.
            count++;
        }
    }
    return count;
}

/*
    @Description
    Calculates the number of primes up to the limit number. Iterates through a true boolean array of size limit + 1.
    If an index (number) is contains true, then all index locations indicated by multiples of that number are marked false (as they are composite numbers).
    The values of the indexes containing true at the end of this function are prime numbers 

*/
void PrimesSieve::sieve() {
    for (int i = 2; i < limit_ + 1; i++) {
        // Sets the value of every index of the array to be true.
        is_prime_[i] = true;
    }
    for (int i = 2; i < sqrt(limit_); i++) {
        // Iterates through every number up to the square root of the limit (due to the i^2 operation performed later).
        if (is_prime_[i] == true) {
            // If the index contains a true value.
            for (int j = i * 2; j < limit_ + 1; j = j + i) {
                // Sets all multiples of that index to false.
                is_prime_[j] = false;
            }
        }
    }
    for (int y = 2; y < limit_ + 1; y++) {
        // Determines the maximum prime number of the list.
        if (is_prime_[y] == true) {
            max_prime_ = y;
        }
    }
    // Sets the total number of prime numbers.
    num_primes_ = count_num_primes();
}

/*
    @Description
    Calculates the amount of digits that are in a number by dividing it by 10 until the resultant is 0.
    Every successful division represents an additional digit.

    @Parameters
    int num : the number to analyze
*/
int PrimesSieve::num_digits(int num) {
    int count = 1;
    while (num / 10 != 0) {
        count++;
        num = num / 10;
    }
    return count;
}

int main() {
    cout << "**************************** "
         << "Sieve of Eratosthenes"
         << " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if (!(iss >> limit)) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // Creates a sieve object using the passed-in limit.
    PrimesSieve sieve1(limit);

    // Displays the prime numbers of up to the limit.
    sieve1.display_primes();

    return 0;
}
