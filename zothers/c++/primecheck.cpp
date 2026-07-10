
#include<iostream>
using namespace std;
bool primecheck(int n ){
 if (n <2) {return false;}
 
for (int i = 2; i*i <=n; i++){  
        if (n%i ==0)
        {
            return false;
        }

    }
    

    return true;
}



int main(){
    int y= 46;
    
    if(primecheck(y)){cout<< " yes ";}
    else{cout<< " no ";}
}