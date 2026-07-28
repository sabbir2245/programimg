# Max-Cut Practice Problems

Similar in spirit to the C2 test: small modifications to the existing code that change a specific
component of the heuristic.

---

## Problem 1: Rank-Based RCL

Instead of building the RCL by a value-based cutoff (`g(v) >= wmin + α·(wmax − wmin)`), build it
by rank.  Sort all unassigned vertices by `g(v) = max(σX(v), σY(v))` descending and keep the top
`⌈α · |unassigned|⌉` vertices in the RCL.  Everything else stays the same.

**Key part of solution:**

```cpp
// Sort unassigned by g-value descending
vector<pair<int,int>> ranked;
for (int v : unassigned)
    ranked.push_back({v, max(sigX[v], sigY[v])});
sort(ranked.begin(), ranked.end(),
     [](const auto& a, const auto& b) { return a.second > b.second; });

int rclSize = max(1, (int)(alpha * unassigned.size()));
rcl.clear();
for (int i = 0; i < rclSize && i < (int)ranked.size(); i++)
    rcl.push_back(ranked[i].first);
```

---

## Problem 2: Probabilistic Placement (Soft Greedy)

Currently the vertex is placed on whichever side gives a larger g-value (hard greedy).
Change it so that the side is chosen probabilistically:

- Let `gain0 = σY(v)` (cut weight if placed in X — edges crossing to Y)
- Let `gain1 = σX(v)` (cut weight if placed in Y — edges crossing to X)
- Place in X with probability `gain0 / (gain0 + gain1)` (avoid division by zero).
- Only fall back to the hard-greedy choice if both gains are zero.

**Key part of solution:**

```cpp
int gain0 = sigY[v];  // value if placed in partition 0
int gain1 = sigX[v];  // value if placed in partition 1

int chosenPartition;
if (gain0 == 0 && gain1 == 0)
    chosenPartition = 0;
else
{
    uniform_int_distribution<int> dist(0, gain0 + gain1 - 1);
    chosenPartition = (dist(rng) < gain1) ? 1 : 0;
}
```

---

## Problem 3: Edge-Based Seeding (Randomised Seeding)

Instead of always picking the maximum-weight edge to seed the two partitions, pick an edge
randomly with probability proportional to its weight.

- Compute total weight of all edges.
- Pick a random edge `e` with probability `w(e) / totalWeight`.
- Place `e.u` in X (0) and `e.v` in Y (1).

**Key part of solution:**

```cpp
long long totalW = 0;
for (const auto& e : g.getEdges()) totalW += e.w;

uniform_int_distribution<long long> dist(0, totalW - 1);
long long r = dist(rng);
Edge seed = g.getEdges()[0];
long long cum = 0;
for (const auto& e : g.getEdges())
{
    cum += e.w;
    if (r < cum) { seed = e; break; }
}

partition[seed.u] = 0;
partition[seed.v] = 1;
```

---

## Problem 4: First-Improvement Local Search

Currently local search uses **best-improvement** (steepest ascent): it scans all vertices and flips
the one with the largest positive delta.  Change it to **first-improvement**: scan in order and flip
the first vertex that gives any positive delta.  Repeat until no improvement is found.

**Key part of solution:**

```cpp
while (true)
{
    bool improved = false;
    for (int v = 0; v < n; v++)
    {
        int delta = (partition[v] == 0) ? (sigX[v] - sigY[v]) : (sigY[v] - sigX[v]);
        if (delta > 0)
        {
            int oldP = partition[v];
            partition[v] = 1 - oldP;
            for (const auto& nbr : g.getNeighbors(v))
            {
                if (oldP == 0) { sigX[nbr.to] -= nbr.weight; sigY[nbr.to] += nbr.weight; }
                else           { sigY[nbr.to] -= nbr.weight; sigX[nbr.to] += nbr.weight; }
            }
            improved = true;
            break;  // restart scan
        }
    }
    if (!improved) break;
}
```

---

## Problem 5: Reactive GRASP (α Adaptation)

Instead of using a fixed α, maintain a set of possible α values
(e.g. `{0.1, 0.3, 0.5, 0.7, 0.9}`).  Track the average solution quality for each α value and
probabilistically select α based on past performance (better α values are chosen more often).

- Maintain a score `avgVal[k]` for each α candidate.
- Every `R` iterations, update selection probabilities proportional to `avgVal[k]`.
- Use a moving window of the last `W` solutions per α.

**Key part of solution:**

```cpp
vector<double> alphas = {0.1, 0.3, 0.5, 0.7, 0.9};
vector<double> avgVal(alphas.size(), 0.0);
vector<int> counts(alphas.size(), 0);

for (int i = 0; i < maxIterations; i++)
{
    double sumVals = 0;
    for (double a : avgVal) sumVals += a;

    int chosenA = 0;
    if (sumVals > 1e-9 && i > 100)  // adapt after warm-up
    {
        uniform_real_distribution<double> dist(0.0, sumVals);
        double r = dist(rng);
        double cum = 0;
        for (int k = 0; k < (int)alphas.size(); k++)
        {
            cum += avgVal[k];
            if (r <= cum) { chosenA = k; break; }
        }
    }
    else
    {
        chosenA = uniform_int_distribution<int>(0, alphas.size() - 1)(rng);
    }

    vector<int> sol = semiGreedyMaxCut(g, alphas[chosenA], rng);
    LocalSearchResult lsRes = localSearch(g, sol);
    int w = computeCutWeight(g, lsRes.partition);

    if (counts[chosenA] > 100)
    {
        double decay = 0.95;
        avgVal[chosenA] = avgVal[chosenA] * decay + w * (1 - decay);
    }
    else
    {
        avgVal[chosenA] = (avgVal[chosenA] * counts[chosenA] + w) / (counts[chosenA] + 1);
        counts[chosenA]++;
    }

    // track best overall ...
}
```

---

## Problem 6: Perturbation-Based Iterated Local Search

After local search converges, **perturb** the solution by randomly flipping a fraction `p` of vertices
(with probability proportional to their delta gain — flips that look less harmful are more likely),
then run local search again.  Repeat for a fixed number of iterations.

**Key part of solution:**

```cpp
double perturbationRate = 0.1;  // flip 10% of vertices
mt19937& rng;

for (int iter = 0; iter < maxIterations; iter++)
{
    // Perturb: randomly flip a fraction of vertices
    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    shuffle(perm.begin(), perm.end(), rng);

    int flipCount = max(1, (int)(perturbationRate * n));
    vector<int> perturbed = currentPartition;
    for (int i = 0; i < flipCount; i++)
        perturbed[perm[i]] = 1 - perturbed[perm[i]];

    // Run local search from perturbed solution
    LocalSearchResult lsRes = localSearch(g, perturbed);
    int newW = computeCutWeight(g, lsRes.partition);

    if (newW > bestWeight)
    {
        bestWeight = newW;
        bestPartition = lsRes.partition;
    }

    // Accept if better (or could use SA-style acceptance)
    if (newW >= currentWeight)
    {
        currentPartition = lsRes.partition;
        currentWeight = newW;
    }
}
```
