
# N_QUEENS 解法ガイド（Problem 3）
**対象課題**: `n_queens`  
**目的**: N×N 盤に N 個のクイーンを「互いに攻撃不可」になるよう配置し、**すべての解の個数**を求める。  
**想定読者**: 再帰・バックトラッキング・ビット演算の基礎〜応用を体系的に押さえたい人。

---

## 1. 仕様（要点）
- 実行形式: `./n_queens n`
- 入力: 正の整数 `n`
- 出力: **解の総数**（整数のみ）を標準出力へ
- エラー: 引数なし／整数でない／`n < 1`／メモリ失敗 等は **1 を返す**
- パフォーマンス: `n` が大きくなると探索空間は急増（指数）。**枝刈り**・**ビット最適化**が鍵。

---

## 2. 問題理解
- クイーンは「**行・列・斜線**」のいずれかが一致すると攻撃できる。
- よって **各行に 1 個** ずつ置く前提にすれば、**行の衝突は発生しない**。  
  残りは **列** と **斜線（↘, ↙）** の衝突のみをチェックすればよい。

---

## 3. アプローチ比較
### 3.1 配列＋衝突チェック（理解しやすい）
- `pos[row] = col` で行 `row` に置いた列 `col` を保持。
- `safe(row, col)` で列・斜線の衝突を **O(row)** で確認。

### 3.2 ビットマスク（高速・実戦向き）
- 使用中の **列**／**右下がり斜線（diag1）**／**左下がり斜線（diag2）** を **ビット** で管理。
- `cols`, `d1`, `d2` として、1 が使用中を表す。
- 行を 1 つ進めるごとにビットを更新して再帰。
- 斜線のインデックス：
  - 右下がり（↘）: `row - col` は負になるので `row - col + (n - 1)` にシフト
  - 左下がり（↙）: `row + col` は `0..2n-2` の範囲

---

## 4. 再帰フロー（バックトラッキング）
1. 行 `row = 0` から開始。
2. すべての列 `col` を試す。
3. 衝突がなければ配置 → 次の行へ。
4. `row == n` に達したら **解を 1 つカウント**。
5. 戻る際に状態を元に戻す（ビット/配列）。

---

## 5. スケルトン（配列版：読みやすさ重視）
```c
#include <stdio.h>
#include <stdlib.h>

static int safe(int *pos, int row, int col) {
    for (int r = 0; r < row; r++) {
        int c = pos[r];
        if (c == col) return 0;                  // 同列
        if (abs(c - col) == abs(r - row)) return 0; // 斜線
    }
    return 1;
}

static long backtrack(int *pos, int n, int row) {
    if (row == n) return 1;
    long sum = 0;
    for (int col = 0; col < n; col++) {
        if (safe(pos, row, col)) {
            pos[row] = col;
            sum += backtrack(pos, n, row + 1);
        }
    }
    return sum;
}

int main(int ac, char **av) {
    if (ac != 2) return 1;
    int n = atoi(av[1]);
    if (n < 1) return 1;

    int *pos = (int *)malloc(sizeof(int) * n);
    if (!pos) return 1;
    long ans = backtrack(pos, n, 0);
    printf("%ld\n", ans);
    free(pos);
    return 0;
}
```

---

## 6. スケルトン（ビットマスク版：高速）
> `n <= 32` 程度なら `uint32_t`、`n <= 64` なら `uint64_t` を利用可能。ここでは 64bit を例示。

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static long dfs(int n, int row, uint64_t cols, uint64_t d1, uint64_t d2) {
    if (row == n) return 1;

    long sum = 0;
    // 使用不可マスク: 1 の位置が置けない列
    uint64_t banned = cols | d1 | d2;
    // 置ける列位置（下位 n ビットのみ有効）
    uint64_t avail = (~banned) & ((1ULL << n) - 1);

    while (avail) {
        uint64_t bit = avail & -avail; // 最下位 1 ビットを取り出す
        avail -= bit;
        // 列/斜線の更新。bit の位置 = 列
        sum += dfs(n, row + 1,
                   cols | bit,
                   (d1 | bit) << 1,      // 次の行では ↘ が 1 列右にずれる
                   (d2 | bit) >> 1);     // 次の行では ↙ が 1 列左にずれる
    }
    return sum;
}

int main(int ac, char **av) {
    if (ac != 2) return 1;
    int n = atoi(av[1]);
    if (n < 1 || n > 32) return 1; // 64bit なら 32 でも十分大きい

    long ans = dfs(n, 0, 0, 0, 0);
    printf("%ld\n", ans);
    return 0;
}
```

**ポイント**
- `avail` は「この行で置ける列の集合」。
- `bit = avail & -avail` は **最下位 1 ビット抽出**（定番テク）。
- 斜線は行を進めると列方向に 1 ビットずれるので、`<< 1` / `>> 1`。

---

## 7. 枝刈り・高速化の工夫
- **対称性削減**（左右反転対称）。
  - 1 行目で「左半分のみ」を配置し、解を 2 倍（奇数 `n` は中央は 1 倍）。
- **ビット版 + 最下位ビット抽出**で高速に列挙。
- **早い段階での失敗判定**（`safe()` をできる限り安く）。
- **尾再帰最適化**（Cコンパイラにより期待できないこともあるので過信しない）。

---

## 8. 計算量・スケール感
- 理論上は指数関数オーダー（厳密解析は複雑）。
- 実用上、ビット最適化で `n=14〜15` 程度までは現実的に到達可能。

---

## 9. テスト計画
### 9.1 正常系
```bash
./n_queens 1   # → 1
./n_queens 4   # → 2
./n_queens 5   # → 10
./n_queens 8   # → 92
```

### 9.2 異常系
```bash
./n_queens            # 引数なし → 終了 1
./n_queens 0          # n<1 → 終了 1
./n_queens abc        # 非数値 → 終了 1（atoiの前に検証するなら要実装）
```

### 9.3 負荷系
```bash
time ./n_queens 12
time ./n_queens 14
```

---

## 10. 可視化（理解補助）
- `pos[row]=col` を横棒で出力する簡易可視化を入れると、再帰過程の理解が深まる。  
  例）`row:col` ログ、配置ごとの盤面出力など（提出要件に合わせて `#ifdef DEBUG` で制御）。

---

## 11. まとめ（攻略ポイント）
- **行を固定**し、**列と斜線の衝突**だけを見ればよい。
- まずは **配列版で正しさ**を固め、次に **ビット版で速度**を上げる二段構えが堅実。
- テストは **既知解（4→2, 8→92）** を基準に妥当性を検証。

