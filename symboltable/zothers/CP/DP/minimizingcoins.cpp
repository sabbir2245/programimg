#include <iostream>
#include <string>
#include <vector>  
#include <array> 
#include <list>  
#include <map>  
#include <unordered_map>  
#include <algorithm>  
#include <cmath>  

using namespace std;


int main() {

// n = number of cooins , x = target sum

int n , x ; 
cin>> n >> x ; 

vector<int> coins ; 
 for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }

vector<int>sum(x+1 ,0 ) ; 

sum[0]= 1 ; 

for(int c : coins){
    for(int i = c ; i <=x; i++){
        sum[i] = sum[i] + sum[i-c] ; 
    }

}

cout << sum[x] ; 

return 0 ; 
 }