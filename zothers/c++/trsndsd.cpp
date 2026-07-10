
#include<algorithm>
#include<cmath>
#include<string>
#include<iostream>
using namespace std;

int main() {
    string s ; 
    cin >> s ;

    int one,two,tr;
    one=0 ;
    two = 0 ;
    tr= 0 ;

    for (int i = 0; i < s.size(); i++)
    {
        if (s[i]== '1')
        {
           one ++;
        }
         if (s[i]== '2')
        {
           two ++;
        } if (s[i]== '3')
        {
           tr ++;
        }
    }
        string output = "";

    for (int  i = 0; i < one; i++)
    {
        output+="1+";
    }
     for (int  i = 0; i <two; i++)
    {
         output+="2+";
    } for (int  i = 0; i < tr; i++)
    {
         output+="3+";
    }
    if (output.back() == '+') {
       
        output.pop_back();
    }
cout<<output;
return 0 ; 
}
