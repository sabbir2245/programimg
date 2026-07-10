#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

class student {
public:
    string name;
    int roll;
    int marks;

    void addstudent() {
        cin.ignore();
        getline(cin, name);
        cout << "Enter marks: ";
        cin >> marks;
        cout << "Enter roll: ";
        cin >> roll;
    }

    void print() {
        cout << "Name: " << name << "\nRoll: " << roll << "\nMarks: " << marks << endl;
    }
};

int main() {
    student st1;
    st1.name = "Masrura";
    st1.roll = 961;
    st1.marks = 95;

    st1.print();

    student st2;
    st2.addstudent();

    student st3;
    st3.addstudent();

    st2.print();
    st3.print();

    return 0;
}
