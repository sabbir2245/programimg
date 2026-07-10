
#include<algorithm>
#include<cmath>
#include<string>
#include<iostream>
using namespace std;

int main() {
    int n ,k, h,w ;
    w=0;
   cin>>n>>k ;
    int ar[n];
   for (int i = 0; i < n; i++)
   { 
    cin>>h;
    ar[i] =h; 

    /* code */
   }
 
   for (int i = 0; i < n; i++){
    if (ar[i]>=ar[k-1] && ar[i]>0)
    {
        w++;
    }
    
   }


  cout<<w ; 
return 0 ; 
}
