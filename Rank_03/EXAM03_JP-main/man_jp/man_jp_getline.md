# GETLINE(3) — Linux Programmer's Manual

## 名前
getline, getdelim — ストリームから 1 行または区切り文字まで読み取る

## 書式
```c
#include <stdio.h>

ssize_t getline(char **lineptr, size_t *n, FILE *stream);
ssize_t getdelim(char **lineptr, size_t *n, int delim, FILE *stream);
```

## 説明
`getline()` は、`stream` から 1 行を読み取り、改行文字を含めて `*lineptr` が指すバッファに格納する。
必要に応じて内部で `realloc(3)` によりバッファを自動的に拡張する。最初の呼び出しでは `*lineptr == NULL`、`*n == 0` としておくのが推奨である。
文字列はヌル終端される。

`getdelim()` は一般化された関数で、行末の代わりに任意の区切り文字 `delim` が見つかるまで読み取る。
`getline(lineptr, n, stream)` は `getdelim(lineptr, n, '\n', stream)` と等価である。

成功時、戻り値は読み取ったバイト数（区切り文字を含む）。エラー時や、読み取るデータがない EOF では `-1` を返す。

## 返り値
成功時：読み取ったバイト数（改行/区切り文字を含む）。  
失敗またはデータなしの EOF：`-1` を返す。`-1` の場合、`feof(3)` と `ferror(3)` で EOF かエラーかを判定できる。

## エラー
`EINVAL`（`lineptr` もしくは `n` が不正）、`ENOMEM`（メモリ確保失敗）、`EIO`（入出力エラー）など。基礎となるファイル記述子の状態によって他の I/O エラーが発生し得る。

## 属性
| インタフェース | 属性 | 値 |
|---|---|---|
| `getline()`, `getdelim()` | スレッド安全性 | MT-Safe |

## 準拠
`getline()` / `getdelim()` は POSIX.1-2008 で規定される。

## 注記（NOTES）
### Feature Test Macro（glibc）
`feature_test_macros(7)` を参照。glibc でこれらを利用するには下記のいずれかを定義する：
```
getline(), getdelim():
    _GNU_SOURCE          （GNU 拡張）
    もしくは POSIX モードで _POSIX_C_SOURCE >= 200809L
```

- 改行（もしくは区切り文字）は**削除されない**。必要であれば呼び出し側で取り除くこと。  
- バッファは必要に応じて再確保されるため、呼び出し後の `*lineptr` は**別アドレス**になり得る。使用後は `free(*lineptr)` で解放できる。

## 例
```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *fp = fopen("/etc/passwd", "r");
    if (!fp) return 1;

    char *line = NULL;
    size_t cap = 0;
    ssize_t nread;

    while ((nread = getline(&line, &cap, fp)) != -1) {
        /* 改行を含む。必要なら取り除く */
        printf("len=%zd: %s", nread, line);
    }
    free(line);
    fclose(fp);
    return 0;
}
```

## 関連項目
`fgets(3)`, `read(2)`, `malloc(3)`, `realloc(3)`, `free(3)`, `feature_test_macros(7)`

## コロフォン（COLOPHON）
このページは Linux man-pages プロジェクトの一部である。プロジェクトの説明、バグ報告、最新版の入手方法については：  
<https://www.kernel.org/doc/man-pages/>

---

## 解説（実務的補足）
- **安全性**：固定長バッファが不要で、行長無制限の入力に強い。`fgets()` より安全。  
- **EOF/エラー判定**：戻り値 `-1` のとき、`feof()` と `ferror()` で分岐するのが定石。  
- **区切り応用**：`getdelim()` により CSV フィールドなど任意区切りでの抽出が簡便になる。  
- **パフォーマンス**：再確保が頻発する入力ではオーバーヘッドが増えるため、大きめの初期容量を与える最適化も有効。