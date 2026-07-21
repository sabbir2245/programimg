import heapq

#======== new code ==============
# Node now stores move_counts dict to track how many times each tile has been moved
class Node:
    def __init__(self, state, p=None, g=0, h=0, move_counts=None):
        self.state = state
        self.p = p
        self.g = g
        self.f = g + h
        self.move_counts = move_counts if move_counts is not None else {}

    def __lt__(self, other):
        return self.f < other.f

#======== new code ==============
# cost = tile_value * (times_moved + 1); tracks per-tile fatigue in move_counts
def get_neighbors(node):
    state = node.state
    move_counts = node.move_counts
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
            if tile_val == 0:
                continue
            times_moved = move_counts.get(tile_val, 0)
            cost = tile_val * (times_moved + 1)
            temp = [list(row) for row in state]
            temp[x][y], temp[nx][ny] = temp[nx][ny], temp[x][y]
            new_move_counts = dict(move_counts)
            new_move_counts[tile_val] = times_moved + 1
            neighbors.append((tuple(tuple(row) for row in temp), cost, new_move_counts))
    return neighbors

#======== new code ==============
# weighted Manhattan: tile_value * (|dr| + |dc|); ignores tile 0
def weighted_manhattan(state, goal):
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

#======== new code ==============
# A* uses weighted_manhattan heuristic; passes move_counts through get_neighbors(node)
def AstarLowlevel(start, goal):
    open_list = [Node(start, None, 0, weighted_manhattan(start, goal))]
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
        for nxt, cost, new_move_counts in get_neighbors(curr):
            g_score = curr.g + cost
            if nxt in best_g and g_score >= best_g[nxt]:
                continue
            best_g[nxt] = g_score
            heapq.heappush(open_list, Node(nxt, curr, g_score, weighted_manhattan(nxt, goal), new_move_counts))
    return None, nodes_explored, 0

#======== new code ==============
# outputs per-step accumulated cost; reconstructs fatigue costs from path
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
                move_counts = {}
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
                        times = move_counts.get(tile_val, 0)
                        step_cost = tile_val * (times + 1)
                        move_counts[tile_val] = times + 1
                        acc += step_cost

if __name__ == "__main__":
    import sys
    input_file = sys.argv[1] if len(sys.argv) > 1 else "c1_input.txt"
    output_file = sys.argv[2] if len(sys.argv) > 2 else "c1_output.txt"
    process_file(input_file, output_file)
