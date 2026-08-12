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
- [x] ID-prefixed grammars named `id2205040_CSubset.g4` / `id2205040_Lexer.g4` (letter-prefix so they compile with ANTLR)

## Part 2 — Syntax Analysis (Parser + Logging + Symbol Table)
- [x] Token-attribute logging (`$ID.text` / `ctx->getStart()->getLine()`)
- [x] `variableDeclaration`: insert all declared IDs into symbol table (e.g. `int a,b,c;`)
- [x] Print each matched rule + code segment to `log.txt` in order
- [x] Print symbol table when a scope exits (before scope removal)
- [x] Print symbol table after parsing finishes
- [x] Syntax errors with line numbers → `error.txt`
- [x] Print line count + error count at end of `log.txt`

> Implementation: Visitor pattern (`SymbolTableVisitor.h/.cpp`) — no grammar actions. Files: `SymbolInfo.h`, `SymbolTable.h`, `main.cpp` (custom `BaseErrorListener`). Note: ANTLR generates an abstract `CSubsetVisitor.h/.cpp`; `clean_updated.sh` removes runtime output + generated ANTLR files (`CSubsetLexer/Parser/BaseVisitor/Visitor`, `.tokens/.interp`), keeping hand-written sources.

## Part 3 — Semantic Analysis (Type checks & Functions)
- [x] Extend `SymbolInfo` (return type, param list/count/types — possibly separate class)
- [x] Type checking: assignment operand consistency, array index must be int, modulus operands int, function-call args match definition, no `void` function in expression
- [x] Type conversion: warning on float→int assignment; `RELOP`/`LOGOP` results are int
- [x] Uniqueness: declared-before-use, no duplicate declarations in same scope
- [x] Array index vs array usage
- [x] Function param count/types; definition-vs-declaration consistency; non-function used as call
- [x] Error-handling grammar rules for sample erroneous inputs

## Final packaging
- [ ] Create `2205040/` zip (ID-prefixed grammar files only, no input/output/generated/exe)
