#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <climits>
#include <random>
#include <map>

using namespace std;

struct Edge
{
    int u, v, w;
};

struct Neighbor
{
    int to;
    int weight;
};

struct LocalSearchResult
{
    vector<int> partition;
    int iterations;
};

class Graph
{
    int n, m;
    vector<Edge> edgelist;
    vector<vector<Neighbor>> adj;

public:
    Graph()
    {
        this->n = 0;
        this->m = 0;
    }

    Graph(int n, int m)
    {
        this->n = n;
        this->m = m;
        this->adj.resize(n);
    }

    void addEdge(int u, int v, int w)
    {
        Edge e;
        e.u = u;
        e.v = v;
        e.w = w;
        edgelist.push_back(e);
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    int getN() const { return n; }
    int getM() const { return m; }
    const vector<Edge>& getEdges() const { return edgelist; }
    const vector<Neighbor>& getNeighbors(int u) const { return adj[u]; }
};

Graph processFile(const string& path)
{
    ifstream infile(path);
    if (!infile.is_open())
    {
        cerr << "Error: input file not found: " << path << endl;
        return Graph();
    }

    int n, m;
    if (!(infile >> n >> m)) return Graph();

    Graph graph(n, m);

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        infile >> u >> v >> w;
        u--; // Convert 1-based index to 0-based
        v--;
        graph.addEdge(u, v, w);
    }

    return graph;
}

int computeCutWeight(const Graph& g, const vector<int>& partition)
{
    int weight = 0;
    for (const auto& e : g.getEdges())
    {
        if (partition[e.u] != partition[e.v])
            weight += e.w;
    }
    return weight;
}

// ---------- Randomized Heuristic ----------
double randomizedMaxCut(const Graph& g, mt19937& rng)
{
    int n = g.getN();
    long long totalCutWeight = 0;

    uniform_int_distribution<int> dist(0, 1);
    const auto& edges = g.getEdges();

    vector<int> partition(n);
    for (int t = 0; t < n; t++)
    {
        for (int i = 0; i < n; i++)
            partition[i] = dist(rng); // set either rand 0 or 1 

        int cutWeight = 0;
        for (const auto& e : edges)
            if (partition[e.u] != partition[e.v])
                cutWeight += e.w;

        totalCutWeight += cutWeight;
    }

    return (double)totalCutWeight / n;
}

// ----------Greedy Heuristic ----------
vector<int> greedyMaxCut(const Graph& g)
{
    int n = g.getN();
    vector<int> partition(n, -1);

    int maxW = INT_MIN, maxU = 0, maxV = 0;
    for (const auto& e : g.getEdges())
    {
        if (e.w > maxW)
        {
            maxW = e.w;
            maxU = e.u;
            maxV = e.v;
        }
    }

    if (maxW == INT_MIN)
    {
        fill(partition.begin(), partition.end(), 0);
        return partition;
    }

    partition[maxU] = 0; // Set X
    partition[maxV] = 1; // Set Y

    vector<int> sigX(n, 0), sigY(n, 0);

    for (const auto& nbr : g.getNeighbors(maxU))
        sigX[nbr.to] += nbr.weight;

    for (const auto& nbr : g.getNeighbors(maxV))
        sigY[nbr.to] += nbr.weight;

    for (int z = 0; z < n; z++)
    {
        if (z == maxU || z == maxV) continue;

        int valIfX = sigY[z]; // edge weight to Y
        int valIfY = sigX[z]; // edge weight to X

        int chosenPartition = (valIfY > valIfX) ? 1 : 0;
        partition[z] = chosenPartition;

        const auto& nbrs = g.getNeighbors(z);
        if (chosenPartition == 0)
        {
            for (const auto& nbr : nbrs)
                sigX[nbr.to] += nbr.weight;
        }
        else
        {
            for (const auto& nbr : nbrs)
                sigY[nbr.to] += nbr.weight;
        }
    }

    return partition;
}

