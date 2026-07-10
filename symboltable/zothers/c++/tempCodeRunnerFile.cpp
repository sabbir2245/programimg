
#include<algorithm>
#include<cmath>
#include<string>
#include<iostream>
using namespace std;

int main() {
  long long n ;
  cin>> n ; 
double sum= 0.00;
  
  for (int i = 0; i < n; i++)
  { int k ; cin>>k ;
     sum+=k;
    /* code */
  }
  
cout<<sum/n;
return 0 ; 
}
