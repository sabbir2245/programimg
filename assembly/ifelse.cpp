#include <iostream>

int main() {
    int num1, num2;

    // ---- INPUT TWO 2-DIGIT NUMBERS ----
    std::cout << "Enter first 2-digit number: ";
    std::cin >> num1;

    std::cout << "Enter second 2-digit number: ";
    std::cin >> num2;

    // ---- PRINT THE SUM ----
    int sum = num1 + num2;
    std::cout << "\nThe sum is: " << sum << std::endl;

    // ---- COMPARE THE NUMBERS ----
    int bigger;
    if (num1 == num2) {
        std::cout << "Both numbers are equal." << std::endl;
        bigger = num1; // If equal, either can be chosen
    } 
    else if (num1 > num2) {
        std::cout << "First number is greater." << std::endl;
        bigger = num1;
    } 
    else {
        std::cout << "Second number is greater." << std::endl;
        bigger = num2;
    }

    // ---- CHECK PARITY OF THE BIGGER ONE ----
    // (bigger % 2 == 0) works exactly like the 'test al, 1' in assembly
    if (bigger % 2 == 0) {
        std::cout << "The bigger one is even." << std::endl;
    } else {
        std::cout << "The bigger one is odd." << std::endl;
    }

    return 0;
}