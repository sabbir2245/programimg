# SymbolTableVisitor.cpp — Explanation

## File Location

`@2205040dev/SymbolTableVisitor.cpp`

## What It Does

This file is a concrete implementation of the ANTLR-generated visitor base class
(`id2205040_CSubsetBaseVisitor`). It walks the parse tree produced by the parser and,
during that walk, **builds a symbol table** and **performs semantic analysis**
(type checking, scope handling, etc.). It validates that declarations, types, and
scopes in the program are correct, and reports any problems it finds to a log file
and an error file.

## Core Data Structures

- **Scope stack `scopes`**: a `vector<SymbolTable>`. Each block/compound statement
  pushes a new `SymbolTable` (symbol table) onto the stack and pops it when leaving.
  Index 0 is the global scope.
- **`SymbolTable`**: internally holds a `vector<SymbolInfo>`.
- **`SymbolInfo`**: describes a single symbol (variable/function/array), storing its
  name, type, whether it is an array, array size, whether it is a function, the
  number/type of its parameters, and whether it has been defined.
- **Helper functions**:
  - `trim`: strips leading/trailing whitespace from a string.
  - `A` / `T` / `AV` / `TV`: convert between `std::any` and `string` /
    `vector<string>`. They are used to pass return values (usually type
    information) between visitor methods.

## Main Responsibilities

### Symbol Lookup
- `findSymbol(name)`: searches for a symbol from the innermost scope out to the
  global scope.
- `findGlobal(name)`: searches only in the global scope (index 0).

### Function Declaration & Definition (`visitFunc_declaration` / `visitFunc_definition`)
- Extracts the return type, function name, and parameter list.
- Checks for conflicts with existing global symbols, return-type mismatches,
  mismatched parameter count/types, and duplicate definitions, reporting semantic
  errors as needed.
- Inserts the function into the global scope; on definition it stores the parameters
  in `pendingParams` so they can be added to the function body's scope.

### Parameter List (`makeParamList` / `visitParameter_list`)
- Collects all tokens in the parameter list, sorts them by position, and separates
  types (int/float/void) from names (ID), producing a `vector<SymbolInfo>`.

### Compound Statement (`visitCompound_statement`)
- Pushes a new scope and inserts the `pendingParams` (function parameters) into it.
- After visiting its children it prints the symbol table and pops the scope.

### Variable Declaration (`visitVar_declaration`)
- Parses the declaration list (possibly multiple variables separated by commas),
  detecting arrays and their sizes.
- Inserts symbols into the current scope; if a name already exists it reports a
  "multiple declaration in the same scope" error.

### Variable Reference (`visitVariable`)
- Looks up the symbol; reports an error if it is undeclared.
- If a subscript `[ ]` is used, checks that the variable is an array and that the
  index expression is an integer.

### Expression Type Checking
It walks down the grammar layers, inferring the type of each expression:
- `visitExpression`: handles assignment; checks that the left and right operand types
  are compatible (e.g., assigning float to int produces a warning).
- `visitLogic_expression` / `visitRel_expression`: logical and relational operations
  return `int`.
- `visitSimple_expression` / `visitTerm`: rules for `+ - * / %` typing (e.g., the
  modulus operator requires both operands to be integers).
- `visitUnary_expression` / `visitFactor`: handles negation, unary plus/minus,
  constants, parenthesized expressions, and function calls.

### Function Call (the ID branch of `visitFactor`)
- Checks that the function is declared, is actually a function, has a matching
  argument count and argument types, and that a `void` function is not used inside
  an expression.

### Argument List (`visitArgument_list` / `visitArguments`)
- Collects and returns the list of argument types (`vector<string>`) used for type
  checking at call sites.

## Error and Log Output
- `semError(line, msg)`: reports a semantic error and increments the global error
  counter `errorCount`.
- `semWarning(line, msg)`: reports a warning (e.g., possible precision loss when
  assigning float to int).
- `logRule(rule, code)`: writes the current grammar rule and its source text to the
  log file `logFile`, useful for debugging and tracing.
- `printSymbolTable()`: prints the symbol tables of all current scopes to the log file.
- Errors go to a global `errorFile`, introduced via `extern` and defined externally
  (in the main program).

## Overall Flow

1. The main program calls the visitor's `visit()` to traverse the entire parse tree.
2. Starting from the root, each node is visited in turn; declarations, definitions,
   and statements trigger symbol-table insertion and type checking.
3. All semantic errors/warnings are recorded to the error file, and symbol tables and
   rule visits are recorded to the log file.
4. Finally, the printed symbol table shows the program's scope structure.
