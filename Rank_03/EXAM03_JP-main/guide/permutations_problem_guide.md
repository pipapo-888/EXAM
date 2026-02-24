
# PERMUTATIONS 解法ガイド（Problem 4）
**対象課題**: `permutations`  
**目的**: 1..n の全順列を重複なく列挙し、所定フォーマットで標準出力へ出す。  
**想定読者**: 再帰・バックトラッキング・生成アルゴリズムの基礎を整理したい人。

---

## 1. 仕様（要点）
- 実行形式: `./permutations n`
- 入力: 正の整数 `n`
- 出力: 各順列を 1 行で空白区切り（例：`1 2 3`）
- エラー: 引数なし／非整数／`n<1`／メモリエラー → 終了 1

---

## 2. 問題理解
- **順列（Permutation）**: n 個の相異なる要素の並べ替え。総数は `n!`。  
- 列挙系アルゴリズムでは **「生成順の重複がないこと」** と **「戻し操作（バックトラック）」** が重要。

---

## 3. アプローチ比較
### 3.1 再帰スワップ法（定番・わかりやすい）
- 配列 `a[0..n-1]` の **位置 k を固定** し、`k..n-1` の要素を順に前へ持ってくる。
- 再帰から戻るときに **swap で元に戻す（バックトラック）**。

### 3.2 Heap’s Algorithm（効率よい全列挙）
- スワップ回数が少なく、実装がコンパクト。
- **偶数/奇数** でスワップ相手が変化する独特の規則で重複なく生成。

---

## 4. スケルトン（再帰スワップ法）
```c
#include <stdio.h>
#include <stdlib.h>

static void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }

static void print_perm(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        if (i) putchar(' ');
        printf("%d", arr[i]);
    }
    putchar('\n');
}

static void permute(int *arr, int k, int n) {
    if (k == n) { print_perm(arr, n); return; }
    for (int i = k; i < n; i++) {
        swap(&arr[k], &arr[i]);
        permute(arr, k + 1, n);
        swap(&arr[k], &arr[i]); // 戻す
    }
}

int main(int ac, char **av) {
    if (ac != 2) return 1;
    int n = atoi(av[1]);
    if (n < 1) return 1;

    int *a = (int*)malloc(sizeof(int)*n);
    if (!a) return 1;
    for (int i = 0; i < n; i++) a[i] = i + 1;

    permute(a, 0, n);
    free(a);
    return 0;
}
```

---

## 5. スケルトン（Heap’s Algorithm）
```c
#include <stdio.h>
#include <stdlib.h>

static void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }

static void print_perm(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        if (i) putchar(' ');
        printf("%d", arr[i]);
    }
    putchar('\n');
}

static void heap_permute(int *a, int n) {
    int c[n]; // 生成用カウンタ
    for (int i = 0; i < n; i++) c[i] = 0;
    print_perm(a, n);
    int i = 0;
    while (i < n) {
        if (c[i] < i) {
            if (i % 2 == 0) swap(&a[0], &a[i]);
            else swap(&a[c[i]], &a[i]);
            print_perm(a, n);
            c[i]++;
            i = 0;
        } else {
            c[i] = 0;
            i++;
        }
    }
}

int main(int ac, char **av) {
    if (ac != 2) return 1;
    int n = atoi(av[1]);
    if (n < 1) return 1;
    int *a = (int*)malloc(sizeof(int)*n);
    if (!a) return 1;
    for (int i = 0; i < n; i++) a[i] = i + 1;
    heap_permute(a, n);
    free(a);
    return 0;
}
```

---

## 6. 設計・実装の注意点
- **スタック深さ**: 再帰法は深さ `n`。`n` が大きすぎるケースは Heap 法や反復法を検討。
- **出力整形**: 末尾の空白や改行は **統一**（自動採点対策）。
- **性能**: 実行時間は `O(n!)`。`n=10` を超えると急速に重くなる。  
- **メモリ**: `O(n)`（配列＋再帰スタック）。

---

## 7. テスト計画
### 7.1 正常系
```bash
./permutations 1
# 1

./permutations 3 | sort
# 1 2 3
# 1 3 2
# 2 1 3
# 2 3 1
# 3 1 2
# 3 2 1
```

### 7.2 異常系
```bash
./permutations
./permutations 0
./permutations abc
```

### 7.3 負荷系
```bash
time ./permutations 9 > /dev/null
```

---

## 8. よくある落とし穴
- **バックトラックの戻し忘れ**（スワップ未復元で列挙が壊れる）。
- **出力フォーマットの不一致**（採点NGの典型）。
- **配列の初期化ミス**（1..n の生成漏れ）。

---

## 9. まとめ（攻略ポイント）
- まずは **再帰スワップ法** で正しさを確立。  
- パフォーマンスや `n` が大きい場合は **Heap’s Algorithm** でスワップ回数を削減。  
- 出力形式と境界条件のテストを徹底すること。

