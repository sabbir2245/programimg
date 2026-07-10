#include<string>
#include<algorithm>
#include<cmath>
#include<iostream>
using namespace std;

void pairWithLowestSum(int a[],int size ){
    

}

void sort(int a[],int size ){
    for (int i = 0 ; i < size; i ++){
  for (int j = i+1; j < size; j++) {  
    if (a[i ]>a[j]){
        int temp = a[i];
        a[i] = a[j];
        a[j]= temp ; 
     }

}}}
int maxfinder(int a[], int size){
 int y = a[0];
    for (int i = 0 ; i < size; i ++){
        if(a[i]> y){
            y = a[i];
        }}
return y ; 

}
int sumelements (int a[], int size){
int total = 0 ;
    for (int i = 0 ; i < size; i ++){
        total+=a[i];
    }
    return total ;
}

int main() {
    int a[] = {80, 60, 30, 40, 50}; // Example array
    int size = sizeof(a) / sizeof(a[0]);

sort(a,size);
int sum = sumelements(a,size);
int maxnum = maxfinder(a,size);
    
for (int i = 0; i < size; i++) {
        cout << a[i] << " ";
    }

    cout<< " \nsum of all elements in the array: "<< sum <<endl;
    cout<< " \nmax of all elements in the array: "<< maxnum <<endl;

return 0 ; 
}
