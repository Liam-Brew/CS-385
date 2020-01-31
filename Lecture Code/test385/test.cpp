#include <iostream>
#include <sstream>

using namespace std;

double max(double a, double b){
    return a > b ? a : b;
}

int main(int argc, char * argv[]){
    double m, n;
    istringstream iss;

    if(argc != 3){
        cerr << "Usage: " << argv[0] << " <double m> <double n>" <<endl;
        return 1;
    }
    
    iss.str(argv[1]);
    if(!(iss >> m)){
        cerr << "Error: The first argument is not a valid double." << endl;
        return 1;
    }

    iss.clear();
    iss.str(argv[2]);
    if(!(iss >> n)){
        cerr << "Error: The first argument is not a valid double." << endl;
        return 1;
    }

    cout << "max(" << m << ", " << n << ") = " << max(m, n)<< endl;
    return 0;
}