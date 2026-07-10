#include<iostream>
using namespace std;

void print(void* ptr ,char type ){
    switch (type)
    {
    case 'i':
        
        break;
    
    default:
        break;
    }
}

int main() {
string name = "Nashita Tabassum Athoy";

string *ptr =&name ;

cout<<ptr<< endl;
cout<<*ptr<< endl;
cout<<&name<< endl;  

int roll = 226 ;
int *ptroll = &roll ;
*ptroll = 3 ;
cout<< roll << endl; 

cout<<"array "<<endl;

int nums[5]= {2,3,4,5,6};

cout<<nums<< endl;
cout<<&nums[0]<< endl;
cout<<*nums<< endl;

cout<<*(nums+2)<< endl;

for (int i = 0 ; i < 5 ; i ++){
    cout<<*(nums+i)<< " ";}




return 0 ; 
}