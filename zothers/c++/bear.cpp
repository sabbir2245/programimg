#include<string>
#include<iostream>
#include<cctype>
#include<cmath>
using namespace std;

int main() {
   int a,b;
   cin>>a>>b;
   int c = 0 ;
 for (int i = 0; i < 100; i++)
 {
    if (a*pow(3,i)<=b*pow(2,i))
    {
        c++;
    }
    else{ 
    break;}
 }
 
   cout<<c;


return 0 ; 
}