#include<iostream>
#include<string>
#include<algorithm>

using namespace std;

class student{

public :
string name ;
int roll;
int marks;

void addstudent(){
    cin.ignore();
    getline(cin,name);
    cout << "say marks"<<endl;
    cin >> roll ;
}
void print (){
    cout<< name << roll << marks;
}

};
int main() {
student st1;
st1.name = "Masrura";
st1.roll = 961;

st1.print();

student st2 ;
st2.addstudent();

student st3;
st3.addstudent();

st2.print();
st3.print();

return 0 ; 
}