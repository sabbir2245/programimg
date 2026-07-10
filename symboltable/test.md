# CSE 310: Symbol Table Online Practice Problems

Two problems at similar difficulty to the online assignments (A1, B1, C1). Each tests different aspects of the symbol table infrastructure.

---

## Problem 1: Rename and Delete-by-Type in Current Scope

### Task 1 — Delete by Type in Current Scope (DD)

Create a command `DD <type>` which deletes **all symbols of the given type** in the **current scope only** (unlike `DT` which deletes across all scopes). After each deletion, print the standard deletion message.

### Task 2 — Rename Across Scopes (RN)

Create a command `RN <old_name> <new_name>` which renames a symbol **in whichever scope it exists** by walking the scope chain from current to root. If `old_name` is found, change its `name` field to `new_name`. If `new_name` already exists in that same scope (conflict), print an error and do nothing. If `old_name` is not found in any scope, print an error.

**Important**: If the symbol is renamed, the hash bucket it lives in changes (because the hash depends on the name). After renaming, the entry must be **moved** to the correct bucket for the new name. Simply overwriting the `name` field without moving the entry will put it in the wrong bucket and break future lookups. The safest approach: **delete the entry** from its current bucket, update the name, then **re-insert** it into the correct bucket.

### Example

Sample Input:
```
3
I x INT
I y FLOAT
I z INT
DD INT
P C
I a VAR
RN a b
RN a c
P C
Q
```

Sample Output:
```
	ScopeTable# 1 created
Cmd 1: I x INT
	Inserted in ScopeTable# 1 at position 1, 1
Cmd 2: I y FLOAT
	Inserted in ScopeTable# 1 at position 2, 1
Cmd 3: I z INT
	Inserted in ScopeTable# 1 at position 3, 1
Cmd 4: DD INT
	Deleted 'x' from ScopeTable# 1 at position 1, 1
	Deleted 'z' from ScopeTable# 1 at position 3, 1
Cmd 5: P C
	ScopeTable# 1
	1-->
	2--> <y,FLOAT>
	3-->
Cmd 6: I a VAR
	Inserted in ScopeTable# 1 at position 1, 1
Cmd 7: RN a b
	Deleted 'a' from ScopeTable# 1 at position 1, 1
	Inserted in ScopeTable# 1 at position 2, 1
Cmd 8: RN a c
	'a' not found in any of the ScopeTables
Cmd 9: P C
	ScopeTable# 1
	1-->
	2--> <y,FLOAT> <b,VAR>
	3-->
Cmd 10: Q
	ScopeTable# 1 removed
```

### Restrictions

- STL not allowed
- Must compile with `-fsanitize=address`
- `DD` deletes only in the **current scope** (not parent scopes)
- `RN` must **move** the entry to the new bucket after renaming — otherwise the hash is wrong

### Marks Distribution

| Task | Marks |
|------|-------|
| DD — delete all matching symbols in current scope | 3 |
| DD — correct deletion messages with position | 2 |
| RN — locate symbol across scope chain | 2 |
| RN — correct bucket move after rename | 2 |
| RN — conflict and not-found error handling | 1 |
| **Total** | **10** |

---

## Problem 2: TinyDB — A Scoped Key-Value Store Language

We will implement a tiny interactive database language called **TinyDB** using the symbol table infrastructure. Variables store **integer values** and are organized in scopes.

### Features

| Command | Description | Syntax |
|---------|-------------|--------|
| `{` / `}` | Enter / Exit scope | `{}` |
| `set` | Declare and set a key's value | `set <key> <value>` |
| `get` | Print the value of a key | `get <key>` |
| `del` | Delete a key in current scope only | `del <key>` |
| `has` | Check if a key exists (walks scopes) | `has <key>` |
| `add` | Add value to an existing key | `add <key> <amount>` |

### Rules

- The first line of input is the bucket count for the symbol table.
- **`set`**: If the key already exists in the **current scope**, output an error and do nothing. Otherwise, declare it with the given value.
- **`del`**: Delete the key from the **current scope only**. If not found, output an error.
- **`get`**: Walk the scope chain to find the key and print its value. If not found, output an error.
- **`has`**: Walk the scope chain. Print `> yes` if found, `> no` otherwise.
- **`add`**: Find the key via scope-chain lookup. If found, add `amount` to its value. If not found, output an error.

### Error Handling

- `set` on an already-declared key in the same scope: `> ERROR in line L: key 'X' already declared in this scope`
- `del` on a non-existent key in current scope: `> ERROR in line L: 'X' not found in current scope`
- `get` on a non-existent key: `> ERROR in line L: 'X' not found in any scope`
- `add` on a non-existent key: `> ERROR in line L: 'X' not found in any scope`
- Skip erroneous lines altogether; do not terminate the program.

### Example

Sample Input:
```
5
set a 10
set b 20
{
set a 30
get a
add a 5
get a
del a
has a
}
has a
get b
get c
set a 5
has c
del d
Q
```

Sample Output:
```
	ScopeTable# 1 created
	ScopeTable# 2 created
> Set a = 10 in ScopeTable# 2
> Set b = 20 in ScopeTable# 2
	ScopeTable# 3 created
> Set a = 30 in ScopeTable# 3
> 30
> Set a = 35 in ScopeTable# 3
> 35
> Deleted a from ScopeTable# 3 at position 1, 1
> no
	ScopeTable# 3 removed
> yes
> 20
> ERROR in line 13: 'c' not found in any scope
> Set a = 5 in ScopeTable# 2
> no
> ERROR in line 16: 'd' not found in current scope
Cmd 17: Q
	ScopeTable# 2 removed
```

### Restrictions

- STL not allowed
- Must compile with `-fsanitize=address`

### Boilerplate

```
ifstream code("code.txt");
int bucket_size;
code >> bucket_size;
int line = 0;
string opcode;
while (code >> opcode) {
    if (opcode == "{") { ... }
    else if (opcode == "}") { ... }
    else if (opcode == "set") { string key; int val; code >> key >> val; ... }
    else if (opcode == "get") { string key; code >> key; ... }
    else if (opcode == "del") { string key; code >> key; ... }
    else if (opcode == "has") { string key; code >> key; ... }
    else if (opcode == "add") { string key; int amt; code >> key >> amt; ... }
    line++;
}
```

### Marks Distribution

| Task | Marks |
|------|-------|
| `{` / `}` scope management | 1 |
| `set` — insert with value + redeclaration error | 2 |
| `get` — scope-chain lookup + output | 2 |
| `del` — delete in current scope only | 1 |
| `has` — check existence across scopes | 1 |
| `add` — modify value across scopes | 2 |
| Error messages and output format | 1 |
| **Total** | **10** |
