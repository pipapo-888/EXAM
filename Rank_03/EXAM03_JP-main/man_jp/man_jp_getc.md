# GETC(3) — Linux Programmer's Manual

## 名前
getc, fgetc, getchar, getc_unlocked — ストリームから 1 文字を読み取る

## 書式
```c
#include <stdio.h>

int getc(FILE *stream);
int fgetc(FILE *stream);
int getchar(void);
int getc_unlocked(FILE *stream);
```

## 説明
`getc()` と `fgetc()` は、指定されたストリーム `stream` から次の 1 文字を読み取り、
`unsigned char` を `int` に拡張した値を返す。  
入力の終端（EOF）またはエラーが発生した場合は `EOF` が返される。

`getchar()` は `getc(stdin)` と同等であり、標準入力から 1 文字を取得する。

`getc_unlocked()` はロックを行わない非同期安全でない版であり、
スレッド安全性を犠牲にして高速化を目的とする場合に使用される。  
同様に `getchar_unlocked()` も存在する。

これらの関数はバッファリングされた I/O を使用する。`fread(3)` のように複数バイトをまとめて
読み込むわけではなく、呼び出しごとに 1 文字ずつ読み取る。

## 返り値
成功時：読み取った文字（`unsigned char` を `int` に拡張した値）を返す。  
エラーまたは EOF：`EOF` を返す。  
どちらであるかを区別するには、`feof(3)` および `ferror(3)` を使用する。

## エラー
- `EAGAIN` — 非ブロッキングモードでデータがまだ利用できない。  
- `EBADF` — ストリームが無効なファイルディスクリプターに関連付けられている。  
- `EINTR` — シグナルで中断された。  
- `EIO` — 入出力エラー。

## 属性
| インタフェース | 属性 | 値 |
|---|---|---|
| `getc()`, `fgetc()`, `getchar()` | スレッド安全性 | MT-Safe locale |
| `getc_unlocked()` | スレッド安全性 | MT-Unsafe |

## 準拠
C89, C99, POSIX.1-2001, POSIX.1-2008 に準拠。

## 注記（NOTES）
- `getc()` はマクロとして実装されることが多く、呼び出しごとに評価副作用がある可能性がある。  
  引数に副作用を持つ式（例：`getc(fp_array[i++])`）を与えるのは避けること。  
- `fgetc()` は常に関数として実装されるため、副作用が評価されない。  
- 1 文字ずつの入出力は遅いため、大量データ読み込みには `fread(3)` の利用を推奨。  
- `getc_unlocked()` を使用する場合は、呼び出し前後で `flockfile(3)` / `funlockfile(3)` により明示的にロック制御を行うこと。

## 例
```c
#include <stdio.h>

int main(void) {
    int c;
    while ((c = getchar()) != EOF) {
        putchar(c);
    }
    return 0;
}
```

## 関連項目
`fread(3)`, `unlocked_stdio(3)`, `ferror(3)`, `feof(3)`, `putc(3)`, `putchar(3)`

## コロフォン（COLOPHON）
このページは Linux man-pages プロジェクトの一部である。プロジェクトの説明、バグ報告、および最新版の入手方法については：  
<https://www.kernel.org/doc/man-pages/>

---

## 解説（実務的補足）
- **getc と fgetc の違い**：多くの実装では `getc` はマクロ、`fgetc` は関数。副作用を避けたい場合は後者を選ぶ。  
- **EOF 判定**：ループ内で `c = getc(fp)` の結果を EOF と比較するのが定石。`while ((c=getc(fp)) != EOF)` の形。  
- **スレッド安全性**：`getc_unlocked()` は高速だが競合に弱い。並列環境では `getc()` を使用するのが安全。  
- **性能対策**：大量の文字読み込みには `fread()`、行単位読み込みには `fgets()` を使用する方が効率的。
