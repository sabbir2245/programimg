
#include<algorithm>
#include<cmath>
#include<string>
#include<iostream>
using namespace std;

int main() {
    int rows = 5 ;
    int cols = rows ;

   int matrix[rows][cols];
    
 for (int i = 1; i < rows+1; i++) {
        for (int j = 1; j < cols+1; j++) {
            cin >> matrix[i][j];
        }
    }
    int m , n ;
    
     for (int i = 1; i < rows+1; i++) {
        for (int j = 1; j < cols+1; j++) {
            if (matrix[i][j] == 1) {
                 m = i ;
                 n = j ;
            }}}
//cout<<m<<n <<endl;
   int ans = abs(3-m )+abs(3-n ) ;
   cout << ans ;
return 0 ; 
}
