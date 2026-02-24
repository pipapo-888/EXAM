
# バックトラッキング徹底解説ガイド
**対象**: アルゴリズム/探索入門〜中級者、42系課題（N-Queens / Permutations / PowerSet / TSP など）  
**目的**: バックトラッキングの考え方・実装テンプレ・代表例×3・枝刈り（Pruning）・エッジケース/注意点を体系化

---

## 1. バックトラッキングとは
- **状態空間木（探索木）** を深さ優先で辿り、**不可能・無駄な枝を早期に打ち切る** 手法。  
- 「選択 → 実行 → 撤回（undo）」を繰り返して **全通り** または **制約を満たす解のみ** を列挙/探索する。
- 代表問題: **N-Queens**, **全順列**, **冪集合**, **部分和/Subset Sum**, **TSP**, **数独**, **迷路探索**。

### 向いている問題
- 制約充足（Constraint Satisfaction）
- 解の列挙（全解/一解）
- 枝刈りが効く構造（制約が強い、下界評価ができる）

---

## 2. 基本テンプレ（C）
最少コア：**選択 → 再帰 → 戻す**。副作用を必ず元に戻す。

```c
void dfs(State *s) {
    if (is_goal(*s)) {
        output(*s);
        return;
    }
    for (Choice c : choices(*s)) {
        if (!feasible(*s, c)) continue;   // 制約チェック（Pruning1）
        apply(s, c);                      // 「選択」
        if (!promising(*s)) {             // 下界/上界での枝刈り（Pruning2/Branch & Bound）
            undo(s, c);
            continue;
        }
        dfs(s);                           // 「再帰」
        undo(s, c);                       // 「撤回」 ← 忘れると壊れる！
    }
}
```

> **設計の鍵**: `feasible()`（局所制約）と `promising()`（グローバルな見通し、下界評価）を分離する。

---

## 3. 実装例①: N-Queens（制約充足 + 典型バックトラッキング）
### 問題
N×N 盤に N 個のクイーンを互いに攻撃不可で配置。**解の個数**を数える。

### 直感
- 行を1つずつ進め、各行で置ける列を選ぶ。
- 同列と斜線（↘/↙）を **ビット** で管理して高速化。

```c
#include <stdio.h>
#include <stdint.h>

static long dfs(int n, int row, uint64_t col, uint64_t d1, uint64_t d2) {
    if (row == n) return 1;
    long sum = 0;
    uint64_t banned = col | d1 | d2;
    uint64_t avail = (~banned) & ((1ULL << n) - 1);
    while (avail) {
        uint64_t bit = avail & -avail;   // 最下位の1
        avail -= bit;
        sum += dfs(n, row + 1,
                   col | bit,
                   (d1 | bit) << 1,      // ↘ は行+1で右へ1
                   (d2 | bit) >> 1);     // ↙ は行+1で左へ1
    }
    return sum;
}

int main(int ac, char **av){
    if (ac != 2) return 1;
    int n = atoi(av[1]);
    if (n < 1 || n > 32) return 1;
    printf("%ld\n", dfs(n, 0, 0, 0, 0));
    return 0;
}
```
**ポイント**
- `bit = avail & -avail` で 1 ビット選択（O(1) 分枝）。
- `feasible` をビットで O(1) 判定 → **強力な枝刈り**。

---

## 4. 実装例②: 全順列（生成問題 + 明快なundo）
### 問題
1..n の全ての並び替えを列挙。

### 直感
- 位置 `k` を確定 → 以降を再帰。
- スワップ後に **必ず元に戻す**（undo）。

```c
#include <stdio.h>
#include <stdlib.h>

static void swap(int *a, int *b){ int t=*a; *a=*b; *b=t; }

static void print_perm(int *a, int n){
    for (int i=0;i<n;i++){ if(i) putchar(' '); printf("%d", a[i]); }
    putchar('\n');
}

static void perm(int *a, int k, int n){
    if (k == n){ print_perm(a, n); return; }
    for (int i=k;i<n;i++){
        swap(&a[k], &a[i]);
        perm(a, k+1, n);
        swap(&a[k], &a[i]); // ← undo を忘れると崩壊
    }
}

int main(int ac, char **av){
    if (ac != 2) return 1;
    int n = atoi(av[1]);
    if (n < 1) return 1;
    int *a = malloc(sizeof(int)*n);
    for (int i=0;i<n;i++) a[i]=i+1;
    perm(a, 0, n);
    free(a);
    return 0;
}
```
**ポイント**
- **副作用（swap）を戻す**のがバックトラッキングの本質。  
- 重複要素がある場合は **used配列** or **同値スキップ**が必要（後述）。

