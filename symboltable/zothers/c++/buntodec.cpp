
#include<cmath>
#include<iostream>
using namespace std;

int main() {
int d = 13 ;
int bin = 0 ;

int i = 1 ;

while (d != 0 ){
    int rem = d%2 ;
    bin+= rem*i ;
    
    i *= 10 ;
    d /= 2 ;

}

cout<<bin ; 

return 0 ; 
}