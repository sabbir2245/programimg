
#include<algorithm>
#include<cmath>
#include<string>
#include<iostream>
using namespace std;


int main() {
    int m,k ,y, n ,a,b; 
    k= 0 ;
    y= 0 ;
    cin>>n ;

for (int i = 0; i < n; i++)
{
    cin>>a>>b;
    m = b-a ;
    k = k + m ;

    if (y<k)
    { 
        y= k ;
    }
    
}



cout<< y ;


return 0 ; 
}