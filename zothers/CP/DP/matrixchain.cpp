#include <iostream>
#include <climits>
using namespace std;

// Recursive function to find the minimum multiplication cost
int matrixChainOrder(int p[], int i, int j)
{
    if (i == j)
        return 0;  // No cost if there is only one matrix

    int minCost = INT_MAX;

    // Try every possible split point between i and j
    for (int k = i; k < j; k++)
    {
        int cost = matrixChainOrder(p, i, k) +
                   matrixChainOrder(p, k + 1, j) +
                   p[i - 1] * p[k] * p[j];

        minCost = min(minCost, cost);  // Store minimum cost
    }

    return minCost;
}

// Function to find the minimum multiplication cost using DP
int matrixChainOrderDP(int p[], int n)
{
    // Create a table to store minimum costs
    int dp[n][n];

    // Cost of multiplying one matrix is zero
    for (int i = 1; i < n; i++)
        dp[i][i] = 0;

    // Fill the table in a bottom-up manner
    for (int length = 2; length < n; length++) // Chain length
    {
        for (int i = 1; i < n - length + 1; i++)
        {
            int j = i + length - 1;
            dp[i][j] = INT_MAX;

            // Try every possible split point
            for (int k = i; k < j; k++)
            {
                int cost = dp[i][k] + dp[k + 1][j] + p[i - 1] * p[k] * p[j];
                dp[i][j] = min(dp[i][j], cost);
            }
        }
    }

    return dp[1][n - 1];  // Minimum cost to multiply matrices
}

int main()
{
    int p[] = {1, 2, 3, 4};  // Example matrix dimensions
    int n = sizeof(p) / sizeof(p[0]) - 1;

    int minCost = matrixChainOrder(p, 1, n);
    cout << "Minimum number of multiplications is " << minCost << endl;

    return 0;
}
