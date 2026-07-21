# Viva Questions — N-Puzzle & A* Search

## Inversion & Solvability
An inversion is a pair of tiles where a larger-numbered tile appears before a smaller-numbered one when the puzzle is flattened into a 1D sequence (excluding the blank). The total inversion count determines solvability. For an odd-width grid, the puzzle is solvable iff the inversion count is even. For even-width, solvability depends on both inversion parity and the blank's row from the bottom: (inversions + blank_row_from_bottom) must be even. This works because each move changes the inversion count by an odd number (specifically ±1 or ±(k-1) etc.), and the blank's vertical position also has a predictable parity effect, so the combined parity is invariant under legal moves. When comparing arbitrary start and goal states (not just the standard goal), we map start's tile order through the goal's order and check parity of the mapped sequence.

## Heuristic Function
A heuristic h(n) estimates the cost from the current state n to the goal. In the N-Puzzle, common heuristics are Manhattan distance (sum of horizontal + vertical distances of each tile from its goal position), Hamming distance (number of misplaced tiles), and Euclidean distance. The heuristic guides A* by prioritizing states closer to the goal, reducing the number of nodes explored. A good heuristic is both informative (close to true cost) and cheap to compute.

## Manhattan Distance
For each numbered tile, Manhattan distance = |current_row − goal_row| + |current_col − goal_col|, summed over all tiles (excluding the blank). It is admissible because each move moves one tile by exactly one step, so the true cost to move a tile to its goal is at least its Manhattan distance. It is also consistent (monotonic) because moving a tile by one step changes its Manhattan distance by exactly ±1, satisfying h(n) ≤ cost(n→n') + h(n').

## Linear Conflict
A linear conflict occurs when two tiles are in the same row or column that is also their goal row or column, but they are on the wrong sides of each other. For example, tile A should be left of tile B in row 3, but in the current state they appear as B, A in the same row. Since one tile must move out of the row and back (at least 2 extra moves), this adds a penalty of 2 to the Manhattan distance. Adding linear conflict penalties to Manhattan distance produces a more accurate (higher) heuristic that remains admissible because the penalty reflects actual minimum extra moves required.

## Admissible Heuristic
A heuristic is admissible if it never overestimates the true minimal cost to reach the goal, i.e., h(n) ≤ h*(n) for all states n. Admissibility is required for A* to guarantee optimality. Manhattan distance is admissible because each tile must move at least its Manhattan distance worth of steps. Linear conflict penalties preserve admissibility because they represent moves that must happen anyway — they are a lower bound on extra cost.

## Consistent (Monotonic) Heuristic
A heuristic is consistent if h(n) ≤ cost(n→n') + h(n') for every successor n' of n, and h(goal) = 0. Consistency implies admissibility and allows A* to never re-open closed nodes. Manhattan distance is consistent because moving a tile changes its Manhattan distance by exactly 1 while the move cost is 1, satisfying the triangle inequality.

## Optimality of A*
A* is optimal when using an admissible heuristic because it never overestimates the remaining cost, so the first time it pops a goal state from the open list, that state has the minimal possible f-value (g + h). Since all unexpanded nodes have f ≥ f(goal), no better path exists. If the heuristic is also consistent, A* never needs to revisit nodes, making it efficient.

## Tile Fatigue (c1)
In the fatigue variant, each tile's move cost increases with usage: the k-th move of tile t costs t × k. This makes g(n) path-dependent — two paths to the same board may have different g values because their move-count histories differ. The state must therefore include per-tile move counts, or the search must forgo standard closed-set pruning. The heuristic is weighted Manhattan (tile_value × Manhattan distance), ignoring fatigue, which remains admissible because fatigue only adds cost beyond this estimate.

## Toroidal Manhattan (b1)
On a torus board, the shortest distance between two positions in one dimension is min(|∆|, k − |∆|) because the blank can wrap around the edge. The toroidal Manhattan distance sums these shortest distances for each tile. This is the exact shortest path distance for a single tile on an empty torus, making it admissible. Move costs differ (normal = 1, wraparound = 2), so total cost is not simply the number of moves.

## Obstacle Cell — (-1) Blocked Cell (a1)
A blocked cell (-1) cannot be entered by any tile or the blank. The neighbor generation simply omits moves into the -1 cell. The heuristic excludes -1 from calculation (it never moves). The solvability check excludes -1 from the inversion count and compares permutation parity between start and goal. The blocked cell effectively shrinks the usable board area, and the blank must navigate around it.

## Why use tuple for state?
Tuples are immutable and hashable in Python, allowing them to be used as keys in dictionaries (best_g) and elements in sets (closed). This enables O(1) lookup for state membership and best-g-score tracking, which is critical for A* performance. Mutable types like lists cannot be hashed.

## Nodes Explored vs Nodes Expanded
"Nodes explored" typically counts how many nodes are popped from the open list (expanded). The closed set prevents re-expansion of already-explored states. A* may generate many more nodes (push to open list) than it explores (pop from open list), especially when the heuristic is weak and many states are revisited.
