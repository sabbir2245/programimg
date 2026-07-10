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

class Solution
{
public:
    int coinChange(vector<int> &coins, int amount)
    {
        vector<int > dp(amount+1,amount +1) ;
        dp[0] =0 ; 
        for(int c : coins) {
            for(int i = c ; i <amount+1 ; i++){
                dp[i] =min( dp[i] , dp[i-c] +1 ) ; 
            }
        } 

        if(dp[amount] > amount){
            return -1 ; 
        }
        else {
            return dp[amount] ; 
        }
    }
};

int main()
{

    Solution obj;

    return 0;
}