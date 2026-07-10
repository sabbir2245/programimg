#include <iostream>
#include <vector>
using namespace std;

int sequenceAlignment(string s1, string s2, int gapPenalty, int mismatchPenalty) {
    int m = s1.length();
    int n = s2.length();

    // DP table to store alignment costs
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    // Base case: If one string is empty, cost is the number of gaps
    for (int i = 0; i <= m; i++) dp[i][0] = i * gapPenalty;
    for (int j = 0; j <= n; j++) dp[0][j] = j * gapPenalty;

    // Fill the DP table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1]; // No penalty if characters match
            } else {
                int matchMismatch = dp[i - 1][j - 1] + mismatchPenalty;
                int insertGap = dp[i][j - 1] + gapPenalty;
                int deleteGap = dp[i - 1][j] + gapPenalty;
                dp[i][j] = min(matchMismatch,min( insertGap, deleteGap));
            }
        }
    }

    return dp[m][n]; // Minimum alignment cost
}

int main() {
    string s1 = "AGTACG";
    string s2 = "GTTAG";
    int gapPenalty = 2;
    int mismatchPenalty = 3;

    cout << "Minimum Alignment Cost: " << sequenceAlignment(s1, s2, gapPenalty, mismatchPenalty) << endl;
    return 0;
}
