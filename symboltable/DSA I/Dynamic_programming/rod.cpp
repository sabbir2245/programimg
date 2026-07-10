#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring> // For memset

using namespace std;

// Recursive approach (Brute Force)
int rodCutRecursive(vector<int>& price, int n) {
    if (n == 0) return 0;
    
    int maxProfit = 0;
    for (int i = 1; i <= n; i++) {
        maxProfit = max(maxProfit, price[i - 1] + rodCutRecursive(price, n - i));
    }
    return maxProfit;
}

// Recursion with Memoization (Top-Down DP)
int rodCutMemo(vector<int>& price, int n, vector<int>& dp) {
    if (n == 0) return 0;
    
    if (dp[n] != -1) return dp[n];

    int maxProfit = 0;
    for (int i = 1; i <= n; i++) {
        maxProfit = max(maxProfit, price[i - 1] + rodCutMemo(price, n - i, dp));
    }
    
    return dp[n] = maxProfit;
}

// Bottom-Up DP (Tabulation)
int rodCutBottomUp(vector<int>& price, int n) {
    vector<int> dp(n + 1, 0);
    
    for (int len = 1; len <= n; len++) {
        int maxProfit = 0;
        for (int i = 1; i <= len; i++) {
            maxProfit = max(maxProfit, price[i - 1] + dp[len - i]);
        }
        dp[len] = maxProfit;
    }
    
    return dp[n];
}

// Space Optimized DP (1D Array)
int rodCutOptimized(vector<int>& price, int n) {
    vector<int> dp(n + 1, 0);
    
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            dp[j] = max(dp[j], price[i - 1] + dp[j - i]);
        }
    }
    
    return dp[n];
}

int main() {
    vector<int> price = {1, 5, 8, 9, 10, 17, 17, 20}; // Example price list
    int n = price.size();

    // Recursive Approach
    cout << "Recursive Approach: " << rodCutRecursive(price, n) << endl;

    // Recursion with Memoization (Top-Down DP)
    vector<int> dp(n + 1, -1);
    cout << "Memoization (Top-Down DP): " << rodCutMemo(price, n, dp) << endl;

    // Bottom-Up DP
    cout << "Bottom-Up DP: " << rodCutBottomUp(price, n) << endl;

    // Space Optimized DP
    cout << "Space Optimized DP: " << rodCutOptimized(price, n) << endl;

    return 0;
}
