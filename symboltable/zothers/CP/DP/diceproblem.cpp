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
const int MOD = 1e9 + 7;
int main()
{

    int n;
    cin >> n;

    int dice[] = {1, 2, 3, 4, 5, 6};

    vector<int> dp(n + 1, 0);
    dp[0] = 1;

    for (int i = 1; i < n + 1; i++)
    {
        for ( int d : dice)
        {
            if (i - d >= 0)
            {
                dp[i] = (dp[i] + dp[i - d] ) % MOD;
            }
        }
    }

    std::cout << dp[n] << endl;

    return 0;
}