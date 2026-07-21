import heapq

class Node:
    def __init__(self, state, p=None, g=0, h=0):
        self.state = state
        self.p = p
        self.g = g
        self.f = g + h

    def __lt__(self, other):
        return self.f < other.f

#======== new code ==============
# neighbor generation skips the blocked cell (-1); the blank cannot swap with it
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
        if 0 <= nx < n and 0 <= ny < n and state[nx][ny] != -1:
            temp = [list(row) for row in state]
            temp[x][y], temp[nx][ny] = temp[nx][ny], temp[x][y]
            neighbors.append((tuple(tuple(row) for row in temp), 1))
    return neighbors

#======== new code ==============
# Manhattan distance for numbered tiles only; excludes both 0 (blank) and -1 (blocked)
def heuristic(state, goal):
    n = len(state)
    goal_pos = {}
    for r in range(n):
        for c in range(n):
            val = goal[r][c]
            if val != 0 and val != -1:
                goal_pos[val] = (r, c)
    h = 0
    for r in range(n):
        for c in range(n):
            val = state[r][c]
            if val != 0 and val != -1:
                gr, gc = goal_pos[val]
                h += abs(r - gr) + abs(c - gc)
    return h

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

#======== new code ==============
# solvability compares permutation parity between start and goal (excluding 0 and -1)
def isSolvable(start, goal, k):
    s_flat = [x for row in start for x in row if x != 0 and x != -1]
    g_flat = [x for row in goal for x in row if x != 0 and x != -1]
    pos_in_goal = {val: i for i, val in enumerate(g_flat)}
    mapped = [pos_in_goal[val] for val in s_flat]
    inversions = count_inversions(mapped)
    if k % 2 == 1:
        return inversions % 2 == 0
    blank_row = -1
    for i in range(k):
        if 0 in start[i]:
            blank_row = i
            break
    row_from_bottom = k - blank_row
    if row_from_bottom % 2 == 1:
        return inversions % 2 == 0
    else:
        return inversions % 2 == 1

#======== new code ==============
# A* uses custom heuristic; no weight parameter since Manhattan is unweighted here
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

#======== new code ==============
# reads both start board and goal board for each test case
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
            goal_rows = []
            for _ in range(k):
                goal_rows.append(tuple(int(x) for x in lines[idx].split()))
                idx += 1
            start_grid = tuple(start_rows)
            goal_grid = tuple(goal_rows)
            if not isSolvable(start_grid, goal_grid, k):
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
    input_file = sys.argv[1] if len(sys.argv) > 1 else "a1_input.txt"
    output_file = sys.argv[2] if len(sys.argv) > 2 else "a1_output.txt"
    process_file(input_file, output_file)
