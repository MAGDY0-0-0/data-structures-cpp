# Stack-based expression evaluator (C++)

One C++ program that uses `std::stack` for two classic algorithms:

1. **Infix to postfix** with the shunting-yard algorithm. It handles
   multi-digit numbers, `+ - * / ^` and parentheses, and treats `^` as
   right-associative.
2. **Postfix evaluation**, which computes the result from the postfix string.

`main()` runs three fixed test expressions and prints each result next to the
expected value:

| Infix | Postfix | Result |
|---|---|---|
| `3+4*5-2` | `3 4 5 * + 2 -` | 21 |
| `(300+20/5)*(43-21)` | `300 20 5 / + 43 21 - *` | 6688 |
| `2^3^2` | `2 3 2 ^ ^` | 512 |

## Running it

```bash
g++ -std=c++17 -o stack_expression stack_expression.cpp
./stack_expression
```

## Files

- `stack_expression.cpp`: the program.
- `project`: a more heavily commented version of the same program. It has no
  file extension.

## Limits

It uses integer arithmetic only, so `/` truncates. It has no unary minus and no
input validation, and the expressions are hard-coded rather than read from input.

---

_Imported to GitHub in August 2026 as a single commit._
