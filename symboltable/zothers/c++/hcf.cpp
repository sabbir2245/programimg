
#include<algorithm>
#include<cmath>
#include<string>
#include<iostream>
using namespace std;

int main() {
    int rows = 5 ;
    int cols = rows ;
int y , z ;
int n;
int ans ; 
    for (int  i = 1; i <=5; i++)
    { for (int j = 1; j <= 5; j++)
    { 
        cin>>n ;
      

        if (n==  1)
        {
              ans = abs(3-i )+abs(3-j ) ;

        }   
    }
    }
   cout << ans ;
return 0 ;
}