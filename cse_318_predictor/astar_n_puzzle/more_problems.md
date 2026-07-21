# More N-Puzzle Variants

Four additional problems at similar difficulty to a1/b1/c1, each with a complete Python solution.

---

## Problem 1: Weighted Tile Cost (Constant)

Each numbered tile t costs exactly t units to move one step. The blank (0) costs nothing. Unlike c1, there is **no fatigue accumulation** — moving tile 5 always costs 5, regardless of how many times it has been moved.

| Aspect | Specification |
|---|---|
| Move cost | face value of the tile sliding into blank (tile_val) |
| Heuristic | weighted Manhattan: Σ tile_val × (|dr| + |dc|) for numbered tiles |
| Solvability | standard inversion-parity check |
| Output | minimum total cost, nodes explored, path with per-step cost |

```python
import heapq

class Node:
    def __init__(self, state, p=None, g=0, h=0):
        self.state = state
        self.p = p
        self.g = g
        self.f = g + h

    def __lt__(self, other):
        return self.f < other.f

def get_neighbors(state):
    n = len(state)
    neighbors = []
    zero_pos = None
    for i in range(n):
        for j in range(n):
            if state[i][j] == 0:
                zero_pos = (i, j)
                break
        if zero_pos:
            break
    x, y = zero_pos
    for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
        nx, ny = x + dx, y + dy
        if 0 <= nx < n and 0 <= ny < n:
            tile_val = state[nx][ny]
            temp = [list(row) for row in state]
            temp[x][y], temp[nx][ny] = temp[nx][ny], temp[x][y]
            neighbors.append((tuple(tuple(row) for row in temp), tile_val))
    return neighbors

def heuristic(state, goal):
    n = len(state)
    goal_pos = {}
    for r in range(n):
        for c in range(n):
            val = goal[r][c]
            if val != 0:
                goal_pos[val] = (r, c)
    h = 0
    for r in range(n):
        for c in range(n):
            val = state[r][c]
            if val != 0:
                gr, gc = goal_pos[val]
                h += val * (abs(r - gr) + abs(c - gc))
    return h

def build_goal(k):
    rows = []
    val = 1
    for i in range(k):
        row = []
        for j in range(k):
            if i == k - 1 and j == k - 1:
                row.append(0)
            else:
                row.append(val)
                val += 1
        rows.append(tuple(row))
    return tuple(rows)

def count_inversions(arr):
    def merge_sort_count(a):
        if len(a) <= 1:
            return a, 0
        mid = len(a) // 2
        left, lc = merge_sort_count(a[:mid])
        right, rc = merge_sort_count(a[mid:])
        merged = []
        i = j = c = 0
        while i < len(left) and j < len(right):
            if left[i] <= right[j]:
                merged.append(left[i])
                i += 1
            else:
                merged.append(right[j])
                c += len(left) - i
                j += 1
        merged.extend(left[i:])
        merged.extend(right[j:])
        return merged, lc + rc + c
    _, inv = merge_sort_count(arr)
    return inv

def isSolvable(arr, k):
    flat = [x for row in arr for x in row if x != 0]
    inversions = count_inversions(flat)
    if k % 2 == 1:
        return inversions % 2 == 0
    blank_row = -1
    for i in range(k):
        if 0 in arr[i]:
            blank_row = i
            break
    row_from_bottom = k - blank_row
    if row_from_bottom % 2 == 1:
        return inversions % 2 == 0
    else:
        return inversions % 2 == 1

def AstarLowlevel(start, goal):
    open_list = [Node(start, None, 0, heuristic(start, goal))]
    closed = set()
    best_g = {start: 0}
    nodes_explored = 0
    while open_list:
        curr = heapq.heappop(open_list)
        nodes_explored += 1
        if curr.state == goal:
            goal_g = curr.g
            path = []
            while curr:
                path.append(curr.state)
                curr = curr.p
            return path[::-1], nodes_explored, goal_g
        if curr.state in closed:
            continue
        closed.add(curr.state)
        for nxt, cost in get_neighbors(curr.state):
            g_score = curr.g + cost
            if nxt in best_g and g_score >= best_g[nxt]:
                continue
            best_g[nxt] = g_score
            heapq.heappush(open_list, Node(nxt, curr, g_score, heuristic(nxt, goal)))
    return None, nodes_explored, 0

def process_file(input_filename, output_filename):
    with open(input_filename, 'r') as infile, open(output_filename, 'w') as outfile:
        lines = [line.strip() for line in infile if line.strip()]
        if not lines:
            return
        num_tests = int(lines[0])
        idx = 1
        for t in range(num_tests):
            if idx >= len(lines):
                break
            k = int(lines[idx])
            idx += 1
            start_rows = []
            for _ in range(k):
                start_rows.append(tuple(int(x) for x in lines[idx].split()))
                idx += 1
            start_grid = tuple(start_rows)
            goal_grid = build_goal(k)
            if not isSolvable(start_grid, k):
                outfile.write("Unsolvable puzzle\n")
                continue
            result, nodes_explored, total_cost = AstarLowlevel(start_grid, goal_grid)
            if result is None:
                outfile.write("Unsolvable puzzle\n")
            else:
                outfile.write(f"Minimum total cost = {total_cost}\n")
                outfile.write(f"Nodes explored = {nodes_explored}\n")
                acc = 0
                for i, state in enumerate(result):
                    outfile.write(f"Cost = {acc}\n")
                    for row in state:
                        outfile.write(" ".join(str(x) for x in row) + "\n")
                    outfile.write("\n")
                    if i < len(result) - 1:
                        nxt = result[i + 1]
                        n = len(state)
                        z1 = z2 = None
                        for r in range(n):
                            for c in range(n):
                                if state[r][c] == 0:
                                    z1 = (r, c)
                                if nxt[r][c] == 0:
                                    z2 = (r, c)
                        tile_val = state[z2[0]][z2[1]]
                        acc += tile_val

if __name__ == "__main__":
    import sys
    input_file = sys.argv[1] if len(sys.argv) > 1 else "p1_input.txt"
    output_file = sys.argv[2] if len(sys.argv) > 2 else "p1_output.txt"
    process_file(input_file, output_file)
```

