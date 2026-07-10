#include<string>
#include<iostream>
using namespace std;

int main() {
   string str;
   cin>>str;

   int sc = 0;
   int cc = 0 ;
   for (int i = 0; i < str.length(); i++)
   {
     if (str[i]<='z' && str[i]>='a')
     {
        sc++;
     }
   }
   for (int i = 0; i < str.length(); i++)
   {
     if (str[i]<='Z' && str[i]>='A')
     {
        cc++;
     }
   }

 if(sc==cc){for (char& c : str)
   {
     c= tolower(c);
   }}

  else if (sc<cc)
   { for (char& c : str)
   {
     c= toupper(c);
   }
   }
   else if(sc>cc){for (char& c : str)
   {
     c= tolower(c);
   }

   }
   
    cout<<str;
    
return 0 ; 
}
