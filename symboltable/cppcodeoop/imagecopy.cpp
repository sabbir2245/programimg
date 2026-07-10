#include <iostream>
#include <fstream>
using namespace std;

int main() {
    // Open the source image file in binary mode for reading
    ifstream input("input_image.jpg", ios::binary);
    if (!input) {
        cout << "Error opening input file!" << endl;
        return 1;
    }

    // Open the output file in binary mode for writing
    ofstream output("output_image.jpg", ios::binary);
    if (!output) {
        cout << "Error opening output file!" << endl;
        return 1;
    }

    // Copy data from the input file to the output file
    output << input.rdbuf();  // Efficient way to copy data using rdbuf()

    // Close both input and output files
    input.close();
    output.close();

    cout << "Image copied successfully!" << endl;
    return 0;
}
