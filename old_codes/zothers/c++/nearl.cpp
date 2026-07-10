
#include<algorithm>
#include<cmath>
#include<string>
#include<iostream>
using namespace std;

int main() {
   long long n ;
    cin>> n ;

     string str  ;

     cin>>str ; 

int cow = 0 ;
int d = 0 ;


 for (int  i = 0; i < str.size(); i++)
 {
    if(str[i] == 'A' ){
        cow++ ; 
    } else
    {
        d++;
    }
    

 }
 
    if (cow >d )
    {
       cout<<"Anton";
    }
    else if (d>cow){
        cout<< "Danik";
    }
    else if (d==cow){
        cout<<"Friendship";
    }

    
return 0 ; 
}
