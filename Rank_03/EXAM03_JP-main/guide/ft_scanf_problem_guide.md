
# FT_SCANF 解法ガイド（Problem 2）
**対象課題**: `ft_scanf`  
**目的**: 標準ライブラリ関数 `scanf()` の一部機能を再現し、  
可変長引数（`<stdarg.h>`）と入力解析の基礎を理解する。

---

## 1. 課題仕様の要点

### 実行形式
```
int ft_scanf(const char *format, ...);
```

### 制約
- 実装対象のフォーマット指定子：
  - `%s`（文字列）
  - `%d`（整数）
  - `%c`（文字）
- 以下のオプション・拡張は**扱わない**：
  - `*`, `m`, `'`, フィールド幅, 型修飾子（h, l, ll, ...）, `%n$`
- 入力は **標準入力（stdin）** から読み取る。
- 正常動作時は「成功した変換の数」を返す。
- 読み取りエラー・EOF 到達時は 0 または EOF を返す。

### 許可関数
```
fgetc, ungetc, ferror, feof, isspace, isdigit, stdin,
va_start, va_arg, va_end
```

---

## 2. 全体設計

### 2.1 処理の流れ
```
format文字列を1文字ずつ読み取り
  ↓
  '%' の場合 → 次の文字で変換指定子を判定
  ↓
  各指定子に応じて標準入力から値を取得
  ↓
  取得結果を va_arg() で渡された変数に格納
  ↓
  読み取れた個数をカウント
  ↓
  最後にカウントを返す
```

### 2.2 フォーマット解析の基本
- `va_list ap;`
- `va_start(ap, format);`
- 各 `%` ごとに `va_arg(ap, type)` で次のポインタを取り出す。
- 最後に `va_end(ap);`

---

## 3. 実装ステップ

### ステップ1：入力文字の取得
```c
int c = fgetc(stdin);
if (c == EOF)
    return (count ? count : EOF);
```

### ステップ2：空白処理
- フォーマット文字列中の空白は「任意数の空白入力にマッチ」。
- `isspace(c)` を利用してスキップ。

### ステップ3：各指定子の処理
#### `%c`
```c
char *dst = va_arg(ap, char *);
int c = fgetc(stdin);
if (c == EOF) return count;
*dst = (char)c;
count++;
```

#### `%s`
```c
char *dst = va_arg(ap, char *);
int c, i = 0;
while ((c = fgetc(stdin)) != EOF && !isspace(c))
    dst[i++] = (char)c;
dst[i] = '\0';
if (c != EOF) ungetc(c, stdin);
count++;
```

#### `%d`
```c
int *dst = va_arg(ap, int *);
int sign = 1, c;
int val = 0;
while (isspace(c = fgetc(stdin)));
if (c == '-') { sign = -1; c = fgetc(stdin); }
if (!isdigit(c)) return count;
do {
    val = val * 10 + (c - '0');
} while (isdigit(c = fgetc(stdin)));
*dst = sign * val;
if (c != EOF) ungetc(c, stdin);
count++;
```

---

## 4. スケルトンコード（Allowed関数のみ）
```c
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

int ft_scanf(const char *format, ...) {
    va_list ap;
    int count = 0;
    va_start(ap, format);

    while (*format) {
        if (isspace(*format)) {
            int c;
            while (isspace(c = fgetc(stdin)));
            ungetc(c, stdin);
            format++;
            continue;
        }
        if (*format == '%') {
            format++;
            if (*format == 'c') {
                char *dst = va_arg(ap, char *);
                int c = fgetc(stdin);
                if (c == EOF) break;
                *dst = (char)c;
                count++;
            } else if (*format == 's') {
                char *dst = va_arg(ap, char *);
                int c, i = 0;
                while (isspace(c = fgetc(stdin)));
                do {
                    dst[i++] = (char)c;
                } while ((c = fgetc(stdin)) != EOF && !isspace(c));
                dst[i] = '\0';
                if (c != EOF) ungetc(c, stdin);
                count++;
            } else if (*format == 'd') {
                int *dst = va_arg(ap, int *);
                int c, val = 0, sign = 1;
                while (isspace(c = fgetc(stdin)));
                if (c == '-') { sign = -1; c = fgetc(stdin); }
                if (!isdigit(c)) break;
                do {
                    val = val * 10 + (c - '0');
                } while (isdigit(c = fgetc(stdin)));
                *dst = sign * val;
                if (c != EOF) ungetc(c, stdin);
                count++;
            }
        }
        format++;
    }
    va_end(ap);
    return count;
}
```

---

## 5. テスト例

### 基本ケース
```bash
$> echo "42 a hello" | ./test_scanf
Result -> i=42, c=a, s=hello
```

### 負数整数
```bash
$> echo "-123" | ./test_scanf
Result -> i=-123
```

### 空白スキップ確認
```bash
$> echo "   77   b  test" | ./test_scanf
Result -> 77 b test
```

### 入力不足（途中でEOF）
```bash
$> echo "42" | ./test_scanf
Result -> 1（整数のみ読み取り）
```

---

## 6. よくある落とし穴
- `va_end()` を忘れる。
- 空白を正しくスキップしない。
- `%d` の負数符号を処理していない。
- `ungetc()` の呼び出し忘れで次回読み取りがズレる。
- 入力が途中で EOF のとき、return 値の扱いを誤る。

---

## 7. 実装上のコツ
| 要素 | 解説 |
|------|------|
| **fgetc/ungetc** | 逐次読み・戻しで簡易パーサを作る。 |
| **isdigit/isspace** | ASCII系判定に必須。 |
| **va_arg** | フォーマットごとに取り出す型に注意。 |
| **EOF処理** | 読み取り不能時は即 return。 |

---

## 8. 発展的課題
- `ft_sscanf()`：入力を文字列バッファから読む版。
- `%u`, `%x`, `%f` の追加対応。
- 入力制限付き（バッファ長を受け取る）安全版。

---

## 9. まとめ
- `ft_scanf` は C 言語の入出力を理解する上で最良の可変引数課題。  
- **手続き的パーサ構築・フォーマット処理・型変換** の3要素をすべて含む。  
- 完成後は `scanf(3)` の man ページと比較して挙動の差を分析すると理解が深まる。

