# Assignment 3 — Progress Tracker

**Course:** CSE310 Compiler Sessional · **Student ID:** 2205040
**Deadline:** August 14, 2026

## Project location
`compiler/antlr/2205040/`

## Environment (installed)
| Item | Status |
|------|--------|
| Java (OpenJDK 17) | Done |
| ANTLR tool 4.13.2 (`/usr/local/bin/antlr4`) | Done |
| ANTLR C++ runtime (`/usr/local/include/antlr4-runtime`, `libantlr4-runtime`) | Done |
| cmake / g++ / git / wget | Present |

---

## Part 1 — Setup & Grammar (Lexical/Syntax foundation)
- [x] Copy skeleton into `2205040/` (grammar, lexer, main.cpp, run/clean scripts)
- [x] Grammar compiles cleanly with `antlr4` (no errors/warnings), generates C++ lexer/parser/visitor
- [x] Dangling-`else` ambiguity resolved (ANTLR binds `else` to nearest `if`, verified with nested case)
- [x] C++ build via `run-script.sh` works; runs on sample `.c` input
- [ ] ID-prefixed submission copies (`2205040_CSubset.g4`, `2205040_Lexer.g4`) — deferred to submission packaging

## Part 2 — Syntax Analysis (Parser + Logging + Symbol Table)
- [ ] Token-attribute logging (`$ID.text` / `ctx->getStart()->getLine()`)
- [ ] `variableDeclaration`: insert all declared IDs into symbol table (e.g. `int a,b,c;`)
- [ ] Print each matched rule + code segment to `log.txt` in order
- [ ] Print symbol table when a scope exits (before scope removal)
- [ ] Print symbol table after parsing finishes
- [ ] Syntax errors with line numbers → `error.txt`
- [ ] Print line count + error count at end of `log.txt`

## Part 3 — Semantic Analysis (Type checks & Functions)
- [ ] Extend `SymbolInfo` (return type, param list/count/types — possibly separate class)
- [ ] Type checking: assignment operand consistency, array index must be int, modulus operands int, function-call args match definition, no `void` function in expression
- [ ] Type conversion: warning on float→int assignment; `RELOP`/`LOGOP` results are int
- [ ] Uniqueness: declared-before-use, no duplicate declarations in same scope
- [ ] Array index vs array usage
- [ ] Function param count/types; definition-vs-declaration consistency; non-function used as call
- [ ] Error-handling grammar rules for sample erroneous inputs

## Final packaging
- [ ] Create `2205040/` zip (ID-prefixed grammar files only, no input/output/generated/exe)
