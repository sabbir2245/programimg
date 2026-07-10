#include<iostream>
#include<string>
using namespace std;

int main() {
string s ;
cin>>s ; 
int x= 0 ,y =0 ;
for (int i = 0; i < s.size(); i++)
{ 
    if (s[i] == '0')
    {
         x++;if (x>6)
         {
            break;
         }
         
         else{y= 0 ;}
    }
    else if (s[i] == '1'){
        y++;
        if (y>6)
         {
            break;
         }
         
         else{  x=0 ;}
        
    }
    
    
    
}
if (x>6 || y>6)
    {
       cout<< "YES";
    }
    else
    {
              cout<< "NO";

    }
    

}
