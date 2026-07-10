#include<cmath>
#include<string>
#include<iostream>
using namespace std;

int main() {
    int x , y, z ;
int k = 0 ;
int l = 0 ;
int j = 0 ;

    int n ;
    cin>>n ;
    for (int i = 0 ; i < n ; i ++){
        cin>>x>>y>>z;
        k+=x;
        l+=y;
        j+=z;}

if (k==0 &&l==0 &&j==0 )
{
    cout<<"YES"<<endl;
}
else
{
    cout<<"NO"<<endl;
    /* code */
}



return 0 ; 
}
