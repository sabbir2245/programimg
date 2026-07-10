#include<string>
#include<iostream>
#include<cctype>
using namespace std;

int main() {
    string str ;
    cin>>str;

for(char& c: str){
    c= tolower(c);
}
//cout<<str;
int i = 0 ;
while(i<str.length())
{

    if(str[i] != 'a' && str[i] != 'e' && str[i] != 'i' && str[i] != 'o' && str[i] != 'u'){
      cout<<"."<<str[i];   
    }
    i++;
    
}


return 0 ; 
}

