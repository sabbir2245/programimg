
#include<algorithm>
#include<cmath>
#include<string>
#include<iostream>
using namespace std;


int main() {
  string s,tar = "hello" ;
  cin >> s;
int y , u=0 , j= 0  ;
   y = s.length();


for (int i = 0 ; i < y ; i ++){
    if (s[i]==tar[j]){
          j++ ; 
        u ++ ; 
    }
}

if (u== tar.length())
{
    /* code */cout <<"YES";

}
else
{
    cout<< "NO";
}


return 0 ; 
}

