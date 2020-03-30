#include <iostream>
using namespace std;

struct Node {
    int key;
    Node *left, *right;
};

void inOrder(Node *n) {
    if (n != nullptr) {
        inOrder(n->left);
        cout << n->key << endl;
        inOrder(n->right);
    }
}

int sum_values(Node *n) {
    if (n == nullptr) {
        return 0;
    }
    return sum_values(n->left) + n->key + sum_values(n->right);
}

/*
    # Insertion into BST
    T(n) = 2T(n/2) + theta(1)

    a = 2
    b = 2
    f(n) = n^0 => d = 0
    
    a _ b^d
    a > 2^0

    T(n) is a number of theta(n^lg(2)) = theta(n)


    50
   /
  30       => Not a BST
 /  \
20   60

*/
