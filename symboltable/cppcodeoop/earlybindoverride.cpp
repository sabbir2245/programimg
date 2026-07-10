#include <iostream>
using namespace std;



// Definition: Early binding (also known as Static Binding) occurs at 
//compile-time. The function call is resolved
//  by the compiler before the program runs.
// When It Happens: This happens when a function is NOT virtual.
//  In this case, the compiler decides which function to call 
//  based on the type of the reference or pointer at compile-time.
// FASTER , but doesnt support polymorphism


class Base {
public:
    void display() {
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

    ptr->display();    // Early binding, calls Base's display
    return 0;
}


