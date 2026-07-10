#include <iostream>
#include <cstring>
using namespace std;

class myLIST {
private:
    char* name;
    string address;
    int* arr;
    int size;

public:
    // Constructor
    myLIST(const char* n, const string& addr, int s) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
        address = addr;
        size = s ;
        arr = new int[size]();  // Initialize array with zeros
    }

    // Destructor
    ~myLIST() {
        delete[] name;
        delete[] arr;
    }

    // Copy Constructor (Deep copy)
    myLIST(const myLIST& other) {
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
        address = other.address;
        size = other.size;
        arr = new int[size];
        for (int i = 0; i < size; ++i) {
            arr[i] = other.arr[i];
        }
    }

    // Resize method to change the size of the list
    void resize(int newSize) {
        int* newArr = new int[newSize];
        for (int i = 0; i < (newSize < size ? newSize : size); ++i) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
        size = newSize;
    }

    // Overloaded = operator to copy one myLIST to another
    myLIST& operator=(const myLIST& other) {
        if (this != &other) {
            delete[] name;
            delete[] arr;

            name = new char[strlen(other.name) + 1];
            strcpy(name, other.name);
            address = other.address;
            size = other.size;
            arr = new int[size];
            for (int i = 0; i < size; ++i) {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }

    // Overloaded [] operator to access elements in the list
    int& operator[](int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("Index out of bounds");
        }
        return arr[index];
    }

    // Method to display the content of the list
    void display() const {
        cout << "Name: " << name << "\n";
        cout << "Address: " << address << "\n";
        cout << "Array: ";
        for (int i = 0; i < size; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    // Creating an object of myLIST
    myLIST list1("John Doe", "123 Elm St", 5);
    
    // Initializing the array values
    for (int i = 0; i < 5; ++i) {
        list1[i] = i * 10;
    }
    
    // Display list1 content
    list1.display();

    // Create a copy of list1 using the copy constructor
    myLIST list2 = list1;
    list2.display();

    // Resize list2 to a larger size
    list2.resize(8);
    list2.display();

    // Use the overloaded assignment operator
    myLIST list3("Jane Doe", "456 Oak St", 3);
    list3 = list1;
    list3.display();

    return 0;
}