---

## 5. 実装例③: TSP（最短路 + 枝刈り/Branch & Bound）
### 問題
距離行列が与えられた n 都市を一度ずつ訪れ、出発点へ戻る巡回路の最小コスト。

### 直感
- 深さ優先で次都市を選ぶ。
- **暫定最良値（best）を超えた時点で切る**（コストの上界）。

```c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static void dfs(int n, int dist[n][n], int curr, int visited, int depth, int cost, int *best){
    if (cost >= *best) return;                       // Pruning: 上界枝刈り
    if (depth == n){
        int round = dist[curr][0];
        if (round < INT_MAX && cost + round < *best) // 戻りコストを加える
            *best = cost + round;
        return;
    }
    for (int next=0; next<n; next++){
        if (!(visited & (1<<next)) && dist[curr][next] < INT_MAX){
            dfs(n, dist, next, visited | (1<<next), depth+1, cost + dist[curr][next], best);
        }
    }
}
```
**発展的枝刈り**
- 残都市の **下界見積**（各行の最小辺の和など）を `cost + lower_bound >= best` で枝刈り。
- 次に試す都市順をヒューリスティックに並べ替える（最近挿入など）。

---

## 6. エッジケース & 注意点
1) **副作用の戻し忘れ**  
- 典型例: perm の `swap` 戻し忘れ。N-Queensでのフラグ解除忘れ。  
→ *撤回（undo）の実装は必ず左右対称に*。

2) **重複要素**（順列/組合せ）  
- 入力に重複があると **同一解が複数回** 出力される。  
→ `used[]` と **同値スキップ**：  
  - 例）ソートして「同値は先に未使用の同値を使った時だけ許可」。

```c
// 重複あり配列の順列（同一解除去）
qsort(a, n, sizeof(int), cmp);
void perm_dup(int *a, int k, int n, int *used){
    if (k == n){ print(a); return; }
    for (int i=0;i<n;i++){
        if (used[i]) continue;
        if (i>0 && a[i]==a[i-1] && !used[i-1]) continue; // 同値スキップ
        used[i]=1; pick[k]=a[i];
        perm_dup(a, k+1, n, used);
        used[i]=0;
    }
}
```

3) **再帰の深さ/スタック**  
- `n=15+` などで深くなる。  
→ 専用スタック/反復実装 or ビットDP/別手法を検討。

4) **整数オーバーフロー**  
- TSP の総距離、組合せ数などが 32bit を超える。  
→ `long long`、`size_t` 使用、`INT_MAX` 番兵と加算順に注意。

5) **ビット演算の落とし穴**  
- `1<<n` は `n>=31` で未定義（32bit）。  
→ `1ULL<<n` と上限チェック。

6) **順序/出力フォーマット**  
- 採点スクリプトは空白・改行に厳しい。  
→ 出力ルールを固定し、テストを自動化。

7) **停止条件の誤り**  
- 例）TSPで「全都市訪問」を満たしても **戻りコスト** を足し忘れる。

8) **Pruning の正当性**  
- **下界評価**が「常に実コスト以上」でなければ解を落とす危険。  
→ 証明できない枝刈りは導入しない。

9) **探索順の影響**  
- 先に良い解に到達できる順で分枝すると **上界がすぐ縮まり** 枝刈りが効きやすい。

10) **メモリリーク/状態破壊**  
- `malloc`/`free` の対応漏れ、共有配列を誤って上書き。  
→ 局所コピー vs 共有のトレードオフに注意。

---

## 7. デバッグ戦略
- **小さな入力**で木の形を可視化（深さ/選択/戻りをログ）。
- 既知の答え（N-Queens: n=4→2, n=8→92）で検証。
- `#ifdef DEBUG` でログを簡単に有効化/無効化。
- Valgrind/ASan でメモリ不具合を早期発見。

---

## 8. いつバックトラッキングを捨てるか？
- オーバーラップする部分問題が多く、**最適解の1値のみ**が必要なら **動的計画法（DP）** が有効。
- TSP は小規模なら BT、**中規模なら Held–Karp（DP）**、大規模は近似・メタヒューリスティクス。

---

## 9. まとめ
- バックトラッキング = **「制約チェック + 撤回」** のループ。  
- **Pruning** を強化できる設計（下界/上界、強い局所制約、探索順最適化）がカギ。  
- 3例（N-Queens / Permutations / TSP）で基本〜応用を自走できるはず。

