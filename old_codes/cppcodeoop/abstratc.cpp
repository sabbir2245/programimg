#include <iostream>
using namespace std;

// Abstract class with a pure virtual function
class Shape {
public:
    virtual void draw() = 0; // pure virtual function
};

// Derived class
class Circle : public Shape {
public:
    void draw() override {
        cout << "Drawing a Circle" << endl;
    }
};

// Another derived class
class Square : public Shape {
public:
    void draw() override {
        cout << "Drawing a Square" << endl;
    }
};

int main() {
    // Shape shape; // Error: Cannot instantiate an abstract class

    Shape* shape1 = new Circle();
    Shape* shape2 = new Square();

    shape1->draw(); // Output: Drawing a Circle
    shape2->draw(); // Output: Drawing a Square

    delete shape1;
    delete shape2;

    return 0;
}
