#include <iostream>
using namespace std;



//to overload operator ---------------------------------

class Complex {
private:
    int real, imag;
public:
    Complex(int r, int i) : real(r), imag(i) {}
    friend Complex operator + (const Complex &c1, const Complex &c2);
    void display() { cout << real << "+" << imag << "i"; }
};

Complex operator + (const Complex &c1, const Complex &c2) {
    return Complex(c1.real + c2.real, c1.imag + c2.imag);
}

// friend class ------------------------------

class A {
private:
    int x;
public:
    A(int val) : x(val) {}
    friend class B;  // B can access A's private members
};

class B {
public:
    void showA(A &a) {
        cout << "A's value: " << a.x << endl;  // Access private member of A
    }
};

/// global frind ----------------------------

class ClassBB;  // Forward declaration of ClassBB

class ClassAA {
private:
    int a;

public:
    ClassAA(int x) : a(x) {}

    // Friend function declaration
    friend int compare(ClassAA, ClassBB);
};

class ClassBB {
private:
    int b;

public:
    ClassBB(int y) : b(y) {}

    // Friend function declaration
    friend int compare(ClassAA, ClassBB);
};

// Friend function definition
int compare(ClassAA aa, ClassBB bb) {
    return aa.a - bb.b;

}





int main() {
    ClassAA objAA(5);  // Object of ClassAA with a = 5
    ClassBB objBB(10);  // Object of ClassBB with b = 10

    int result = compare(objAA, objBB);  // Compare a and b
  std::cout <<result<<std::endl ; 

    return 0;
}