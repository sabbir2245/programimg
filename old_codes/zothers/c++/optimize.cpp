
#include<algorithm>
#include<cmath>
#include<string>
#include<iostream>
using namespace std;

int main() {
  long long n,k ;
  cin>> n >>k;
int y = n/2;

  int a[n];
if (n%2==0 )
{
for (int i = 1; i <= n/2; i++)
{
  a[i-1]=2*i-1;
}
for (int i = 1; i <=n/2; i++)
{a[i +y -1] = 2*i; }

cout<<a[k-1];
}

else
{
  for (int i = 1; i <= 1+ n/2; i++)
{
  a[i-1]=2*i-1;
}
for (int i = 1; i <=n/2; i++)
{a[i +y ] = 2*i; }

cout<<a[k-1];

}


}