---

## Problem 2: King-Move Blank (8-Directional)

The blank moves like a chess king — 8 directions (N, S, E, W, NE, NW, SE, SW). All moves cost 1. Diagonal moves allow a tile to change both row and column in a single step.

| Aspect | Specification |
|---|---|
| Move cost | 1 for all 8 directions |
| Heuristic | Chebyshev distance: Σ max(|dr|, |dc|) for numbered tiles |
| Solvability | not needed (all configurations reachable with king moves) |
| Output | minimum number of moves, nodes explored, path |

```python
import heapq

class Node:
    def __init__(self, state, p=None, g=0, h=0):
        self.state = state
        self.p = p
        self.g = g
        self.f = g + h

    def __lt__(self, other):
        return self.f < other.f

def get_neighbors(state):
    n = len(state)
    neighbors = []
    zero_pos = None
    for i in range(n):
        for j in range(n):
            if state[i][j] == 0:
                zero_pos = (i, j)
                break
        if zero_pos:
            break
    x, y = zero_pos
    for dx in (-1, 0, 1):
        for dy in (-1, 0, 1):
            if dx == 0 and dy == 0:
                continue
            nx, ny = x + dx, y + dy
            if 0 <= nx < n and 0 <= ny < n:
                temp = [list(row) for row in state]
                temp[x][y], temp[nx][ny] = temp[nx][ny], temp[x][y]
                neighbors.append((tuple(tuple(row) for row in temp), 1))
    return neighbors

def chebyshev_heuristic(state, goal):
    n = len(state)
    goal_pos = {}
    for r in range(n):
        for c in range(n):
            val = goal[r][c]
            if val != 0:
                goal_pos[val] = (r, c)
    h = 0
    for r in range(n):
        for c in range(n):
            val = state[r][c]
            if val != 0:
                gr, gc = goal_pos[val]
                h += max(abs(r - gr), abs(c - gc))
    return h

def build_goal(k):
    rows = []
    val = 1
    for i in range(k):
        row = []
        for j in range(k):
            if i == k - 1 and j == k - 1:
                row.append(0)
            else:
                row.append(val)
                val += 1
        rows.append(tuple(row))
    return tuple(rows)

def AstarLowlevel(start, goal):
    open_list = [Node(start, None, 0, chebyshev_heuristic(start, goal))]
    closed = set()
    best_g = {start: 0}
    nodes_explored = 0
    while open_list:
        curr = heapq.heappop(open_list)
        nodes_explored += 1
        if curr.state == goal:
            path = []
            while curr:
                path.append(curr.state)
                curr = curr.p
            return path[::-1], nodes_explored
        if curr.state in closed:
            continue
        closed.add(curr.state)
        for nxt, cost in get_neighbors(curr.state):
            g_score = curr.g + cost
            if nxt in best_g and g_score >= best_g[nxt]:
                continue
            best_g[nxt] = g_score
            heapq.heappush(open_list, Node(nxt, curr, g_score, chebyshev_heuristic(nxt, goal)))
    return None, nodes_explored

def process_file(input_filename, output_filename):
    with open(input_filename, 'r') as infile, open(output_filename, 'w') as outfile:
        lines = [line.strip() for line in infile if line.strip()]
        if not lines:
            return
        num_tests = int(lines[0])
        idx = 1
        for t in range(num_tests):
            if idx >= len(lines):
                break
            k = int(lines[idx])
            idx += 1
            start_rows = []
            for _ in range(k):
                start_rows.append(tuple(int(x) for x in lines[idx].split()))
                idx += 1
            start_grid = tuple(start_rows)
            goal_grid = build_goal(k)
            result, nodes_explored = AstarLowlevel(start_grid, goal_grid)
            if result is None:
                outfile.write("Unsolvable puzzle\n")
            else:
                moves = len(result) - 1
                outfile.write(f"Minimum number of moves = {moves}\n")
                outfile.write(f"Nodes explored = {nodes_explored}\n")
                for state in result:
                    for row in state:
                        outfile.write(" ".join(str(x) for x in row) + "\n")
                    outfile.write("\n")

if __name__ == "__main__":
    import sys
    input_file = sys.argv[1] if len(sys.argv) > 1 else "p2_input.txt"
    output_file = sys.argv[2] if len(sys.argv) > 2 else "p2_output.txt"
    process_file(input_file, output_file)
```

