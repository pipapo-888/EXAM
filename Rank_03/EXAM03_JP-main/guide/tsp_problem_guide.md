
# TSP 解法ガイド（Problem 7）
**対象課題**: `tsp`  
**目的**: 距離行列が与えられた都市群を **一度ずつ訪問して出発点へ戻る** 最短巡回路（Hamiltonian cycle）を求める。  
**キーワード**: brute force, backtracking, 枝刈り, Held–Karp（ビットDP）, 近似法。

---

## 1. 仕様（要点）
- 実行形式（例）: `./tsp n < matrix.txt`
  - `n`: 都市数（2 以上）
  - `matrix.txt`: `n x n` の非負整数距離行列（対称・非対称いずれも可）。対角は 0。
- 出力: **最短距離**（整数1行）。（経路自体の出力は任意）
- エラー: 引数不足／`n < 2`／行列不正／メモリエラー → 終了 1
- 時間計算量は原則として **指数**。正しさ重視なら全探索 or 枝刈り併用、速度重視なら **Held–Karp**。

---

## 2. アプローチ比較
| 手法 | 計算量 | 空間 | 特徴 |
|------|--------|------|------|
| Brute force（全順列） | `O(n!)` | `O(n)` | 実装が最短・確実に最適解。`n<=10` 程度向け |
| Backtracking + 枝刈り | `O(α·n!)` | `O(n)` | 部分和が暫定最良値を超えたら打ち切り。かなり効く |
| Held–Karp（ビットDP） | `O(n^2·2^n)` | `O(n·2^n)` | 最適解を厳密に出す高速DP。`n<=22` 前後が実用目安 |
| 近似（貪欲, 最近挿入, 2-OPT） | 多項式 | 低 | 近似・ヒューリスティクス。最適性は保証しない |

---

## 3. データ構造と入力
- 距離行列 `dist[n][n]`（`int` 推奨。溢れに注意）
- 訪問状態は：
  - **Backtracking**: `used[n]` の bool 配列
  - **Held–Karp**: `mask`（訪問集合） + `last`（終端都市）

### 入力バリデーション
- 行数・列数が `n` と一致するか
- 非負整数か（負は原則扱わない）
- `dist[i][i] == 0`
- 非対称を許すかは仕様に合わせる（ここでは可とする）

---

## 4. Brute force（全順列）スケルトン
- 都市 0 を出発点に固定（対象を `(n-1)!` 通りに削減）
```c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static void swap(int *a, int *b){ int t=*a; *a=*b; *b=t; }

static int route_cost(int *p, int n, int dist[n][n]){
    int sum = 0;
    for (int i=0;i<n-1;i++){
        int d = dist[p[i]][p[i+1]];
        if (d == INT_MAX) return INT_MAX; // 到達不能
        sum += d;
    }
    if (dist[p[n-1]][p[0]] == INT_MAX) return INT_MAX;
    sum += dist[p[n-1]][p[0]]; // 戻る
    return sum;
}

static void perm(int *p, int l, int r, int n, int dist[n][n], int *best){
    if (l == r){
        int c = route_cost(p, n, dist);
        if (c < *best) *best = c;
        return;
    }
    for (int i=l;i<=r;i++){
        swap(&p[l], &p[i]);
        perm(p, l+1, r, n, dist, best);
        swap(&p[l], &p[i]);
    }
}

int main(int ac, char **av){
    if (ac!=2) return 1;
    int n = atoi(av[1]);
    if (n<2) return 1;
    int dist[n][n];
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            if (scanf("%d", &dist[i][j])!=1) return 1;

    int p[n];
    for (int i=0;i<n;i++) p[i]=i;
    int best = INT_MAX;
    perm(p, 1, n-1, n, dist, &best); // 先頭0固定
    if (best==INT_MAX) return 1;
    printf("%d\n", best);
    return 0;
}
```
> 注意: `INT_MAX` を **到達不能の番兵** として扱う例。入力で未接続は `INT_MAX` 相当で埋めるか、読み込み時にガードを入れる。

---

## 5. Backtracking + 枝刈り スケルトン
- **部分和が暫定最良値を超えたら打ち切る**（最重要）。
```c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static void dfs(int n, int dist[n][n], int curr, int visited, int depth, int cost, int *best){
    if (cost >= *best) return; // 枝刈り
    if (depth == n){
        if (dist[curr][0] != INT_MAX){
            int total = cost + dist[curr][0];
            if (total < *best) *best = total;
        }
        return;
    }
    for (int next=0; next<n; next++){
        if (!(visited & (1<<next)) && dist[curr][next] != INT_MAX){
            dfs(n, dist, next, visited | (1<<next), depth+1, cost+dist[curr][next], best);
        }
    }
}

int main(int ac, char **av){
    if (ac!=2) return 1;
    int n = atoi(av[1]);
    if (n<2 || n>31) return 1; // bitmask制約
    int dist[n][n];
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            if (scanf("%d", &dist[i][j])!=1) return 1;
    int best = INT_MAX;
    dfs(n, dist, 0, 1<<0, 1, 0, &best);
    if (best==INT_MAX) return 1;
    printf("%d\n", best);
    return 0;
}
```
**改善案**: 最小辺の下界推定（1-tree 近似や各行最小2本の和など）を加えると枝刈りがさらに効く。

