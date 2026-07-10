#include <iostream>
#include <string>

using namespace std;

class Vector {
private:
    int x, y, z; // Corrected: Declare z as part of the class
    string name;
    char *loc;
    int *arr; // You had arr[] as a pointer, so we declare it correctly as a pointer

public:
    // Constructor
    Vector(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z), arr(nullptr) {}

    // Copy Constructor
    Vector(const Vector &other) {
        x = other.x;
        y = other.y;
        z = other.z;
<<<<<<< HEAD
=======
        // Assuming arr is dynamically allocated, you should handle deep copy for it
        if (other.arr != nullptr) {
            arr = new int[10]; // Example size, change as needed
            for (int i = 0; i < 10; ++i) {
                arr[i] = other.arr[i];
            }
        } else {
            arr = nullptr;
        }
>>>>>>> f58129b (dad)
    }

    // Assignment Operator
    Vector& operator=(const Vector& v) {
        if (this != &v) { // Avoid self-assignment
            x = v.x;
            y = v.y;
            z = v.z;
            // Deep copy of arr (assuming arr is dynamically allocated)
            if (arr != nullptr) {
                delete[] arr;
            }
            if (v.arr != nullptr) {
                arr = new int[10]; // Example size
                for (int i = 0; i < 10; ++i) {
                    arr[i] = v.arr[i];
                }
            } else {
                arr = nullptr;
            }
        }
        return *this;
    }

      bool operator==(const Vector& v) const {
        return (x == v.x && y == v.y && z == v.z && name == v.name);
    }

    // Overload + operator (Vector + Vector)
    Vector operator+(const Vector& v) const {
        return Vector(x + v.x, y + v.y, z + v.z);
    }

//     Vector operator+(const Vector& v) const {
//     Vector temp; // Create a temporary vector
//     temp.x = x + v.x;
//     temp.y = y + v.y;
//     temp.z = z + v.z;
//     return temp;
// }


    // Overload += operator (Vector += Vector)
    Vector& operator+=(const Vector& v) {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    // Overload + operator (Vector + int)
    Vector operator+(int val) {
        return Vector(x + val, y + val, z + val);
    }

    // Overload + operator (int + Vector)
    friend Vector operator+(int val, const Vector& v) {
        return Vector(val + v.x, val + v.y, val + v.z);
    }

    // Pre-increment (++v)
    Vector& operator++() {
        ++x;
        ++y;
        ++z;
        return *this;
    }

    // Post-increment (v++)
    Vector operator++(int) {
        Vector temp = *this; // Store old value
        x++;
        y++;
        z++;
        return temp; // Return old value
    }

    // Display function
    void display() const {
        cout << "(" << x << ", " << y << ", " << z << ")" << endl;
    }

    // Destructor to free allocated memory (if any)
    ~Vector() {
        if (arr != nullptr) {
            delete[] arr;
        }
    }
};

int main() {
    Vector v1(1, 2, 3), v2(4, 5, 6);

    // Vector + Vector
    Vector v3 = v1 + v2;
    v3.display();  // Output: (5, 7, 9)

    // Vector += Vector
    v1 += v2;
    v1.display();  // Output: (5, 7, 9)

    // Vector + int
    Vector v4 = v1 + 10;
    v4.display();  // Output: (15, 17, 19)

    // int + Vector
    Vector v5 = 20 + v2;
    v5.display();  // Output: (24, 25, 26)

    // Pre-increment
    ++v1;
    v1.display();  // Output: (6, 8, 10)

    // Post-increment
    Vector v6 = v1++;
    v6.display();  // Output: (6, 8, 10) [Old value before increment]
    v1.display();  // Output: (7, 9, 11) [New value after increment]

    // Copy constructor test
    Vector v7 = v5;
    v7.display();  // Output: (24, 25, 26)

    // Assignment operator test
    Vector v8;
    v8 = v4;
    v8.display();  // Output: (15, 17, 19)

    return 0;
}
