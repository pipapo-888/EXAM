# FERROR(3) — Linux Programmer's Manual

## 名前
ferror, feof, clearerr, ferror_unlocked, feof_unlocked, clearerr_unlocked — ストリームのエラー／EOF 指示子の検査とクリア

## 書式
```c
#include <stdio.h>

int ferror(FILE *stream);
int feof(FILE *stream);
void clearerr(FILE *stream);

/* GNU 拡張（glibc）*/
int ferror_unlocked(FILE *stream);
int feof_unlocked(FILE *stream);
void clearerr_unlocked(FILE *stream);
```

## 説明
各 `FILE *` ストリームは 2 つの状態指示子を持つ：
- **エラー指示子**（error indicator）
- **EOF 指示子**（end-of-file indicator）

入出力操作中にエラーが発生するとエラー指示子が立ち、
入力操作でファイル終端に到達すると EOF 指示子が立つ。

- `ferror(stream)` は、`stream` の**エラー指示子が立っているか**を検査する。  
- `feof(stream)` は、`stream` の**EOF 指示子が立っているか**を検査する。  
- `clearerr(stream)` は、これら **両方の指示子をクリア** する。

`*_unlocked` 版はロックを行わない非同期安全でない実装であり、GNU 拡張である。

`getc(3)` / `fgetc(3)` などが `EOF` を返したとき、
**EOF なのかエラーなのか**は `feof()` と `ferror()` の組合せで判定する。

## 返り値
- `ferror()` / `feof()` / `ferror_unlocked()` / `feof_unlocked()`：
  - 該当の指示子が立っていれば**非 0**、それ以外は **0** を返す。
- `clearerr()` / `clearerr_unlocked()`：値を返さない。

## エラー
これらの関数自体は `errno` を設定しない。  
ただし、先行する I/O 操作が失敗している場合は `errno` に原因が残っている可能性がある。

## 属性
| インタフェース | 属性 | 値 |
|---|---|---|
| `ferror()`, `feof()`, `clearerr()` | スレッド安全性 | MT-Safe |
| `*_unlocked` 版 | スレッド安全性 | MT-Unsafe |

## 準拠
`ferror()`, `feof()`, `clearerr()` は C89, C99, POSIX.1-2001, POSIX.1-2008 に準拠。  
`ferror_unlocked()`, `feof_unlocked()`, `clearerr_unlocked()` は GNU 拡張。

## 注記（NOTES）
- ある読み取り関数が `EOF` を返した直後に、`feof()` と `ferror()` の両方が **0** の可能性はない。  
  いずれか（EOF かエラー）が必ず立っている。  
- 一部の I/O 失敗では、**エラー発生時点で `errno` が設定** されるが、`ferror()` は単に「エラーが起きた」事実のみを示す。  
  具体的な理由は、直前の I/O 関数の戻り値と `errno` を確認する。
- 失敗からの復帰には `clearerr()` が必要になる場合がある（例：`EINTR` による中断後の再試行など）。
- `*_unlocked` は明示的な `flockfile(3)` / `funlockfile(3)` と併用して使う。

## 例
```c
#include <stdio.h>

int main(void) {
    int c;
    while ((c = getchar()) != EOF) {
        /* 入力をそのまま写す */
        if (putchar(c) == EOF)
            break;
    }

    if (ferror(stdin))  { perror("stdin");  clearerr(stdin); }
    if (ferror(stdout)) { perror("stdout"); clearerr(stdout); }
    if (feof(stdin))    { /* EOF 到達 */ }

    return 0;
}
```

## 関連項目
`perror(3)`, `strerror(3)`, `getc(3)`, `fgetc(3)`, `flockfile(3)`, `funlockfile(3)`

## コロフォン（COLOPHON）
このページは Linux man-pages プロジェクトの一部である。プロジェクトの説明、バグ報告、および最新版の入手方法：  
<https://www.kernel.org/doc/man-pages/>

---

## 解説（実務的補足）
- **診断の流れ**：I/O 関数が失敗 → 戻り値を確認 → `errno` を記録 → `ferror()` / `feof()` で状態確定 → 必要なら `clearerr()`。  
- **反復処理**：`EOF` によるループ終了時、真の EOF か一時エラー（`EINTR` など）かを判別し、再試行方針を決める。  
- **バッファリングの影響**：出力失敗（例：`EPIPE`）は `fclose(3)` や `fflush(3)` のタイミングで初めて発覚することがある。エラー確認を徹底する。