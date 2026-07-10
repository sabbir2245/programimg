#include <iostream>
using namespace std;

int main(){

/*   cout<<   1
            121
           12321 << endl; */
    int n = 10 ;
    
    int i=1;
    for ( i = 1; i <= n ; i++){   


    for (int j = 1; j<= n- i ; j++){ 
        cout<< " ";}
   
    for (int l = 1; l<= i ; l++){ 
        cout<< l ;}

    for (int j = i -1; j>= 1 ; j--){ 
        cout<< j ;}

     cout<<endl;

    }
    
       
  return 3;  
}
