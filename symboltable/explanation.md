# CSE 310 Symbol Table — Code Explanation

This document explains how `2205040_symbol_table.cpp` works. It is a **hash-table-based hierarchical symbol table** for a compiler course, built without the C++ STL (it uses a custom linked list template from `2205040_general.h`).

---

## Table of Contents

1. [High-Level Architecture](#1-high-level-architecture)
2. [Global Output Stream](#2-global-output-stream)
3. [Class `SymbolInfo`](#3-class-symbolinfo)
4. [Class `ScopeTable`](#4-class-scopetable)
   - [4.1 Hash Function — `SDBMHash`](#41-hash-function--sdbmhash)
   - [4.2 Insert](#42-insert)
   - [4.3 Lookup](#43-lookup)
   - [4.4 Delete](#44-delete)
   - [4.5 Print](#45-print)
   - [4.6 Constructor & Destructor](#46-constructor--destructor)
5. [Class `SymbolTable`](#5-class-symboltable)
   - [5.1 Scope Lifecycle](#51-scope-lifecycle)
   - [5.2 Delegating Methods](#52-delegating-methods)
   - [5.3 Cross-Scope Lookup](#53-cross-scope-lookup)
   - [5.4 Root Scope Guard](#54-root-scope-guard)
6. [Command Processor — `processCommand`](#6-command-processor--processcommand)
   - [6.1 `I` (Insert) — Special Forms](#61-i-insert--special-forms)
   - [6.2 `L` (Lookup)](#62-l-lookup)
   - [6.3 `D` (Delete)](#63-d-delete)
   - [6.4 `S` / `E` (Scope Enter / Exit)](#64-s--e-scope-enter--exit)
   - [6.5 `P` (Print)](#65-p-print)
7. [Main Function](#7-main-function)
   - [7.1 Input Parsing](#71-input-parsing)
   - [7.2 Command Dispatch Loop](#72-command-dispatch-loop)
   - [7.3 Command Validation Gate](#73-command-validation-gate)
8. [Supporting File: `2205040_general.h`](#8-supporting-file-2205040generalh)
9. [Summary of Output Format](#9-summary-of-output-format)

---

## 1. High-Level Architecture

The program implements a **scope-chained symbol table** — a stack of hash tables, each representing a scope:

```
SymbolTable
  └─ ScopeTable (current, innermost)
       └─ ScopeTable (parent)
            └─ ScopeTable (grandparent)
                 └─ ... (root)
```

Each `ScopeTable` is a **hash table** whose buckets are custom linked lists (`mylist<SymbolInfo>`). The buckets hold `SymbolInfo` entries (name, type, optional metadata).

The program reads a script-like input file where each line is a command (`I`, `L`, `D`, `S`, `E`, `P`, `Q`) that manipulates the symbol table. All output is captured into a global `ostringstream` and flushed to a file at the end.

---

## 2. Global Output Stream

```cpp
ostringstream out;           // line 9
```

**Every diagnostic message** (insert confirmations, lookup results, errors, print output) is written to this **single global** `ostringstream`. At program exit (`main`, line 373–375), the collected string is written to the output file:

```cpp
ofstream fout(outputFile);
fout << out.str();
fout.close();
```

This pattern avoids threading an output stream through every function parameter.

---

## 3. Class `SymbolInfo`

```cpp
class SymbolInfo {
    string name;
    string type;
    string extraInfo;
    // SymbolInfo* next;     // (dead code — commented out)
};
```

Every symbol stored in the table has:

| Field | Purpose |
|---|---|
| `name` | The identifier name (e.g. `"foo"`, `"i"`) |
| `type` | The type string (e.g. `"VAR"`, `"INT"`, `"FUNCTION"`, `"STRUCT"`) |
| `extraInfo` | Optional metadata (e.g. function signature `"INT<==(INT,FLOAT)"`, struct field list `"{(INT,a),(FLOAT,b)}"`) |

The dead field `next` and its getter/setter (`getNext`/`setNext`) were originally intended for separate chaining but are never used — the `mylist` class handles its own internal linked-list nodes. They have been commented out.

---

## 4. Class `ScopeTable`

A **single scope** backed by a **separate-chaining hash table**.

### 4.1 Hash Function — `SDBMHash`

```cpp
unsigned int SDBMHash(const string& str) {
    unsigned int h = 0;
    for (unsigned int i = 0; i < str.length(); i++) {
        h = ((str[i]) + (h << 6) + (h << 16) - h) % total_buckets;
    }
    return h;
}
```

- The **SDBM** hash (a simple, fast general-purpose hash).
- The modulo (`% total_buckets`) folds the hash into the bucket array bounds.
- **Caution**: If `total_buckets` is 0, this causes a division-by-zero runtime error. The program now guards against this in `main` (lines 347–350).

### 4.2 Insert

```cpp
bool Insert(string name, string type, string extra = "");
```

1. Compute `hash = SDBMHash(name)`.
2. Access `table[hash]` (the bucket = `mylist<SymbolInfo>`).
3. Walk the bucket's linked list checking for a duplicate `name`.
4. If found: print `"'name' already exists..."` and return `false`.
5. Otherwise: `push_back` a new `SymbolInfo` and print `"Inserted in ScopeTable# N at position bucket, pos"`.

The position output uses **1-based indexing**: `bucketIdx = hash + 1`, and the chain position is the element's index within that bucket (starting at 1).

### 4.3 Lookup

```cpp
SymbolInfo* Lookup(string name, int& outBucket, int& outPos);
```

Scans **only this scope's hash table** for `name`. Returns the `SymbolInfo*` if found, `nullptr` otherwise. The `outBucket` and `outPos` reference parameters report location (1-based) for use by the caller's diagnostic printing.

### 4.4 Delete

```cpp
bool Delete(string name);
```

1. Compute `hash = SDBMHash(name)`.
2. Use `mylist::remove_if` with a lambda that matches by name.
3. If removed: print `"Deleted 'name' from ScopeTable# N at position bucket, pos"`.
4. If not found: print `"Not found in the current ScopeTable"`.

### 4.5 Print

```cpp
void Print(int depth, bool showAll);
```

Outputs the scope in the format:

```
ScopeTable# N
1--> <sym1_name,sym1_type> <sym1_name,sym1_type,sym1_extra>
2--> <sym2_name,sym2_type>
3-->
...
```

- Each bucket number is 1-indexed.
- Each symbol in a bucket is rendered as `<name,type>` or `<name,type,extraInfo>` (if extra is non-empty).
- The `depth` parameter controls indentation (tabs) for nested scope display.
- If `showAll` is true and a parent exists, recursively prints parent scopes with increased depth.

### 4.6 Constructor & Destructor

```cpp
ScopeTable(int buckets, int id, ScopeTable* parent = nullptr);
~ScopeTable();
```

- Allocates the hash table array: `table = new mylist<SymbolInfo>[buckets]`.
- Prints `"ScopeTable# N created"`.
- Destructor frees the array and prints `"'ScopeTable# N removed"`.

---

## 5. Class `SymbolTable`

Orchestrates the **scope chain** — a stack of `ScopeTable` objects linked via `parentScope` pointers.

### 5.1 Scope Lifecycle

```
Constructor: creates root ScopeTable with id=1
    ↓
S (EnterScope): pushes a new ScopeTable with next sequential id
    ↓
E (ExitScope):  pops the current ScopeTable, restores parent
    ↓
Destructor:    repeatedly pops until root is gone
```

**Constructor** (`SymbolTable`, line 165–167):

```cpp
SymbolTable(int bucketSize)
    : currentScope(nullptr), bucketSize(bucketSize), scopeCounter(0) {
    EnterScope();   // creates ScopeTable# 1
}
```

Scope IDs are **sequential integers**: 1, 2, 3, … (not hierarchical; that is a separate variant in `A1_online_solution.cpp`).

### 5.2 Delegating Methods

`Insert`, `Remove`, `PrintCurrent`, `PrintAll` all delegate to `currentScope`. E.g.:

```cpp
bool Insert(string name, string type, string extra = "") {
    if (!currentScope) return false;
    return currentScope->Insert(name, type, extra);
}
```

### 5.3 Cross-Scope Lookup

`SymbolTable::Lookup` (line 191–204) is the standard **scope-chain lookup**: it walks from `currentScope` up through parent scopes until it finds the name or reaches the root:

```cpp
SymbolInfo* Lookup(string name) {
    ScopeTable* sc = currentScope;
    int bucket = 0, pos = 0;
    while (sc) {
        SymbolInfo* found = sc->Lookup(name, bucket, pos);
        if (found) {
            out << "\t'" << name << "' found in ScopeTable# " << sc->getScopeId()
                << " at position " << bucket << ", " << pos << endl;
            return found;
        }
        sc = sc->getParentScope();
    }
    out << "\t'" << name << "' not found in any of the ScopeTables" << endl;
    return nullptr;
}
```

### 5.4 Root Scope Guard

```cpp
bool isRootScope() {
    return currentScope && !currentScope->getParentScope();
}
```

Used in `main` (line 364) to **silently skip** `E` (exit scope) when already at the root:

```cpp
if (line[0] == 'E' && st.isRootScope()) continue;
```

This prevents the root scope from being removed.

---

## 6. Command Processor — `processCommand`

```cpp
void processCommand(string line, SymbolTable& st);
```

Parses the command from the first token `cmd`, then dispatches:

### 6.1 `I` (Insert) — Special Forms

```
I name type [extra...]
```

Two special forms produce structured `extraInfo`:

**FUNCTION** (`I name FUNCTION retType param1 param2 ...`):

Packages as `retType<==(param1,param2,...)`. The first token after `FUNCTION` is the return type; the rest are comma-joined as parameters.

**STRUCT / UNION** (`I name STRUCT type1 name1 type2 name2 ...`):

Packages as `{(type1,name1),(type2,name2),...}`.

If neither special form applies, any remaining tokens are comma-joined into `extraInfo` verbatim.

**Validation**: If `I` is followed by fewer than 2 tokens (name + type), the command is rejected with `"Number of parameters mismatch for the command I"` (line 230–233).

### 6.2 `L` (Lookup)

```
L name
```

Calls `st.Lookup(name)` which walks the scope chain. Extra arguments produce `"Number of parameters mismatch for the command L"`.

### 6.3 `D` (Delete)

```
D name
```

Deletes from the **current scope only** (not ancestor scopes). Missing arguments produce `"Number of parameters mismatch for the command D"`.

### 6.4 `S` / `E` (Scope Enter / Exit)

```
S       → st.EnterScope()
E       → st.ExitScope()
```

No arguments expected.

### 6.5 `P` (Print)

```
P C     → print current scope only
P A     → print all scopes (current + ancestors)
```

Only `C` and `A` are valid sub-commands; anything else (e.g., `P X`) is silently ignored.

---

## 7. Main Function

### 7.1 Input Parsing

```cpp
string inputFile = (argc >= 2) ? argv[1] : "sample_input.txt";
string outputFile = (argc >= 3) ? argv[2] : "new_output.txt";
```

- Defaults to `sample_input.txt` / `new_output.txt` when no arguments given.
- **Line 1 of the input file** must be the hash table bucket count (integer).
- Bucket size ≤ 0 is handled by printing a diagnostic and defaulting to 1 (lines 347–350).

### 7.2 Command Dispatch Loop

```cpp
int cmdCount = 1;
while (getline(inFile, line)) {
    // trim trailing whitespace
    // Q → break
    // E on root scope → skip (silently)
    // command validation gate
    // output "Cmd N: <line>"
    // processCommand(line, st)
    // cmdCount++
}
```

- Empty lines are skipped (line 357).
- Trailing whitespace is stripped (line 358–359).
- Commands are **1-indexed**: the first command is `Cmd 1: ...`.

### 7.3 Command Validation Gate

Before dispatching, `main` validates the command token (lines 369–375):

| Command | Validation |
|---------|-----------|
| `P` | Sub-command must be `C` or `A` |
| `I`, `L`, `D`, `S`, `E` | Accepted |
| `Q` | Exits the loop (handled earlier) |
| Anything else | **Silently ignored** (line `continue`) |

This means unknown commands are swallowed without error — a deliberate design choice per the assignment spec.

---

## 8. Supporting File: `2205040_general.h`

Provides `mylist<T>`, a minimal singly-linked list template:

```cpp
template <typename T>
class mylist {
    struct Node { T data; Node* next; };
    Node* head;
public:
    class iterator { /* forward iterator */ };
    void push_back(const T&);
    template <typename Pred> Node* find_if(Pred);
    template <typename Pred> bool remove_if(Pred);  // removes first match
    template <typename Func> void for_each(Func);
    // Rule of Three: copy ctor, copy assignment (added as fix)
};
```

Key points:
- **No STL containers** — `mylist` is the only data structure.
- `remove_if` removes only the **first** matching element, then returns `true`.
- The **Rule of Three** (copy constructor, copy assignment operator) was added to prevent double-free if a `mylist` is ever copied. The code currently only uses `mylist` in heap-allocated arrays (`new mylist<SymbolInfo>[N]`), so copies don't arise in normal operation, but the fix protects against future misuse.

---

## 9. Summary of Output Format

| Event | Output |
|---|---|
| Scope created | `\tScopeTable# N created` |
| Scope removed | `\tScopeTable# N removed` |
| Insert success | `\tInserted in ScopeTable# N at position B, P` |
| Insert duplicate | `\t'X' already exists in the current ScopeTable` |
| Lookup found | `\t'X' found in ScopeTable# N at position B, P` |
| Lookup not found | `\t'X' not found in any of the ScopeTables` |
| Delete success | `\tDeleted 'X' from ScopeTable# N at position B, P` |
| Delete not found | `\tNot found in the current ScopeTable` |
| Param mismatch | `\tNumber of parameters mismatch for the command CMD` |
| Command header | `Cmd N: <full line>` |
| Print header | `\tScopeTable# N` then per-bucket `B--> <...>` |
| `Q` (quit) | `Cmd N: Q` |

All lines are prefixed with `\t` (tab). The output from multiple runs collects in the global `ostringstream` and is written to the output file at program end.
