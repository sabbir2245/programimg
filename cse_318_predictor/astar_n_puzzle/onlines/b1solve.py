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
# torus board: coordinates wrap around edges; wraparound move costs 2, normal costs 1
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
        nx, ny = (x + dx) % n, (y + dy) % n
        is_wrapping = (dx == -1 and x == 0) or (dx == 1 and x == n - 1) or \
                      (dy == -1 and y == 0) or (dy == 1 and y == n - 1)
        cost = 2 if is_wrapping else 1
        temp = [list(row) for row in state]
        temp[x][y], temp[nx][ny] = temp[nx][ny], temp[x][y]
        neighbors.append((tuple(tuple(row) for row in temp), cost))
    return neighbors

#======== new code ==============
# toroidal Manhattan distance: min(dr, k-dr) + min(dc, k-dc) for each numbered tile
def toroidal_heuristic(state, goal):
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
                dr = min(abs(r - gr), n - abs(r - gr))
                dc = min(abs(c - gc), n - abs(c - gc))
                h += dr + dc
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

#======== new code ==============
# returns total path cost (goal_g) alongside path; no solvability check needed
def AstarLowlevel(start, goal):
    open_list = [Node(start, None, 0, toroidal_heuristic(start, goal))]
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
            heapq.heappush(open_list, Node(nxt, curr, g_score, toroidal_heuristic(nxt, goal)))
    return None, nodes_explored, 0

#======== new code ==============
# outputs per-step accumulated cost; no solvability check (inputs guaranteed solvable)
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
                        dr_raw = z2[0] - z1[0]
                        dc_raw = z2[1] - z1[1]
                        if abs(dr_raw) == n - 1:
                            acc += 2
                        elif abs(dr_raw) == 1:
                            acc += 1
                        if abs(dc_raw) == n - 1:
                            acc += 2
                        elif abs(dc_raw) == 1:
                            acc += 1

if __name__ == "__main__":
    import sys
    input_file = sys.argv[1] if len(sys.argv) > 1 else "b1_input.txt"
    output_file = sys.argv[2] if len(sys.argv) > 2 else "b1_output.txt"
    process_file(input_file, output_file)
