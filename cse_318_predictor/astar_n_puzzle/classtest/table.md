### Uninformed Search Algorithms Comparison

| Search Strategy | Complete? | Time Complexity | Space Complexity | Optimal? |
| :--- | :--- | :--- | :--- | :--- |
| **Breadth-First Search (BFS)** | **Yes** (if branching factor $b$ is finite) | $O(b^{d+1})$ | $O(b^{d+1})$ (keeps every node in memory) | **Yes** (if step cost is constant/1) |
| **Uniform-Cost Search (UCS)** | **Yes** (if step cost $\ge \epsilon > 0$) | Number of nodes with path cost $g(n) \le C^*$ | Number of nodes with path cost $g(n) \le C^*$ | **Yes** (for any non-negative step cost) |
| **Depth-First Search (DFS)** | **No** (fails in infinite-depth spaces) | $O(b^m)$ (where $m$ is max depth) | $O(bm)$ (linear space) | **No** (may find a non-optimal goal first) |
| **Depth-Limited Search (DLS)** | **No** (fails if solution is deeper than limit $L$) | $O(b^L)$ | $O(bL)$ | **No** (suboptimal if $L > d$) |
| **Iterative Deepening (IDS)** | **Yes** | $O(b^d)$ | $O(bd)$ (inherits DFS's memory efficiency) | **Yes** (if step cost = 1) |
| **Bi-Directional Search** | **Yes** (if both directions use BFS) | $O(b^{d/2})$ | $O(b^{d/2})$ | **Yes** (if step cost is constant/1) |

---

### Variable Guide for Your Exam:
* **$b$**: Branching factor (the maximum number of successors any node can have).
* **$d$**: Depth of the shallowest (closest) goal node.
* **$m$**: Maximum depth of the state space (can be infinite).
* **$L$**: Depth limit set for Depth-Limited Search.
* **$C^*$**: Cost of the optimal path.