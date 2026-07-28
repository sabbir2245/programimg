# CSE 318 Assignment 02 — Solving the Max-Cut Problem by GRASP

**Date:** July 6, 2026

---

## Problem Statement

Given an undirected graph $G = (V, U)$ with vertices $V$, edges $U$, and weights $w_{uv}$ for each edge $(u, v) \in U$, the **Maximum Cut (MAX-CUT)** problem is to find a nonempty proper subset $S \subset V$ ($S \neq \emptyset$) that maximizes the cut weight:

$$
w(S, \bar{S}) = \sum_{u \in S, v \in \bar{S}} w_{uv}
$$

---

## Algorithms to Implement

### 1. Randomized Heuristic
Place each vertex into partition $X$ or $Y$ uniformly at random (probability $\frac{1}{2}$ each). Run $n$ times and average the cut weights.

### 2. Greedy Heuristic
Start by placing the endpoints of the maximum-weight edge into $X$ and $Y$. For each remaining unassigned vertex, place it into the partition where it contributes the most to the current partial cut.

### 3. Semi-Greedy Heuristic
Builds on the greedy function by introducing randomness. A **Restricted Candidate List (RCL)** is constructed using a value-based method:

$$
\mu = w_{\min} + \alpha \cdot (w_{\max} - w_{\min}), \quad \alpha \in [0, 1]
$$

Candidates with greedy value $\ge \mu$ enter the RCL, and one is selected randomly.

Greedy function for vertex $v$:

$$
\sigma_X(v) = \sum_{u \in Y} w_{vu}, \quad
\sigma_Y(v) = \sum_{u \in X} w_{vu}
$$

$$
\text{greedy value} = \max\{\sigma_X(v), \sigma_Y(v)\}
$$

### 4. Local Search
Given a feasible cut $(S, \bar{S})$, evaluate moving each vertex to the opposite partition. The change in cut weight for vertex $v$:

$$
\delta(v) =
\begin{cases}
\sigma_S(v) - \sigma_{\bar{S}}(v), & \text{if } v \in S \\
\sigma_{\bar{S}}(v) - \sigma_S(v), & \text{if } v \in \bar{S}
\end{cases}
$$

Apply the best improving move. Repeat until no improvement is possible (local optimum).

### 5. GRASP (Greedy Randomized Adaptive Search Procedure)
Iterates `MaxIterations` times:
1. **Construction:** Build a solution using the semi-greedy heuristic.
2. **Local Search:** Improve the constructed solution via local search.
3. Keep the best solution found across all iterations.

---

## Input Format

- **First line:** `n m` — number of vertices and edges.
- **Next $m$ lines:** `V1 V2 Wt` — an undirected edge with weight `Wt`.

---

## Benchmark Data Set

54 input graphs. Known best solutions for 24 of them:

| Problem | Known Best | Problem | Known Best | Problem | Known Best | Problem | Known Best |
|---------|------------|---------|------------|---------|------------|---------|------------|
| G1      | 12078      | G14     | 3187       | G32     | 1560       | G43     | 7027       |
| G2      | 12084      | G15     | 3169       | G33     | 1537       | G44     | 7022       |
| G3      | 12077      | G16     | 3172       | G34     | 1541       | G45     | 7020       |
| G11     | 627        | G22     | 14123      | G35     | 8000       | G48     | 6000       |
| G12     | 621        | G23     | 14129      | G36     | 7996       | G49     | 6000       |
| G13     | 645        | G24     | 14131      | G37     | 8009       | G50     | 5988       |

---

## Deliverables

### 1. CSV File (`2205***.csv`)
Summary of results from all 5 algorithms on all 54 graphs. Include $\alpha$ values for semi-greedy.

### 2. Report (`2205***.pdf`)
- High-level description of each algorithm.
- Comparison of algorithm performance.
- Plots/visualizations.

### 3. Source Code
Place all source files in a folder named `2205***`, include report and CSV, compress to `2205***.zip`, and submit via Moodle.

---

## Mark Distribution

| Task                               | Marks |
|------------------------------------|-------|
| Randomized Algorithm               | 10    |
| Greedy Algorithm                   | 10    |
| Semi-Greedy Algorithm              | 20    |
| GRASP                              | 40    |
| Report                             | 10    |
| Observation from Plots             | 5     |
| Proper Submission                  | 5     |
| **Total**                          | **100** |

---

**Submission Deadline:** July 20, Monday, 11:55 PM