---

## Problem 3: Dual-Blank Puzzle

The board contains two blanks (0 and -2). Either can be moved in any turn. Each move costs 1. The goal is the standard board with 0 at bottom-right and -2 at top-left (or any other fixed position). Two blanks make the puzzle strictly easier — every configuration is solvable.

| Aspect | Specification |
|---|---|
| Move cost | 1 for either blank |
| Heuristic | standard Manhattan for numbered tiles only (both blanks ignored) |
| Solvability | not needed (all configurations reachable with two blanks) |
| Output | minimum number of moves, nodes explored, path |

```python
import heapq

class Node:
    def __init__(self, state, p=None, g=0, h=0):
        self.state = state
        self.p = p
        self.g = g
        self.f = g + h

    def __lt__(self, other):
        return self.f < other.f

def get_neighbors(state):
    n = len(state)
    neighbors = []
    blanks = [(i, j) for i in range(n) for j in range(n) if state[i][j] == 0 or state[i][j] == -2]
    for x, y in blanks:
        for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            nx, ny = x + dx, y + dy
            if 0 <= nx < n and 0 <= ny < n:
                temp = [list(row) for row in state]
                temp[x][y], temp[nx][ny] = temp[nx][ny], temp[x][y]
                neighbors.append((tuple(tuple(row) for row in temp), 1))
    return neighbors

def heuristic(state, goal):
    n = len(state)
    goal_pos = {}
    for r in range(n):
        for c in range(n):
            val = goal[r][c]
            if val > 0:
                goal_pos[val] = (r, c)
    h = 0
    for r in range(n):
        for c in range(n):
            val = state[r][c]
            if val > 0:
                gr, gc = goal_pos[val]
                h += abs(r - gr) + abs(c - gc)
    return h

def build_goal(k):
    rows = []
    val = 1
    for i in range(k):
        row = []
        for j in range(k):
            if i == k - 1 and j == k - 1:
                row.append(0)
            elif i == 0 and j == 0:
                row.append(-2)
            else:
                row.append(val)
                val += 1
        rows.append(tuple(row))
    return tuple(rows)

def AstarLowlevel(start, goal):
    open_list = [Node(start, None, 0, heuristic(start, goal))]
    closed = set()
    best_g = {start: 0}
    nodes_explored = 0
    while open_list:
        curr = heapq.heappop(open_list)
        nodes_explored += 1
        if curr.state == goal:
            path = []
            while curr:
                path.append(curr.state)
                curr = curr.p
            return path[::-1], nodes_explored
        if curr.state in closed:
            continue
        closed.add(curr.state)
        for nxt, cost in get_neighbors(curr.state):
            g_score = curr.g + cost
            if nxt in best_g and g_score >= best_g[nxt]:
                continue
            best_g[nxt] = g_score
            heapq.heappush(open_list, Node(nxt, curr, g_score, heuristic(nxt, goal)))
    return None, nodes_explored

def process_file(input_filename, output_filename):
    with open(input_filename, 'r') as infile, open(output_filename, 'w') as outfile:
        lines = [line.strip() for line in infile if line.strip()]
        if not lines:
            return
        num_tests = int(lines[0])
        idx = 1
        for t in range(num_tests):
            if idx >= len(lines):
                break
            k = int(lines[idx])
            idx += 1
            start_rows = []
            for _ in range(k):
                start_rows.append(tuple(int(x) for x in lines[idx].split()))
                idx += 1
            start_grid = tuple(start_rows)
            goal_grid = build_goal(k)
            result, nodes_explored = AstarLowlevel(start_grid, goal_grid)
            if result is None:
                outfile.write("Unsolvable puzzle\n")
            else:
                moves = len(result) - 1
                outfile.write(f"Minimum number of moves = {moves}\n")
                outfile.write(f"Nodes explored = {nodes_explored}\n")
                for state in result:
                    for row in state:
                        outfile.write(" ".join(str(x) for x in row) + "\n")
                    outfile.write("\n")

if __name__ == "__main__":
    import sys
    input_file = sys.argv[1] if len(sys.argv) > 1 else "p3_input.txt"
    output_file = sys.argv[2] if len(sys.argv) > 2 else "p3_output.txt"
    process_file(input_file, output_file)
```

