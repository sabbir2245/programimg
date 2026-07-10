#include<iostream>
using namespace std;

int main() {
    int x,y,z;
    cout<<"Input the value of 1st element :" <<endl;
    cin>> x ;
     cout<<"Input the value of 2nd element :" <<endl;
    cin>> y ;
     cout<<"Input the value of 3rd element :" <<endl;
    cin>> z ;

cout<< "the values before swapping "<<endl;
cout<<"element 1 = "<< x << endl;
cout<<"element 2 = "<< y << endl;
cout<<"element 2 = "<< z << endl;

int *ptrx = &x;
int *ptry = &y;
int *ptrz = &z;

int temp = *ptrx;
    *ptrx = *ptrz;
    *ptrz = *ptry;
    *ptry = temp;



cout<< "the values after swapping "<<endl;
cout<<"element 1 = "<< x << endl;
cout<<"element 2 = "<< y << endl;
cout<<"element 3 = "<< z << endl;


return 0 ; 
}
