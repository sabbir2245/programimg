
#include<string>
#include<iostream>
using namespace std;

bool checker(int n ){
    if(n<2 ){
        return false;
    }
    for (int i = 2; i*i <=n; i++)
    { if(n%i == 0 ){
        return false ;
    }
        /* code */
    }
    return true ;
}

void prime(int st , int end ){
   for(int p = st ; p<= end ; p++){
    if (checker(p )){
        cout<< p << " ";
    }
         }
   
}
int main() {

prime(0 , 57);


return 0 ; 
}