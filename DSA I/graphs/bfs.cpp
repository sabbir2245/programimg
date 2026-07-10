#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> bfstraversal(vector<vector<int>> &arr, int rows, int start)
{
    vector<int> result;

    vector<int> visited(rows, 0);

    visited[start] = 1;

    queue<int> temp;
    temp.push(start);

    while (!temp.empty())
    {
        int curr = temp.front();
        temp.pop();
       // cout << curr + 1 << " ";
        result.push_back(curr + 1);

        for (int i = 0; i < rows; i++)
        {
            if ((arr[curr][i] == 1) && (visited[i] == 0))
            {
                visited[i] = 1;
                temp.push(i);
            }
        }
    }

    return result;
}

int main()
{
   // cout << "start" << endl;
    FILE *f = fopen("input.txt", "r");
    int rows, tunnels;
    fscanf(f, "%d %d", &rows, &tunnels);

    vector<vector<int>> matrix(rows, vector<int>(rows, 0));

    for (int i = 0; i < tunnels; i++)
    {
        int x, y;
        fscanf(f, "%d %d", &x, &y);
        matrix[x - 1][y - 1] = 1;
        matrix[y - 1][x - 1] = 1;
    }

    // for (int i = 0; i < rows; i++)
    // {
    //     for (int j = 0; j < rows; j++)
    //     {
    //         cout << matrix[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    fclose(f);
  //  cout << "Bfs traversal of the graph is" << endl;
    vector<int> ans = bfstraversal(matrix, rows, 0);
    vector<int> arr2;
    cout << endl;

    sort(ans.begin(), ans.end());
    // for (int &c : ans)
    // {
    //     cout << c << " ";
    // }
    // cout << endl;

    int current = 1;
    for (int i = 0; i < ans.size(); i++)
    {
        while (ans[i] > current)
        {
            arr2.push_back(current);
            current++;
        }
        current++ ; 
    }
    // cout<<"missing elements" <<endl;
    // for (int &c : arr2)
    // {
    //     cout << c << " ";
    // }
    // cout<<endl;

    cout<<" " <<arr2.size() <<endl; 
    cout<<ans[0] <<" " <<arr2[0] <<endl;
    for (int i = 0; i < arr2.size()/2; i++){
        cout<<arr2[i] <<" "<<arr2[i+1]<<endl;
    }
    
}