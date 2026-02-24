
# FILTER 解法ガイド（Problem 1）
**対象課題**: `filter`  
**目的**: 標準入力の文字列中に現れる **検索文字列 `s`** を、同じ長さの `*` に **すべて置換** して標準出力へ出す。  
**想定読者**: 42/低レイヤ学習者、C初中級、I/O・メモリ・エラー処理を体系的に学びたい人。

---

## 1. 仕様（原文の要点を日本語で整理）
- 実行形式: `./filter s`
- 入力: 標準入力（任意長テキスト）
- 出力: 標準出力（`s` の **全出現** を `'*'` × `strlen(s)` に置換したテキスト）
- エラー出力: `read()` / `malloc()` 系の失敗時に **`stderr` へ** `Error: <システムメッセージ>` を表示（`perror()` 使用）
- 終了コード:
  - 正常時: `0`
  - エラー時: `1`
- 引数が **0 個 / 空文字 / 2 個以上** の場合は **エラー終了**（1を返す）

**Allowed functions**（課題指定）:  
`read, strlen, malloc, calloc, realloc, free, printf, perror`  
※ `write` や `strncmp` は **使わない**。`read()` のみで入力し、出力は `printf()`。比較は自前実装で行う。

---

## 2. 設計指針
### 2.1 入力の取り扱い
- 入力は **任意長** で来る可能性が高い。`read()` で **チャンク読み**し、**動的バッファ**に貯める。
- 42的には **単純で安全** かつ **わかりやすい** 実装が望ましい。
  - 初学者向け: **全入力を一度にバッファへ読み切る方式**（シンプル）
  - 発展: **ストリーミング置換**（KMP など）だが今回は **要件外**。

### 2.2 置換アルゴリズム（要件適合 & シンプル最優先）
- 検索対象: 平文の **バイト列**（UTF-8 のコードポイント単位ではなく **バイト単位**）。
- 基本方針（Naive 全探索）:
  1. `needle = s`、`haystack = 入力全体`。
  2. `i = 0..len(haystack)-len(needle)` を走査し、**前方一致**したら `len(needle)` 文字を `'*'` に置換、`i` を `+ len(needle)` 進める（**非重複**置換）。
  3. 一致しなければ `i++`。
- **重なりの扱い**: 仕様に明確な記載がないが、一般的な `sed 's/pat/rep/g'` と同様、**左から最長非重複**で良い。  
  例）`aaaa` から `aa` を `**` に → `****`。

### 2.3 エラー処理・終了方針
- **引数検証**: `ac != 2` or `av[1]==""` → `return 1`。
- **I/O**: `read()` が `-1` → `perror("Error")` → `return 1`。
- **メモリ**: `malloc/calloc/realloc` が `NULL` → `perror("Error")` → `return 1`。  
  ※ `perror` は直近の `errno` を用いる。失敗時は直後に呼ぶ。

### 2.4 時間・空間計算量
- Naive 探索: `O(N * M)`（`N=入力長`, `M=|s|`）。
- 追加メモリ: `O(N)`（入力全体の保持）。

---

## 3. 実装ステップ（ロードマップ）
1. **引数検証**: `ac == 2` か、`av[1]` が空でないか。
2. **入力読込**: `read()` を使って `/dev/stdin`（fd=0）からチャンク読み → **可変長バッファ**に格納。
3. **置換処理**: Naive 前方一致で `'*'` に差し替え。
4. **出力**: `printf("%s", buf);`
5. **後始末**: `free(buf);` → `return 0;`

---

## 4. 参考スケルトン（Allowed関数のみ使用）
> **注意**: そのまま提出するのではなく、あなたのコーディングスタイル／Norminetteに合わせて整理してください。

