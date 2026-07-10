#include <iostream>
using namespace std;

class Base {
public:
    virtual void display() {   // Virtual function
        cout << "Base class display()" << endl;
    }
};

class Derived : public Base {
public:
    void display() {   // Overriding function
        cout << "Derived class display()" << endl;
    }
};

int main() {
    Base base;
    Derived derived;
    Base* ptr = &derived;

    base.display();    // Calls Base's display
    derived.display(); // Calls Derived's display

    ptr->display();    // Late binding, calls Derived's display
    return 0;
}
