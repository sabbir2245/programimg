# SymbolTableSpec

Course project: C++ symbol table for a compiler course, plus assembly exercises.

## Directories

- **`symboltable/`** — Main project (see `symboltable/AGENTS.md` for full details)
  - `2205040_symbol_table.cpp` — Core assignment (single-file, no STL)
  - `A1_online_solution.cpp`, `B1_online_solution.cpp`, `C1_online_solution.cpp` — Extended solutions
  - `2205040_general.h` — Custom `mylist<T>` linked list (shared by all files)
  - `2205040_build.sh` — Convenience compile + run script
  - `explanation.md` — Detailed architecture walkthrough
  - `changes.md` — Planned refactoring (lambda removal, constructor style, unused function cleanup)
  - `test.md` — Practice problems with exact input/output specs
  - `newcode.cpp` — Code snippet collection from all three solutions
- **`assembly/`** — Separate MIPS/assembly programs (unrelated to symbol table)
