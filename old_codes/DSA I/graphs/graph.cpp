#include <iostream>
#include <vector>

using namespace std;

class Graph
{
private:
    int numofVertices;
    vector<vector<int>> adjlist;

public:
    Graph(int n) : numofVertices(n), adjlist(n) {}

    void addEdge(int u, int v)
    {
        adjlist[u].push_back(v);
        adjlist[v].push_back(u);
    }
    void displaygraph()
    {
        cout << "the graph is " << endl;
        for (int i = 0; i < numofVertices; i++)
        {
            cout << "vertex " << i << " : ";
            for (int j = 0; j < adjlist[i].size(); j++)
            {
                cout << adjlist[i][j] << " ";
            }
            cout << endl;
        }
    }

    void BFs(int s ){
        
    }
    void addvertex(int val)
    {
        vector<int> temp(numofVertices, 0);
        adjlist.push_back(temp);
        numofVertices++;
    }
    void removeEdge(int u, int v)
    {

        for (int j = 0; j < adjlist[u].size(); j++)
        {
            if (adjlist[u][j] == v)
            {
                for (int k = j; k < adjlist[u].size() - 1; k++)
                {
                    adjlist[u][k] = adjlist[u][k + 1];
                }
                adjlist[u].pop_back();
                break;
            }
        }
    }
};

int main()
{
    cout << "cats ";

    Graph gra1(6);
    gra1.addEdge(0, 1);
    gra1.addEdge(0, 2);
    gra1.addEdge(1, 2);
    gra1.addEdge(1, 3);
    gra1.addEdge(2, 3);
    gra1.addEdge(2, 4);
    gra1.addEdge(3, 5);

    gra1.displaygraph();
}