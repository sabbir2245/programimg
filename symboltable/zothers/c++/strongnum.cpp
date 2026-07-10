#include<string>
#include<iostream>
using namespace std;

int factorial(int n ){
    int y = 1 ;
    for (int i = 1 ; i < n+1 ; i ++){
        y= y*i ;
}
return y ;
}

bool checker(int n ){ 
    int org = n ;
    int sum = 0 ;

    while(n>0 ){
        int digit = n%10 ;
        sum+=  factorial(digit);

        n/=10;
    }

    if(sum == org){
        return true;
    }
    else{return false ;}
}


int main() {
    int u =1000;
    for (int pi = 1; pi < u; pi++)
    {
        if (checker(pi)){
            cout<<pi<< " ";
    }
    
    }
 
}
