#include<algorithm>
#include<cmath>
#include<string>
#include<iostream>
using namespace std;
int  checker(int n ){  
      string str;

    str = to_string(n) ;

for (int i = 0; i < str.length(); i++) {
      for (int j = i+1; j < str.length(); j++) {  

if (str[i]==str[j]){
 return 1 ; 
}
   

}}
return -1 ;
}

int main(){
  int n;
  cin>>n ;
 

    
for (int i = n+1; i <100000 ; i++)
if (checker(i)==-1)
{
    cout<<i ; 
    break;
}

return 0 ; 
}