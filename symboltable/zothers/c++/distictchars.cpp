#include<iostream>
#include<string>
#include<set>


using namespace std;
int discac(string str){


    set<char> list;

    for( char c : str){
        list.insert(c);
    }

    return list.size();
    
}
int main() {
    string str ;
    cin>>str;

    int y = discac(str);

if (y%2 == 0 )
{
   cout<<"CHAT WITH HER!";
}
else {
   cout<<"IGNORE HIM!";

}

return 0 ; 
}