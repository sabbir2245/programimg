#include <iostream>
using namespace std;

// Function overloads
void space(int a) {
    cout << "Called space(int): " << a << endl;
}

void space(int a, char c) {
    cout << "Called space(int, char): " << a << ", " << c << endl;
}

int main() {
    // Function pointers
    void (*fp1)(int);
    void (*fp2)(int, char);

    // Assigning function addresses to the pointers
    fp1 = space;      // fp1 points to space(int)
    fp2 = space;      // fp2 points to space(int, char)

    // Calling functions using function pointers
    fp1(10);          // Calls space(int)
    fp2(20, 'X');     // Calls space(int, char)

  //  space(10) ; 
   // space(10,'k') ; 

    return 0;
}
