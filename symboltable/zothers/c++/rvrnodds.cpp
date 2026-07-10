#include <bits/stdc++.h>
//recursion

using namespace std;

int main() {

  int n ;
  cin>>n ;

  int one= 0 , two = 0 , thr= 0 , four = 0 ;

  while ( n--)
  
  {
   int k ;
   cin>>k ; 
   if (k==1)
   {
    /* code */one++;
   }
   else if(k==2 ){ 
    two++;
   }
    else if(k==3 ){ 
    thr++;
   }
    else if(k==4 ){ 
    four++;
   } 
  }
  
cout<<one<<two<<thr<<four;}
