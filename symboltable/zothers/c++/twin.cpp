
#include<cmath>
#include<iostream>
#include<algorithm>
using namespace std;

bool des (int a , int b ){
    return a > b ;
}

int main() {
 int n,k;
 cin>>n;
 int *a = new int[n]; 
k= n ; 
 for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

sort(a , a+n , des );
int fsum = 0 ;
int lsum = 0 ;

for (int i = 0; i < n; i++) {
    fsum+=a[i];
    lsum+=a[n-i-1];
        if (fsum>lsum)
        {
             k = i +1;
             break;
        }
    }

cout<<k; 
 delete[] a;
}