---

## 6. Held–Karp（ビットDP）スケルトン
- 状態 `dp[mask][i] = {0..n-1 の集合 mask を訪問し i で終わる最短距離}`
- 遷移 `dp[mask][i] = min_j dp[mask\{i}][j] + dist[j][i]`
- 答え `min_i dp[(1<<n)-1][i] + dist[i][0]`
```c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int min(int a,int b){ return a<b?a:b; }

int main(int ac, char **av){
    if (ac!=2) return 1;
    int n = atoi(av[1]);
    if (n<2 || n>22) return 1; // 2^22 * 22 * 22 は現実的上限の目安

    int dist[n][n];
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            if (scanf("%d", &dist[i][j])!=1) return 1;

    int N = 1<<n;
    int **dp = (int**)malloc(sizeof(int*)*N);
    if (!dp) return 1;
    for (int m=0;m<N;m++){
        dp[m]=(int*)malloc(sizeof(int)*n);
        if (!dp[m]) return 1;
        for (int i=0;i<n;i++) dp[m][i]=INT_MAX;
    }
    dp[1<<0][0] = 0; // 出発は0

    for (int mask=0; mask<N; mask++){
        for (int i=0;i<n;i++){
            if (!(mask&(1<<i)) || dp[mask][i]==INT_MAX) continue;
            for (int j=0;j<n;j++){
                if (mask&(1<<j)) continue; // 未訪問に遷移
                if (dist[i][j]==INT_MAX) continue;
                int nmask = mask | (1<<j);
                int cand = dp[mask][i] + dist[i][j];
                if (cand < dp[nmask][j]) dp[nmask][j]=cand;
            }
        }
    }

    int ans = INT_MAX;
    int full = N-1;
    for (int i=1;i<n;i++){
        if (dp[full][i]==INT_MAX || dist[i][0]==INT_MAX) continue;
        ans = min(ans, dp[full][i] + dist[i][0]);
    }
    if (ans==INT_MAX) return 1;
    printf("%d\n", ans);

    for (int m=0;m<N;m++) free(dp[m]);
    free(dp);
    return 0;
}
```
> メモリは約 `n * 2^n * 4 bytes`。`n=22` で ~92MB 程度。ヒープ確保の失敗に注意。

---

## 7. テスト計画
### 7.1 既知インスタンス
```
4
0 10 15 20
10 0 35 25
15 35 0 30
20 25 30 0
```
- 期待最短距離: **80**
```bash
./tsp 4 < matrix.txt
```

### 7.2 非対称行列
- `dist[i][j] != dist[j][i]` のケースでも正しいことを確認。

### 7.3 到達不能エッジ
- `INT_MAX` 相当で未接続を表現し、到達不能の扱いを確認。

### 7.4 スケール
- `n=10`（brute/backtracking）
- `n=20`（Held–Karp の速度/メモリ確認）

---

## 8. よくある落とし穴
- **戻りコストの足し忘れ**（最後に `dist[last][0]` を加える）。
- **bitmask の範囲外アクセス**（`n>31` で `1<<n` が UB）。
- **INT オーバーフロー**（コスト合計が32bit域超えうる）。`long long` で受けるのも手。
- **距離 0 の扱い**（自己ループ以外に 0 があると特殊ケースになる）。
- **入力の読み取り不整合**（行数/列数不一致）。

---

## 9. 速度アップのヒント
- **Backtracking**:
  - 都市の並び替えヒューリスティクス（最近挿入順に試す等）。
  - **下界推定**：残り都市の最小エッジ合計を足した下界で枝刈り。
- **Held–Karp**:
  - ロール配列（`dp_prev`, `dp_cur`）でメモリ半減。
  - 経路を復元しないなら遷移表を持たない。
  - 出発点固定（0）で状態を削減。

---

## 10. まとめ（攻略ポイント）
- `n<=10`: **Backtracking + 枝刈り**が楽で速い。  
- `10<n<=22`: **Held–Karp** が有力（実務でも定番）。  
- 常に **戻りコスト**を忘れず、入力検証・番兵値・ビット操作の境界を丁寧に扱えば堅牢に動く。

