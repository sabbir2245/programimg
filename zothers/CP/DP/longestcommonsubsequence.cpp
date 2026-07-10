#include <iostream>
#include <string>
using namespace std;

// Recursive function to find LCS length
int LCSLength(string X, string Y, int m, int n)
{
    if (m == 0 || n == 0)
        return 0;  // Base case: LCS length is 0 if either string is empty

    if (X[m - 1] == Y[n - 1])  // If last characters match
        return 1 + LCSLength(X, Y, m - 1, n - 1);

    // If last characters don't match, consider two cases
    return max(LCSLength(X, Y, m, n - 1), LCSLength(X, Y, m - 1, n));
}


string LCSrecursion(string X, string Y, int m, int n)
{
    if (m == 0 || n == 0)
        return "";  // Base case: empty string if one string is empty

    if (X[m - 1] == Y[n - 1]) 
        return LCSrecursion(X, Y, m - 1, n - 1) + X[m - 1];  // Include current character

    // If last characters don't match, find max length LCS
    string lcs1 = LCSrecursion(X, Y, m - 1, n);
    string lcs2 = LCSrecursion(X, Y, m, n - 1);
    
    return (lcs1.length() > lcs2.length()) ? lcs1 : lcs2;
}


// Function to calculate the LCS length and store the table
void LCS(string X, string Y, int m, int n, int L[][100])
{
    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;
            else
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
        }
    }
}



// Function to print the LCS
void printLCS(string X, string Y, int m, int n, int L[][100])
{
    int index = L[m][n];
    string lcs(index, '\0');

    int i = m, j = n;
    while (i > 0 && j > 0)
    {
        if (X[i - 1] == Y[j - 1])
        {
            lcs[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        }
        else if (L[i - 1][j] > L[i][j - 1])
            i--;
        else
            j--;
    }
    cout << "LCS is " << lcs << endl;
}

// Function to print the LCS table
void printTable(string X, string Y, int m, int n, int L[][100])
{
    cout << "  ";
    for (char c : Y)
        cout << c << " ";
    cout << endl;

    for (int i = 0; i <= m; i++)
    {
        if (i > 0)
            cout << X[i - 1] << " ";
        else
            cout << "  ";

        for (int j = 0; j <= n; j++)
            cout << L[i][j] << " ";
        cout << endl;
    }
}

int main()
{
    string X = "AGGTAB";
    string Y = "GXTXAYB";
    int m = X.length(), n = Y.length();

    const int MAX = 100;
    int L[MAX][MAX];

    // Calculate LCS table
    LCS(X, Y, m, n, L);

    // Print LCS length
    cout << "Length of LCS is " << L[m][n] << endl;

    // Print the LCS table
    printTable(X, Y, m, n, L);

    // Print the actual LCS
    printLCS(X, Y, m, n, L);

    return 0;
}
