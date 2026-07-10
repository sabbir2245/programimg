#include <iostream>
#include <vector>
#include <cstring> // For memset
using namespace std;

// Recursive approach (Brute Force)
int lcsRecursive(string X, string Y, int m, int n) {
    if (m == 0 || n == 0) return 0;

    if (X[m - 1] == Y[n - 1])
        return 1 + lcsRecursive(X, Y, m - 1, n - 1);
    
    return max(lcsRecursive(X, Y, m - 1, n), lcsRecursive(X, Y, m, n - 1));
}

// Recursion with Memoization (Top-Down DP)
int lcsMemo(string X, string Y, int m, int n, vector<vector<int>>& dp) {
    if (m == 0 || n == 0) return 0;

    if (dp[m][n] != -1) return dp[m][n]; // Return precomputed result

    if (X[m - 1] == Y[n - 1])
        return dp[m][n] = 1 + lcsMemo(X, Y, m - 1, n - 1, dp);

    return dp[m][n] = max(lcsMemo(X, Y, m - 1, n, dp), lcsMemo(X, Y, m, n - 1, dp));
}

// Bottom-Up DP (Tabulation)
int lcsBottomUp(string X, string Y, int m, int n) {
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[m][n];
}

// Space Optimized DP (1D Array)
int lcsOptimized(string X, string Y, int m, int n) {
    vector<int> prev(n + 1, 0), curr(n + 1, 0);

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1])
                curr[j] = 1 + prev[j - 1];
            else
                curr[j] = max(prev[j], curr[j - 1]);
        }
        prev = curr;
    }
    return prev[n];
}

int main() {
    string X = "AGGTAB";
    string Y = "GXTXAYB";
    int m = X.length();
    int n = Y.length();

    // Recursive Approach
    cout << "Recursive Approach: " << lcsRecursive(X, Y, m, n) << endl;

    // Recursion with Memoization (Top-Down DP)
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, -1));
    cout << "Memoization (Top-Down DP): " << lcsMemo(X, Y, m, n, dp) << endl;

    // Bottom-Up DP
    cout << "Bottom-Up DP: " << lcsBottomUp(X, Y, m, n) << endl;

    // Space Optimized DP
    cout << "Space Optimized DP: " << lcsOptimized(X, Y, m, n) << endl;

    return 0;
}