// ---------- Algorithm 4: Semi-Greedy Heuristic ----------
vector<int> semiGreedyMaxCut(const Graph& g, double alpha, mt19937& rng, bool biased = false)
{
    int n = g.getN();
    vector<int> partition(n, -1);

    int maxW = INT_MIN, maxU = 0, maxV = 0;
    for (const auto& e : g.getEdges())
    {
        if (e.w > maxW)
        {
            maxW = e.w;
            maxU = e.u;
            maxV = e.v;
        }
    }

    if (maxW == INT_MIN)
    {
        fill(partition.begin(), partition.end(), 0);
        return partition;
    }

    partition[maxU] = 0;
    partition[maxV] = 1;

    vector<int> sigX(n, 0), sigY(n, 0);
    vector<int> unassigned;
    unassigned.reserve(n);

    for (const auto& nbr : g.getNeighbors(maxU))
        sigX[nbr.to] += nbr.weight;

    for (const auto& nbr : g.getNeighbors(maxV))
        sigY[nbr.to] += nbr.weight;

    for (int v = 0; v < n; v++)
        if (partition[v] == -1)
            unassigned.push_back(v);

    vector<int> rcl;
    while (!unassigned.empty())
    {
        vector<int> gvals(unassigned.size());
        int wmin = INT_MAX, wmax = INT_MIN;
        for (size_t i = 0; i < unassigned.size(); i++)
        {
            int v = unassigned[i];
            gvals[i] = max(sigX[v], sigY[v]);
            wmin = min(wmin, gvals[i]);
            wmax = max(wmax, gvals[i]);
        }

        double cutoff = wmin + alpha * (wmax - wmin);

        rcl.clear();
        for (size_t i = 0; i < unassigned.size(); i++)
            if (gvals[i] >= cutoff)
                rcl.push_back(unassigned[i]);

        if (rcl.empty()) rcl = unassigned;


        // this part is new code ---------------

        int chosen;
        if (biased)
        {
            vector<int> gvalsRCL(rcl.size());
            int gsum = 0;
            for (size_t i = 0; i < rcl.size(); i++)
            {
                int v = rcl[i];
                gvalsRCL[i] = max(sigX[v], sigY[v]);
                gsum += gvalsRCL[i];
            }
            if (gsum == 0)
            {
                uniform_int_distribution<int> dist(0, rcl.size() - 1);
                chosen = rcl[dist(rng)];
            }
            else
            {
                uniform_int_distribution<int> dist(0, gsum - 1);
                int r = dist(rng);
                int cumulative = 0;
                chosen = rcl[0];
                for (size_t i = 0; i < rcl.size(); i++)
                {
                    cumulative += gvalsRCL[i];
                    if (r < cumulative)
                    {
                        chosen = rcl[i];
                        break;
                    }
                }
            }
        }
        else
        {
            uniform_int_distribution<int> dist(0, rcl.size() - 1);
            chosen = rcl[dist(rng)];
        }


        // this is same as before form this point . . .

        int chosenPartition = (sigX[chosen] >= sigY[chosen]) ? 1 : 0;
        partition[chosen] = chosenPartition;

        for (size_t i = 0; i < unassigned.size(); i++)
        {
            if (unassigned[i] == chosen)
            {
                unassigned[i] = unassigned.back();
                unassigned.pop_back();
                break;
            }
        }

        const auto& nbrs = g.getNeighbors(chosen);
        if (chosenPartition == 0)
        {
            for (const auto& nbr : nbrs)
                sigX[nbr.to] += nbr.weight;
        }
        else
        {
            for (const auto& nbr : nbrs)
                sigY[nbr.to] += nbr.weight;
        }
    }

    return partition;
}

