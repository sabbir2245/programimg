#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <cmath>
using namespace std;

class Student
{
    int roll;
    string name;

public:
    // constructor
    Student() {} // default constructor
    Student(int roll, string name) : roll(roll), name(name) {}
    void setroll(int n);
    void printobj();
    void setname(string name)
    {
        this->name = name;
    }
};
void Student::setroll(int n)
{
    roll = n;
}

void Student::printobj()
{
    cout << "Name: " << name << "\nRoll: " << roll << endl;
}

int main()
{
    Student s1;
    s1.setroll(1);
    s1.setname("John Doe");
    s1.printobj();

    Student arr[3] = {Student(1, "rt"), Student(2, "bjk"), Student(3, "poi ")};
    // 2d array of students
    Student arra[3][4] = {Student(1, "rt"), Student(2, "bjk"), Student(3, "poi "),Student(366, "poirfv "),
                         Student(1, "rt"), Student(2, "bjkoiuop"), Student(3, "poi "),Student(37, "poi9887jhk "),
                          Student(1, "rt"), Student(2, "bjk"), Student(3, "poi "),Student(3, "poi "),

    } ;

                      arra[1][3].printobj() ; 
    return 0;
}