---

## Problem 4: Checkpoint Puzzle

One cell is the **checkpoint** (-1). The blank must swap with -1 at least once during the path (this "activates" the checkpoint). After activation, the -1 tile can be moved freely. The goal state must have -1 back at its starting position (top-left) and the board otherwise matching the standard goal.

The node includes a boolean `activated`. The search state key is `(board, activated)`.

| Aspect | Specification |
|---|---|
| Move cost | 1 for all moves |
| State key | `(board_tuple, activated_flag)` |
| Heuristic | standard Manhattan for numbered tiles + -1 tile (excludes only 0) |
| Goal | board matches goal AND activated is True |
| Solvability | standard inversion-parity check |

```python
import heapq

CHECKPOINT_GOAL = -1

class Node:
    def __init__(self, state, activated=False, p=None, g=0, h=0):
        self.state = state
        self.activated = activated
        self.p = p
        self.g = g
        self.f = g + h

    def __lt__(self, other):
        return self.f < other.f

def get_neighbors(state):
    n = len(state)
    neighbors = []
    zero_pos = None
    for i in range(n):
        for j in range(n):
            if state[i][j] == 0:
                zero_pos = (i, j)
                break
        if zero_pos:
            break
    x, y = zero_pos
    for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
        nx, ny = x + dx, y + dy
        if 0 <= nx < n and 0 <= ny < n:
            tile_val = state[nx][ny]
            temp = [list(row) for row in state]
            temp[x][y], temp[nx][ny] = temp[nx][ny], temp[x][y]
            activated = (tile_val == CHECKPOINT_GOAL)
            neighbors.append((tuple(tuple(row) for row in temp), activated))
    return neighbors

def heuristic(state, goal):
    n = len(state)
    goal_pos = {}
    for r in range(n):
        for c in range(n):
            val = goal[r][c]
            if val != 0:
                goal_pos[val] = (r, c)
    h = 0
    for r in range(n):
        for c in range(n):
            val = state[r][c]
            if val != 0:
                gr, gc = goal_pos[val]
                h += abs(r - gr) + abs(c - gc)
    return h

def build_goal(k, checkpoint_pos=(0, 0)):
    rows = []
    val = 1
    for i in range(k):
        row = []
        for j in range(k):
            if (i, j) == checkpoint_pos:
                row.append(CHECKPOINT_GOAL)
            elif i == k - 1 and j == k - 1:
                row.append(0)
            else:
                row.append(val)
                val += 1
        rows.append(tuple(row))
    return tuple(rows)

def count_inversions(arr):
    def merge_sort_count(a):
        if len(a) <= 1:
            return a, 0
        mid = len(a) // 2
        left, lc = merge_sort_count(a[:mid])
        right, rc = merge_sort_count(a[mid:])
        merged = []
        i = j = c = 0
        while i < len(left) and j < len(right):
            if left[i] <= right[j]:
                merged.append(left[i])
                i += 1
            else:
                merged.append(right[j])
                c += len(left) - i
                j += 1
        merged.extend(left[i:])
        merged.extend(right[j:])
        return merged, lc + rc + c
    _, inv = merge_sort_count(arr)
    return inv

def isSolvable(arr, k):
    flat = [x for row in arr for x in row if x != 0 and x != CHECKPOINT_GOAL]
    inversions = count_inversions(flat)
    if k % 2 == 1:
        return inversions % 2 == 0
    blank_row = -1
    for i in range(k):
        if 0 in arr[i]:
            blank_row = i
            break
    row_from_bottom = k - blank_row
    if row_from_bottom % 2 == 1:
        return inversions % 2 == 0
    else:
        return inversions % 2 == 1

def AstarLowlevel(start, goal):
    open_list = [Node(start, False, None, 0, heuristic(start, goal))]
    closed = set()
    best_g = {(start, False): 0}
    nodes_explored = 0
    while open_list:
        curr = heapq.heappop(open_list)
        nodes_explored += 1
        if curr.state == goal and curr.activated:
            path = []
            while curr:
                path.append(curr.state)
                curr = curr.p
            return path[::-1], nodes_explored
        key = (curr.state, curr.activated)
        if key in closed:
            continue
        closed.add(key)
        for nxt, act in get_neighbors(curr.state):
            new_act = curr.activated or act
            g_score = curr.g + 1
            nkey = (nxt, new_act)
            if nkey in best_g and g_score >= best_g[nkey]:
                continue
            best_g[nkey] = g_score
            heapq.heappush(open_list, Node(nxt, new_act, curr, g_score, heuristic(nxt, goal)))
    return None, nodes_explored

def process_file(input_filename, output_filename):
    with open(input_filename, 'r') as infile, open(output_filename, 'w') as outfile:
        lines = [line.strip() for line in infile if line.strip()]
        if not lines:
            return
        num_tests = int(lines[0])
        idx = 1
        for t in range(num_tests):
            if idx >= len(lines):
                break
            k = int(lines[idx])
            idx += 1
            start_rows = []
            for _ in range(k):
                start_rows.append(tuple(int(x) for x in lines[idx].split()))
                idx += 1
            start_grid = tuple(start_rows)
            goal_grid = build_goal(k)
            if not isSolvable(start_grid, k):
                outfile.write("Unsolvable puzzle\n")
                continue
            result, nodes_explored = AstarLowlevel(start_grid, goal_grid)
            if result is None:
                outfile.write("Unsolvable puzzle\n")
            else:
                moves = len(result) - 1
                outfile.write(f"Minimum number of moves = {moves}\n")
                outfile.write(f"Nodes explored = {nodes_explored}\n")
                for state in result:
                    for row in state:
                        outfile.write(" ".join(str(x) for x in row) + "\n")
                    outfile.write("\n")

if __name__ == "__main__":
    import sys
    input_file = sys.argv[1] if len(sys.argv) > 1 else "p4_input.txt"
    output_file = sys.argv[2] if len(sys.argv) > 2 else "p4_output.txt"
    process_file(input_file, output_file)
```

---

## Comparison Table

| Problem | Cost Model | Heuristic | Solvability | Key Challenge |
|---|---|---|---|---|
| P1: Weighted Tile | tile_val per step | weighted Manhattan (t×dist) | standard parity | weighted g(n) |
| P2: King Blank | 1 per 8-dir move | Chebyshev max(dr, dc) | none needed | higher branching factor |
| P3: Dual-Blank | 1 per 2 blanks | Manhattan (tiles only) | none needed | 2× neighbors per state |
| P4: Checkpoint | 1 per move | Manhattan (includes -1) | standard parity | boolean state flag |