// ---------- Optimized Local Search (Returns Partition & Iteration Count) ----------
LocalSearchResult localSearch(const Graph& g, vector<int> partition)
{
    int n = g.getN();
    vector<int> sigX(n, 0), sigY(n, 0);

    for (int u = 0; u < n; u++)
    {
        for (const auto& nbr : g.getNeighbors(u))
        {
            if (partition[nbr.to] == 0)
                sigX[u] += nbr.weight;
            else if (partition[nbr.to] == 1)
                sigY[u] += nbr.weight;
        }
    }

    int iterations = 0;

    while (true)
    {
        int bestDelta = 0;
        int bestV = -1;

        for (int v = 0; v < n; v++)
        {
            int delta = (partition[v] == 0) ? (sigX[v] - sigY[v]) : (sigY[v] - sigX[v]);

            if (delta > bestDelta)
            {
                bestDelta = delta;
                bestV = v;
            }
        }

        if (bestDelta > 0)
        {
            iterations++;
            int oldP = partition[bestV];
            int newP = 1 - oldP;
            partition[bestV] = newP;

            for (const auto& nbr : g.getNeighbors(bestV))
            {
                int u = nbr.to;
                int w = nbr.weight;
                if (oldP == 0) // bestV moved from X (0) to Y (1)
                {
                    sigX[u] -= w;
                    sigY[u] += w;
                }
                else // bestV moved from Y (1) to X (0)
                {
                    sigY[u] -= w;
                    sigX[u] += w;
                }
            }
        }
        else
        {
            break;
        }
    }

    return {partition, iterations};
}

// ---------- GRASP ----------
vector<int> grasp(const Graph& g, int maxIterations, double alpha, mt19937& rng, bool biased = false)
{
    vector<int> bestPartition;
    int bestWeight = -1;

    for (int i = 0; i < maxIterations; i++)
    {
        vector<int> sol = semiGreedyMaxCut(g, alpha, rng, biased);
        LocalSearchResult lsRes = localSearch(g, sol);
        int w = computeCutWeight(g, lsRes.partition);

        if (i == 0 || w > bestWeight)
        {
            bestWeight = w;
            bestPartition = lsRes.partition;
        }
    }

    return bestPartition;
}

int main()
{
    map<int, string> knownBestMap = {
        {1, "12078"}, {11, "627"}, {22, "14123"}, {32, "1560"}
    };

    string basePath = "set1/";
    int graspIterations = 300;
    int testFiles[] = {1, 11, 22, 32};

    cout << "Comparison: Uniform vs Biased (proportional) GRASP" << endl;
    cout << "File\t|V|\t|E|\tKnownBest\t"
         << "Uniform_a0.3\tBiased_a0.3\t"
         << "Uniform_a0.7\tBiased_a0.7" << endl;

    ofstream csv("csolve.csv");
    csv << "File,|V|,|E|,KnownBest,Uniform_a0.3,Biased_a0.3,Uniform_a0.7,Biased_a0.7" << endl;

    for (int idx = 0; idx < 4; idx++)
    {
        int gNum = testFiles[idx];
        string filename = basePath + "g" + to_string(gNum) + ".rud";
        Graph g = processFile(filename);
        if (g.getN() == 0) continue;

        int n = g.getN(), m = g.getM();
        string kbStr = knownBestMap.count(gNum) ? knownBestMap[gNum] : "";

        mt19937 rng1(42), rng2(42), rng3(42), rng4(42);

        int gUniform03 = computeCutWeight(g, grasp(g, graspIterations, 0.3, rng1, false));
        int gBiased03  = computeCutWeight(g, grasp(g, graspIterations, 0.3, rng2, true));
        int gUniform07 = computeCutWeight(g, grasp(g, graspIterations, 0.7, rng3, false));
        int gBiased07  = computeCutWeight(g, grasp(g, graspIterations, 0.7, rng4, true));

        cout << "G" << gNum << "\t" << n << "\t" << m << "\t" << kbStr << "\t"
             << gUniform03 << "\t\t" << gBiased03 << "\t\t"
             << gUniform07 << "\t\t" << gBiased07 << endl;

        csv << "G" << gNum << "," << n << "," << m << "," << kbStr << ","
            << gUniform03 << "," << gBiased03 << ","
            << gUniform07 << "," << gBiased07 << endl;
    }

    csv.close();
    cout << "Results written to csolve.csv" << endl;

    return 0;
}
