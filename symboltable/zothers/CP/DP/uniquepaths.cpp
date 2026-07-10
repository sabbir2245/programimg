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

// to reach the the bottom of a grid 

class Solution
{
public:
    int numofways(int m, int n)
    {
        vector<vector<int>> a(m, vector<int>(n));
        for (int i = 0; i < m; ++i)
        {
            a[i][n - 1] = 1;
        }
        for (int i = 0; i < n; ++i)
        {
            a[m - 1][i] = 1;
        }

        for (int i = m-2; i >-1; i--) {
        for (int j = n-2; j >-1; j--) {
           a[i][j] = a[i][j+1] + a[i+1][j] ; 
        }}

        return a[0][0] ; 
    }
};

int main()
{
    Solution obj;
    int m = 3 ; 
    int n = 7 ; 

    cout<<"thw worls"<<endl;
    cout<<obj.numofways(m,n) ;

    return 0;
}