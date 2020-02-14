#include <iostream>

using namespace std;

int mystery1(int a, int b) {
    int c = a - b,
        d = (c >> 7) & 1,
        mystery = a - c * d;
    return mystery;
}

void mystery2(int values[], int i, int j) {
    cout << values[i] << endl;
    cout << values[j] << endl;

    values[i] = values[i] ^ values[j];
    values[j] = values[i] ^ values[j];
    values[i] = values[i] ^ values[j];

    cout << values[i] << endl;
    cout << values[j] << endl;
}

int mystery3(int x, int y) {
    int s, c;
    s = x ^ y;
    c = x & y;
    while (c != 0) {
        c = c << 1;
        x = s;
        y = c;
        s = x ^ y;
        c = x & y;
    }
    return s;
}

int main(int argc, char *argv[]) {
    // mystery1() test
    // cout << mystery1(3, 7) << endl;
    // cout << mystery1(8, 7) << endl;

    // mystery2() test
    // int arr1[4] = {1, 2, 3, 4};
    // mystery2(arr1, 0, 3);
    // mystery2(arr1, 1, 2);

    // mystery3() test
    cout << mystery3(5, 7) << endl;
    cout << mystery3(2, 8) << endl;
    

}

