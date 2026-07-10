#include<iostream>
using namespace std;

void sort (int a[],int size ){
    
    for (int i = 0; i < size; i++) {
     for (int j = i+1; j < size; j++) {

        if (a[i]>a[j]){
            int tr = a[i];
            a[i]= a[j];
            a[j]=tr;
                  }
        
     }}}

void reverser(int a[],int size ){
       for (int i = 0; i < size/2; i++) {
        int temp =  a[i];
         a[i] = a[size-1-i];
        a[size-1-i] =temp ;
       }
}

int main() {
    int a[] = {10,3,46 ,20, 30, 40, 50,60}; // Example array
    int size = sizeof(a) / sizeof(a[0]);

sort(a ,size);
reverser(a,size);

for (int i = 0; i < size; i++) {
        cout << a[i] << " ";
    }


return 0 ; 
}