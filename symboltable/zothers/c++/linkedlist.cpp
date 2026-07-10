
#include<algorithm>
#include<cmath>
#include<string>
#include<iostream>
#include <bits/stdc++.h>
using namespace std;

bool reverse(int n ){
  string h = to_string(n);
  int size = h.size();
 //string m(size, ' ') ; 
  for (int i =0;i<size;i++)
  { 
    if (h[i]!=h[size-1-i])
    {
         return false;  /* code */
    }
    
  }


return true ; 
}
int main() {
  int n ;
  cin>> n ; 
  
    if (reverse(n))
    {
      cout<< "yes, it is a palindrom"<<endl ;
    }
    else
    {
      cout<<" no ";
    }
    
  }
  

