#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stack>

using namespace std;


void dfs(int start, const vector<vector<int>> &adjList, vector<int> &visited, vector<int> &result)
{
    stack<int> s;
    s.push(start);
    visited[start] = 1;

    while (!s.empty())
    {
        int node = s.top();
        s.pop();
        result.push_back(node + 1);  

   
        for (int neighbor : adjList[node])
        {
            if (visited[neighbor] == 0)
            {
                visited[neighbor] = 1;
                s.push(neighbor);
            }
        }
    }
}

vector<int> dfstraversal(const vector<vector<int>> &adjList, int rows, int start)
{
    vector<int> result;
    vector<int> visited(rows, 0);
    dfs(start, adjList, visited, result);
    return result;
}

int main()
{
    FILE *f = fopen("input.txt", "r");
    int rows, tunnels;
    fscanf(f, "%d %d", &rows, &tunnels);
    vector<vector<int>> adjList(rows);
    for (int i = 0; i < tunnels; i++)
    {
        int x, y;
        fscanf(f, "%d %d", &x, &y);
        adjList[x - 1].push_back(y - 1);
        adjList[y - 1].push_back(x - 1);
    }
    fclose(f);

    
    vector<int> dfsResult = dfstraversal(adjList, rows, 0);

    vector<int> arr2;
    sort(dfsResult.begin(), dfsResult.end());

    int current = 1;
    for (int node : dfsResult)
    {
        while (current < node)
        {
            arr2.push_back(current);
            current++;
        }
        current++;
    }


    cout << arr2.size() << endl;
    if (!arr2.empty())
    {
        cout << dfsResult[0] << " " << arr2[0] << endl;
        for (int i = 0; i < arr2.size() / 2; i++)
        {
            cout << arr2[i] << " " << arr2[i + 1] << endl;
        }
    }

    return 0;
}
