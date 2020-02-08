#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class MyPoint{
public:
    // Constructor that uses an initializer list.
    MyPoint(int x, int y, float z) : x_{x}, y_{y}, z_{z} { }

    // Destructor frees up memory allocated by the class.
    ~MyPoint(){
        cout << "Destructor called." << endl;
    }

    // Methods that do not modify member variables should be declared const.
    void print_coords() const{
        cout << "(x, y, z) = (" << x_ << ", " << y_ << ", " << fixed << setprecision(2) << z_ << ")" << endl;
    }

    // Accessor.
    int get_x() const{
        return x_;
    }

    // Mutator.
    void set_x(int x){
        x_ = x;
    }

private:
    int x_, y_;
    float z_;

};

// Takes in a vector and displays each one of them.
// Use reference as values will not be modified.
void display_points(const vector<MyPoint> &points){
    for(auto it = points.cbegin(); it != points.cend(); ++it){
        it -> print_coords();
    }
}

int main(){
    int x, y;
    
    MyPoint point1(5, 7.7, 1.24);
    MyPoint point2(1, 2, 3);
    MyPoint point3(4, 5, 6);

    vector<MyPoint> points;
    points.push_back(point1);
    points.push_back(point2);
    points.push_back(point3);

    vector<MyPoint> points_above_two;
    for (const auto &point : points){
        if(point.get_x() > 2){
            points_above_two.push_back(point);
        }
    }

    display_points(points_above_two);

    cout << "Input x: ";
    cin >> x;

    cout << "Input y: ";
    cin >> y;

    MyPoint *point4 = new MyPoint(x, y, 7);
    point4 -> print_coords();
    delete point4;

    return 0;
}
