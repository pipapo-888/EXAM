# 42 Exam Rank 03

This repository contains solutions for 42 School's Exam Rank 03, organized by difficulty levels.
このリポジトリには、難易度別に整理された42 School's Exam Rank 03の解答が含まれています。

## Structure

```
├── LEVEL-1/
│   ├── broken_gnl/     # Get Next Line implementation with fixes (修正済み「Get Next Line」の実装を取得する)
│   ├── filter/         # String filtering and replacement program (文字列フィルタリングおよび置換プログラム)
│   └── scanf/          # Custom scanf implementation (カスタムscanf実装)
└── LEVEL-2/
    ├── n_queens/       # N-Queens problem solver (Nクイーンズ問題ソルバー)
    ├── permutations/   # String permutation generator (文字列順列生成器)
    ├── powerset/       # Subset sum problem solver (部分和問題ソルバー)
    ├── rip/           # Parentheses balancing problem (括弧のバランス問題)
    └── tsp/           # Travelring Salesman Problem solve (巡回セールスマン問題の解決)
```

## Level 1 Exercises

### broken_gnl
Implementation of `get_next_line` function that reads a file line by line.
(ファイルを1行ずつ読み込む`get_next_line`関数の実装。)
- **Files**: `brocken_gnl.c`, `my_broken_gnl.c`
- **Key concepts**: File I/O, static variables, buffer management (ファイル入出力、静的変数、バッファ管理)

### filter
Program that reads from stdin and replaces occurrences of a given word with asterisks.
(標準入力から読み込み、指定された単語の出現箇所をアスタリスクで置換するプログラム。)
- **Files**: `filter.c`, `filter2.c`
- **Usage**: `echo "hello world" | ./filter hello` → `***** world`
- **Key concepts**: String manipulation, memory management, stdin processing (文字列操作、メモリ管理、標準入力処理)

### scanf
Custom implementation of `scanf` function supporting `%c`, `%d`, and `%s` format specifiers.
(`%c`、`%d`、`%s` 形式指定子をサポートする `scanf` 関数のカスタム実装。)
- **Files**: `scanf2.c`, `s.c`
- **Key concepts**: Variadic functions, format parsing, input validation (可変長引数関数、フォーマット解析、入力検証)

## Level 2 Exercises

### n_queens
Solves the N-Queens problem using backtracking algorithm.
(Solves the N-Queens problem using backtracking algorithm.)
- **Files**: `n_queens.c`, `my_n_queen.c`
- **Usage**: `./n_queens 4` outputs all valid queen placements on a 4x4 board
(4x4の盤面におけるすべての有効なクイーン配置を出力する)
- **Key concepts**: Backtracking, recursion, constraint satisfaction (バックトラッキング、再帰、制約充足)

### permutations
Generates all permutations of a given string in alphabetical order.
(指定された文字列の全順列をアルファベット順に生成します。)
- **Files**: `permutations.c`, `permutations2.c`
- **Usage**: `./permutations abc` → outputs all permutations of "abc"
- **Key concepts**: Recursion, backtracking, sorting algorithms (再帰、バックトラッキング、ソートアルゴリズム)

### powerset
Finds all subsets of a given set that sum to a target value.
(指定された集合の、合計が目標値となるすべての部分集合を見つける。)
- **Files**: `powerset.c`
- **Usage**: `./powerset 5 2 3` → outputs subsets that sum to 5 (合計が5になる部分集合を出力する)
- **Key concepts**: Subset generation, dynamic programming concepts (部分集合生成、動的計画法の概念)

### rip
Balances parentheses by removing the minimum number of characters.
(最小限の文字数を除去することで括弧をバランスよく整えます。)
- **Files**: `rip2.c`
- **Usage**: `./rip "(()"` → outputs all valid balanced strings (すべての有効な平衡文字列を出力する)
- **Key concepts**: String validation, backtracking, recursion (文字列検証、バックトラッキング、再帰)

### tsp
Solves the Traveling Salesman Problem using brute force with optimizations.
(最適化を施した力ずくの手法で巡回セールスマン問題を解く。)
- **Files**: `tsp.c`, `tsp_give.c`
- **Input format**: City coordinates as `x, y` pairs (都市座標を`x, y`のペアとして)
- **Key concepts**: Graph algorithms, optimization, geometric calculations (グラフアルゴリズム、最適化、幾何学的計算 )

## Compilation

Most programs can be compiled with:
```bash
gcc -Wall -Wextra -Werror *.c -o program_name
```

For TSP, add math library:
```bash
gcc -Wall -Wextra -Werror tsp.c -lm -o tsp
```

## Testing

Each exercise directory contains test files and expected outputs. The TSP directory includes multiple test cases with expected results.
(各演習ディレクトリにはテストファイルと期待される出力が含まれています。TSPディレクトリには複数のテストケースと期待される結果が含まれています。)

## Key Learning Objectives

- **Algorithm Design**: Backtracking, recursion, optimization (バックトラッキング、再帰、最適化)
- **Memory Management**: Dynamic allocation, proper cleanup (動的割り当て、適切なクリーンアップ)
- **String Processing**: Parsing, manipulation, validation (解析、操作、検証)
- **File I/O**: Reading from files and stdin (ファイルと標準入力からの読み込み)
- **Mathematical Concepts**: Combinatorics, graph theory, geometric calculations (組み合わせ論、グラフ理論、幾何学的計算)

## Notes

- All solutions follow 42 School's coding standards (Norminette) (すべてのソリューションは42 Schoolのコーディング基準（Norminette）に従います)
- Error handling and edge cases are properly managed (エラー処理とエッジケースは適切に管理されている)
- Memory leaks are avoided through proper cleanup (メモリリークは適切なクリーンアップによって回避される)
- Solutions are optimized for readability and efficiency (ソリューションは可読性と効率性を最適化しています)

---

*This repository represents exam-level programming challenges that test fundamental computer science concepts and C programming skills.*
このリポジトリは、コンピュータサイエンスの基礎概念とCプログラミングスキルをテストする試験レベルのプログラミング課題を提供します。*



        man_stdarg.txt \


        errno見直し
