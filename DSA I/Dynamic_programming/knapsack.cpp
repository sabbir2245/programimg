#include <iostream>
#include <vector>
#include <cstring> // For memset
using namespace std;

// Recursive approach (Brute Force)
int knapsackRecursive(int W, vector<int>& wt, vector<int>& val, int n) {
    if (n == 0 || W == 0) return 0;
    
    if (wt[n - 1] > W) // Cannot include this item
        return knapsackRecursive(W, wt, val, n - 1);
    
    // Include the item or exclude it
    return max(val[n - 1] + knapsackRecursive(W - wt[n - 1], wt, val, n - 1),
               knapsackRecursive(W, wt, val, n - 1));
}

// Recursion with Memoization (Top-Down DP)
int knapsackMemo(int W, vector<int>& wt, vector<int>& val, int n, vector<vector<int>>& dp) {
    if (n == 0 || W == 0) return 0;

    if (dp[n][W] != -1) return dp[n][W]; // Return precomputed result

    if (wt[n - 1] > W)
        return dp[n][W] = knapsackMemo(W, wt, val, n - 1, dp);

    return dp[n][W] = max(val[n - 1] + knapsackMemo(W - wt[n - 1], wt, val, n - 1, dp),
                          knapsackMemo(W, wt, val, n - 1, dp));
}

// Bottom-Up DP (Iterative Approach)
int knapsackBottomUp(int W, vector<int>& wt, vector<int>& val, int n) {
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (wt[i - 1] <= w)
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }
    return dp[n][W];
}

// Space Optimized DP (1D Array - Bottom-Up)
int knapsackOptimized(int W, vector<int>& wt, vector<int>& val, int n) {
    vector<int> dp(W + 1, 0);

    for (int i = 0; i < n; i++) {
        for (int w = W; w >= wt[i]; w--) {
            dp[w] = max(dp[w], val[i] + dp[w - wt[i]]);
        }
    }
    return dp[W];
}

int main() {
    int W = 50; // Knapsack weight capacity
    vector<int> wt = {10, 20, 30}; // Weights of items
    vector<int> val = {60, 100, 120}; // Values of items
    int n = wt.size();

    // Recursive Approach
    cout << "Recursive Approach: " << knapsackRecursive(W, wt, val, n) << endl;

    // Recursion with Memoization (Top-Down DP)
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, -1));
    cout << "Memoization (Top-Down DP): " << knapsackMemo(W, wt, val, n, dp) << endl;

    // Bottom-Up DP
    cout << "Bottom-Up DP: " << knapsackBottomUp(W, wt, val, n) << endl;

    // Space Optimized DP
    cout << "Space Optimized DP: " << knapsackOptimized(W, wt, val, n) << endl;

    return 0;
}
