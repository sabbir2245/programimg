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

int n ; 
cin>> n ; 

vector<long long>dp(n+1, 0) ; 

dp[0]=0 ;
dp[1]=1 ;

for(int i = 2 ; i <n+1 ; i++){
    dp[i] = dp[i-1]+ dp [i-2] ; 
}

cout<<dp[n] ; 
 


return 0 ; 
 }