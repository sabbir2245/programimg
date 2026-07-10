#include<algorithm>
#include<iostream>
#include <cstdlib>
using namespace std;
//this is the bruteforc emethod
void mintwosuminarray(int a[],int size){
int minl =0 , minr = 1 ;
int minsum = abs(a[minl]+ a[minr]);
for (int i = 0; i < size -1; i++) {
          for (int j = i+1; j < size; j++) {  
            int newsum = abs(a[i] + a[j]);

            if (newsum < minsum){
                minsum = newsum;
                minl = i ;
                minr = j ;
            }
    }
}

cout<< " the nums are "<< a[minl]<< " and "<< a[minr];
}

int main() {
int a[] = {-29,10, 20, 30, 40, 50}; // Example array
    int size = sizeof(a) / sizeof(a[0]);

mintwosuminarray(a , size );

return 0 ; 
}