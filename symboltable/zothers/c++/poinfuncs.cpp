#include<iostream>
#include<climits>
using namespace std;

void minmax (int a[],int size,int *max, int *min ){
    *min = a[0];
     *max = a[0];
    for (int i = 0; i < size; i++) {
        if (a[i]<*min )
        { 
            *min = a[i];
        }
        if(a[i]>*max ){
            *max = a[i];
        }
}
}
int main() {

int a[] = {10, 20, 30, -4, 50};
int size = 5;

int maxnum , minnum ;

minmax(a , 5,& maxnum , &minnum );

cout << maxnum << "  "<< minnum ;
return 0 ; 
}