```c
#include <unistd.h>   // read
#include <stdlib.h>   // malloc, realloc, free
#include <string.h>   // strlen
#include <stdio.h>    // printf, perror

#define CHUNK 4096

static int starts_with(const char *h, const char *n) {
    size_t j = 0;
    while (n[j]) {
        if (h[j] == '\0' || h[j] != n[j]) return 0;
        j++;
    }
    return 1;
}

int main(int ac, char **av) {
    if (ac != 2 || av[1] == NULL || av[1][0] == '\0')
        return 1;

    const char *needle = av[1];
    size_t nlen = strlen(needle);
    if (nlen == 0) return 1;

    // 1) read() で全入力を読み込む（可変長バッファ）
    size_t cap = CHUNK, len = 0;
    char *buf = (char *)malloc(cap);
    if (!buf) { perror("Error"); return 1; }

    for (;;) {
        ssize_t r = read(0, buf + len, cap - len);
        if (r < 0) { perror("Error"); free(buf); return 1; }
        if (r == 0) break; // EOF
        len += (size_t)r;
        if (cap - len == 0) {
            size_t ncap = cap + CHUNK;
            char *nbuf = (char *)realloc(buf, ncap);
            if (!nbuf) { perror("Error"); free(buf); return 1; }
            buf = nbuf; cap = ncap;
        }
    }

    // ヌル終端（printf用）。1バイト余分に確保する。
    char *nbuf = (char *)realloc(buf, len + 1);
    if (!nbuf) { perror("Error"); free(buf); return 1; }
    buf = nbuf; buf[len] = '\0';

    // 2) 置換（左から非重複で '*' に差し替え）
    if (nlen <= len) {
        size_t i = 0;
        while (i + nlen <= len) {
            if (starts_with(buf + i, needle)) {
                for (size_t k = 0; k < nlen; k++) buf[i + k] = '*';
                i += nlen; // 非重複で進む
            } else {
                i++;
            }
        }
    }

    // 3) 出力
    printf("%s", buf);
    free(buf);
    return 0;
}
```

---

## 5. テスト計画（手動 & 自動）
### 5.1 手動テスト
```bash
# 1) 基本
echo 'abcdefgaaaabcdefabc' | ./filter abc | cat -e
# 期待: ***defgaaa***def***$

# 2) 先頭・末尾マッチ
echo 'abcXYZ' | ./filter abc
echo 'XYZabc' | ./filter abc

# 3) 連続・重なり
echo 'aaaa' | ./filter aa   # 期待: ****

# 4) 改行・空行・バイナリ近いデータ
printf 'line1\n\nline3\n' | ./filter line
printf '\x00abc' | ./filter abc | hexdump -C

# 5) 大きな入力（10MB）
head -c 10485760 /dev/zero | tr '\0' 'a' | ./filter a > /dev/null
```

### 5.2 失敗系
```bash
./filter                 # 引数なし → 終了 1
./filter ""              # 空文字 → 終了 1
./filter a b             # 多引数 → 終了 1
```

### 5.3 Valgrind/アサーション
```bash
valgrind --leak-check=full --show-leak-kinds=all ./filter abc < big.txt > /dev/null
```

---

## 6. よくある落とし穴
- **Allowed外の関数**を使う（`write`, `strncmp`, `memmem` など）。→ 不可。
- `read()` の戻り値未チェック。→ `-1` はエラー、`0` は EOF。
- `realloc()` 失敗時に **元ポインタを失う**。→ 失敗時は古いポインタが有効、必ず一時変数で受ける。
- `printf("%s", buf)` のための **ヌル終端を付け忘れる**。
- 重なりマッチの仕様を誤る。→ 左から非重複（sed相当）ならOK。
- 超大入力での性能懸念。→ 課題範囲では許容。

---

## 7. 発展: ストリーミング置換（読み切らない方式）
- KMP/Rabin-Karp などで **前方一致状態**を持ちながら、`read()` しつつ **即時出力** できる。
- メリット: メモリ定数・巨大入力に強い。  
- デメリット: 実装が複雑に。今回は **要件外** なので採用不要。

---

## 8. ビルド & 実行例
```bash
cc -Wall -Wextra -Werror filter.c -o filter
echo 'abcdefgaaaabcdefabc' | ./filter abc | cat -e
# → ***defgaaa***def***$
```

---

## 9. まとめ（攻略ポイント）
- **I/O**: `read()` を確実に使いこなす（戻り値/EOF/エラー）。
- **メモリ**: `realloc()` の正しい使い方・ヌル終端の意識。
- **探索**: まずは **Naive + 非重複置換** で十分に合格水準。
- **検証**: 失敗系・大容量・境界条件を押さえたテストで堅牢性を担保。

---

### Appendix: starts_with 実装方針
- `strncmp()` は Allowed 外なので**自前実装**する。
- `needle` の終端 `'\0'` を到達条件にすれば、`nlen` を毎回参照しなくても判定可能。
- ただし本実装では `nlen` を事前に取り、走査の範囲チェック（`i + nlen <= len`）に使用している。
