#include <iostream>

int main() {
    int n;
    std::cout << "Enter n: ";
    if (!(std::cin >> n)) return 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            // If row and col have the same parity (both odd or both even), print the column digit
            if ((i % 2) == (j % 2)) {
                std::cout << j;
            } else {
                std::cout << '*';
            }
        }
        std::cout << '\n';
    }
    return 0;
}