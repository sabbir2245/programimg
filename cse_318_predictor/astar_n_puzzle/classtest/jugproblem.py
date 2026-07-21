from collections import deque
import math

def is_solvable(jug1_cap: int, jug2_cap: int, target: int) -> bool:
    """
    Checks if a solution is mathematically possible using Bézout's identity.
    The target must be less than or equal to the largest jug and a multiple
    of the Greatest Common Divisor (GCD) of both jugs.
    """
    if target > max(jug1_cap, jug2_cap):
        return False
    return target % math.gcd(jug1_cap, jug2_cap) == 0


def print_step(step_num: int, action: str, j1: int, j2: int, c1: int, c2: int):
    """
    Prints a clean, visual text representation of the current state of the jugs.
    """
    # Create simple text-based ASCII visual representations of fill levels
    j1_visual = f"[{'█' * j1}{' ' * (c1 - j1)}]"
    j2_visual = f"[{'█' * j2}{' ' * (c2 - j2)}]"
    
    print(f"Step {step_num:<2} | {action:<22} | Jug 1 {j1_visual} {j1}/{c1}g | Jug 2 {j2_visual} {j2}/{c2}g")


def solve_water_jug(jug1_cap: int, jug2_cap: int, target: int):
    """
    Solves the water jug problem using BFS to find the shortest path.
    Tracks states as (jug1_current, jug2_current) and stores the action history.
    """
    if not is_solvable(jug1_cap, jug2_cap, target):
        print("\n❌ Impossible! This combination cannot physically measure the target amount.")
        return

    # Queue stores: (current_j1, current_j2, path_history)
    # path_history is a list of tuples: (action_description, j1_after_action, j2_after_action)
    queue = deque([(0, 0, [("Initial State", 0, 0)])])
    visited = {(0, 0)}

    while queue:
        j1, j2, path = queue.popleft()

        # Goal check: Did either jug reach the target amount?
        if j1 == target or j2 == target:
            print(f"\n✅ Success! Target of {target} reached in {len(path) - 1} steps:")
            print("-" * 85)
            for idx, (action, res_j1, res_j2) in enumerate(path):
                print_step(idx, action, res_j1, res_j2, jug1_cap, jug2_cap)
            print("-" * 85)
            return

        # Generate all 6 possible rule-based transitions
        moves = [
            ("Fill Jug 1", jug1_cap, j2), # Fill J1
            ("Fill Jug 2", j1, jug2_cap), # Fill J2
            ("Empty Jug 1", 0, j2),       # Empty J1
            ("Empty Jug 2", j1, 0),       # Empty J2
            # Pour J1 -> J2
            ("Pour Jug 1 -> Jug 2", j1 - min(j1, jug2_cap - j2), j2 + min(j1, jug2_cap - j2)),
            # Pour J2 -> J1
            ("Pour Jug 2 -> Jug 1", j1 + min(j2, jug1_cap - j1), j2 - min(j2, jug1_cap - j1))
        ]

        for action, next_j1, next_j2 in moves:
            if (next_j1, next_j2) not in visited:
                visited.add((next_j1, next_j2))
                new_path = list(path)
                new_path.append((action, next_j1, next_j2))
                queue.append((next_j1, next_j2, new_path))

    print("\n❌ Explored all options. No solution found.")


if __name__ == "__main__":
    print("=== Water Jug Problem Solver ===")
    try:
        j1_size = int(input("Enter capacity of Jug 1: "))
        j2_size = int(input("Enter capacity of Jug 2: "))
        target_size = int(input("Enter target amount to measure: "))
        
        solve_water_jug(j1_size, j2_size, target_size)
        
    except ValueError:
        print("Please enter valid integers for sizes and targets.")