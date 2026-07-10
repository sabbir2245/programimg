#include<string>
#include<algorithm>
#include <climits>
#include<cmath>
#include<iostream>
using namespace std;

void fun(int a[],int size );

int main() {
    int a[] = {10, 20, 30, 40, 50}; // Example array
    int size = sizeof(a) / sizeof(a[0]);

     fun(a, size );

return 0 ; 
}

void fun (int a[], int size){

    sort(a , a+size );

    int minsum = INT_MAX ;
int right= size - 1 ;
int left =0 ;
    int cleft , cright ;

    while (left < right ){
        int sum = a[left ]+ a[right];
        if(abs(sum )< abs(minsum)){
            minsum = abs(sum );
            cleft = left;
            cright = right;

        }
        if(sum < 0 ){
            left++;
        }
        else {
            right--;
        }
    }

cout<< " The elements who have the lowest sum is : "<< a[cleft ]<< " and "<< a[cright]<< " ";

}