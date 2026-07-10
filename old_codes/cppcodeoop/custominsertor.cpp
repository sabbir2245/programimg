#include <iostream>
using namespace std;

class MyClass {
    int x, y;

public:
    // Default constructor
    MyClass() : x(0), y(0) {}

    // Parameterized constructor (optional)
    MyClass(int a, int b) : x(a), y(b) {}

    // Overloading >> (Input)
    friend istream& operator>>(istream& in, MyClass& obj) {
       // cout << "Enter values for x and y: ";
        in >> obj.x >> obj.y;
        return in;
    }

    // Overloading << (Output)
    friend ostream& operator<<(ostream& out, const MyClass& obj) {
        out << "(" << obj.x << ", " << obj.y << ") ";
        return out;
    }
};

int main() {
    MyClass ob1, ob2;

    cin >> ob1 >> ob2;  // Calls overloaded >>
    cout << ob1 << ob2 << endl;  // Calls overloaded <<

    return 0;
}
