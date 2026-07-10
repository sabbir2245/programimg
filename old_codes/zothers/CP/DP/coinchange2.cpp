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

// using 1d array 

int change(int amount, std::vector<int>& coins) {
    // dp[i] will store the number of ways to make the amount i
    std::vector<int> dp(amount + 1, 0);
    dp[0] = 1; // Base case: There's one way to make amount 0 (by using no coins)

    // Iterate over each coin
    for (int coin : coins) {
        // Update the dp array for each amount that can be made with this coin
        for (int i = coin; i <= amount; ++i) {
            dp[i] = dp[i] + dp[i - coin];
        }
    }
    
    return dp[amount];
}

// using 2d array

int change22(int amount, std::vector<int>& coins) {
    int n = coins.size();
    
    // Create a dp table of size (n+1) x (amount+1)
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(amount + 1, 0));
    
    // Base case: There is exactly one way to make the amount 0 (by not using any coins)
    for (int i = 0; i <= n; ++i) {
        dp[i][0] = 1;
    }

    // Fill the dp table
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= amount; ++j) {
            // Exclude the current coin: dp[i-1][j]
            dp[i][j] = dp[i-1][j];

            // Include the current coin if it's less than or equal to the current amount
            if (j >= coins[i-1]) {
                dp[i][j] += dp[i][j - coins[i-1]];
            }
        }
    }

    // The result is the number of ways to make the amount using all coins
    return dp[n][amount];
}




int main() {
    int amount = 15;
    std::vector<int> coins = {1, 2, 5};
    
    std::cout << "Number of ways to make amount " << amount << ": " << change(amount, coins) << std::endl;

    return 0;
}

