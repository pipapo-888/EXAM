
# POWERSET 解法ガイド（Problem 5）
**対象課題**: `powerset`  
**目的**: 集合 `{1..n}` の **冪集合（全ての部分集合）** を漏れなく生成し、所定のフォーマットで出力する。  
**想定読者**: 組み合わせ列挙・ビット演算・再帰分岐をきれいに整理したい人。

---

## 1. 仕様（要点）
- 実行形式: `./powerset n`
- 入力: 整数 `n >= 0`
- 出力: 各部分集合を 1 行で表示（例: `{1, 3}`）。空集合は `{}`。
- エラー: 引数なし／非整数／負数／メモリエラー → 終了 1
- 性質: 部分集合の総数は **2^n**。出力量が指数的に増える。

---

## 2. 問題理解
- 冪集合は「各要素を **含める／含めない** の 2 択」で全通り（2^n）。
- 生成順は任意（辞書順などの規定がなければ OK）。採点用に **出力フォーマットの統一** が重要。

---

## 3. アプローチ比較
### 3.1 ビットマスク法（最短距離で実装可能）
- `mask` を 0..(2^n - 1) までループし、`j` ビットが 1 なら要素 `j+1` を採用。
- 計算量: `O(n * 2^n)`、空間 `O(1)`（出力用一時領域を除く）。

### 3.2 再帰分岐法（直感的・学習向け）
- インデックス `k` に対して「**入れる** → 再帰」「**入れない** → 再帰」を展開。
- 葉に到達したら 1 つの部分集合が完成。
- 計算量: `O(2^n)`、空間 `O(n)`（再帰スタック）。

---

## 4. スケルトン（ビットマスク法）
```c
#include <stdio.h>
#include <stdlib.h>

static void print_set_mask(int mask, int n) {
    putchar('{');
    int first = 1;
    for (int j = 0; j < n; j++) {
        if (mask & (1 << j)) {
            if (!first) printf(", ");
            printf("%d", j + 1);
            first = 0;
        }
    }
    printf("}\n");
}

int main(int ac, char **av) {
    if (ac != 2) return 1;
    int n = atoi(av[1]);
    if (n < 0) return 1;

    int total = 1 << n; // n が 31 以下を想定
    for (int mask = 0; mask < total; mask++) {
        print_set_mask(mask, n);
    }
    return 0;
}
```

> **注意**: `n >= 31` で `1<<n` が未定義挙動になるので、64bit を使う場合は `1ULL<<n` と範囲チェックを入れる。

---

## 5. スケルトン（再帰分岐法）
```c
#include <stdio.h>
#include <stdlib.h>

static void print_set(int *pick, int n) {
    putchar('{');
    int first = 1;
    for (int i = 0; i < n; i++) {
        if (pick[i]) {
            if (!first) printf(", ");
            printf("%d", i + 1);
            first = 0;
        }
    }
    printf("}\n");
}

static void dfs(int k, int n, int *pick) {
    if (k == n) { print_set(pick, n); return; }
    pick[k] = 0; dfs(k + 1, n, pick); // 含めない
    pick[k] = 1; dfs(k + 1, n, pick); // 含める
}

int main(int ac, char **av) {
    if (ac != 2) return 1;
    int n = atoi(av[1]);
    if (n < 0) return 1;

    int *pick = (int*)malloc(sizeof(int) * n);
    if (!pick && n > 0) return 1;
    dfs(0, n, pick ? pick : (int[]){0});
    free(pick);
    return 0;
}
```

---

## 6. 出力フォーマットのコツ
- **空集合**: 必ず `{}` を出す。
- **区切り**: 要素間は `", "`（カンマ + スペース）を使用。末尾にカンマを出さない。
- **整合性**: 自動採点に備え、不要な空白・改行は出力しない。

---

## 7. 計算量と限界
- 時間: `O(n * 2^n)`（ビット法）、`O(2^n)`（再帰の生成自体は同程度）。
- 空間: `O(1)` または `O(n)`。
- `n=20` で 1,048,576 行出力、`n=25` で 33,554,432 行。**実行時間・ファイルサイズに注意。**

---

## 8. テスト計画
### 8.1 正常系
```bash
./powerset 0
# {}

./powerset 3 | sort
# {}
# {1}
# {1, 2}
# {1, 2, 3}
# {1, 3}
# {2}
# {2, 3}
# {3}
```

### 8.2 異常系
```bash
./powerset
./powerset -1
./powerset abc
```

### 8.3 負荷系
```bash
time ./powerset 20 > /dev/null
```

---

## 9. よくある落とし穴
- `1<<n` のオーバーフロー（`n>=31` の時）。→ `1ULL<<n` と範囲制限。
- 出力フォーマットのブレ（スペース・カンマ・空集合の扱い）。
- `n=0` ケースの未対応。

---

## 10. まとめ（攻略ポイント）
- まずは **ビットマスク法** で最短距離に完成させる。  
- 学習・説明重視なら **再帰分岐法** で状態空間を可視化。  
- 出力仕様の一貫性と、大きな `n` に対する **現実的な性能見積り** を忘れないこと。

