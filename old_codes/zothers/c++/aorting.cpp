
#include<iostream>
#include <algorithm>
using namespace std;

void bubblesort( int arr[], int n){
    bool swapped ; 
 
    for( int i = 0 ; i < n -1;i++){
        swapped = false ; 
    
        for (int j = 0; j < n-i-1; j++){  
            if(arr[j] > arr[j+1]){ 
            int t = arr[j] ;
            arr[j] = arr[j+1];
            arr[j+1] = t ;
            swapped = true ;  
       
            }
        }    
     if (!swapped) {
            break;
        }
   
    }

}
int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    int barr[n];

    std::copy(arr, arr + n, barr);

    bubblesort(arr,n );


      for(int y :barr){
        cout<<y << " "; 
     }

}