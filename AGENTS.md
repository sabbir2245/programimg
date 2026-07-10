# SymbolTableSpec

C++ symbol table implementation for a compiler course (single-file assignment).

## Build & Test

```bash
# Compile
g++ -std=c++11 -Wall -Wextra 2205040_symbol_table.cpp -o symbol_table

# Run (args: input_file output_file; defaults: sample_input.txt new_output.txt)
./symbol_table sample_input.txt new_output.txt

# Verify
diff -w sample_output.txt new_output.txt
```

## Key Facts

- **No STL containers** — uses custom `mylist<T>` linked list template (`2205040_general.h`)
- **Global output** — all diagnostics collect into global `ostringstream out`, flushed to output file at end
- **First line of input** is the hash table bucket count (integer, e.g. `7`)
- **Root scope protection** — `E` (exit scope) silently skips if `isRootScope()` is true (`2205040_symbol_table.cpp:354`)
- **Command parser** accepts only `I`, `L`, `D`, `S`, `E`, `P Q`; `P` only with `C` or `A`; invalid lines are silently ignored (`:359-365`)
- **`I` special forms**: `I name FUNCTION retType params...` stores extra info as `retType<==(param,...)`; `I name STRUCT/UNION type name...` stores as `{(type,name),...}` (`:233-261`)

## Online Solutions

Three separate solution files implement additional features on top of `2205040_general.h`:

| File | Features | Compile |
|------|----------|---------|
| `A1_online_solution.cpp` | Hierarchical scope IDs (`1`, `1.1`, `1.2.1`…), `M` merge command | `g++ -std=c++11 -fsanitize=address A1_online_solution.cpp -o A1_sol` |
| `B1_online_solution.cpp` | "Mickey Lang" interpreter (`{`, `}`, `declare`, `set`, `+`, `print`) | `g++ -std=c++11 -fsanitize=address B1_online_solution.cpp -o B1_sol` |
| `C1_online_solution.cpp` | `DT <type>` delete-by-type across all scopes, `IS <name> <type>` scope-local symbols | `g++ -std=c++11 -fsanitize=address C1_online_solution.cpp -o C1_sol` |

B1 reads token-by-token (boilerplate style) — first token is bucket size, then each opcode starts a command. All three require `-fsanitize=address` per spec.
