# MALLOC(3) — Linux Programmer's Manual

## 名前
malloc, free, calloc, realloc, reallocarray — 動的メモリの確保・再確保・解放

## 書式
```c
#include <stdlib.h>

void *malloc(size_t size);
void free(void *ptr);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);
```

## 説明
`malloc()` 関数は、`size` バイトのメモリ領域を確保し、その先頭へのポインタを返す。
確保された領域の内容は未定義である。

`calloc()` は、`nmemb` 個の要素からなる配列を確保し、すべてのバイトを 0 で初期化する。
引数 `nmemb * size` の積がオーバーフローする場合、確保は失敗する。

`realloc()` は、以前に確保されたブロック `ptr` のサイズを `size` に変更する。
新しい領域が必要になった場合、古い内容は新しい領域にコピーされ、古い領域は解放される。
`ptr` が `NULL` の場合、`realloc(ptr, size)` は `malloc(size)` と等価。
`size` が 0 の場合、`free(ptr)` と等価であり、NULL を返す。

`reallocarray()` は、`nmemb * size` の積のオーバーフローを安全に検出できる `realloc()` の拡張版である。

`free()` は、以前に確保されたメモリ領域を解放する。
`ptr` が `NULL` の場合、何も行われない。

## 返り値
成功時：確保された領域へのポインタ。  
失敗時：`NULL` を返し、`errno` に `ENOMEM` を設定する。
`realloc()` が失敗した場合でも元のブロックは保持される。

## エラー
`ENOMEM` — メモリ不足またはシステム制限により確保に失敗した。

## 属性
| インタフェース | 属性 | 値 |
|---|---|---|
| `malloc()`, `free()`, `calloc()`, `realloc()`, `reallocarray()` | スレッド安全性 | MT-Safe |

## 準拠
C89, C99, POSIX.1-2001, POSIX.1-2008 に準拠。
`reallocarray()` は OpenBSD で導入され、glibc 2.26 以降で利用可能。

## 注記（NOTES）
- `malloc()` で確保された領域の内容は未定義であるため、必要に応じて `memset()` で初期化する。  
- `calloc()` は要素数と要素サイズの積がオーバーフローする場合に安全に失敗する。  
- `realloc()` で NULL を渡すと `malloc(size)` と同等、`size` が 0 の場合は `free(ptr)` と同等。  
- `reallocarray()` は整数オーバーフローを検出するため、配列確保に推奨される。  
- `free()` 後のポインタを再利用することは未定義動作であり、クラッシュや脆弱性につながる。  
- ダブルフリー（二重解放）は重大なエラーであり、セキュリティリスクを伴う。

## 例
```c
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int *arr = malloc(5 * sizeof(int));
    if (!arr) {
        perror("malloc");
        return 1;
    }

    for (int i = 0; i < 5; i++) arr[i] = i;

    int *tmp = realloc(arr, 10 * sizeof(int));
    if (!tmp) {
        perror("realloc");
        free(arr);
        return 1;
    }
    arr = tmp;

    for (int i = 5; i < 10; i++) arr[i] = i;

    for (int i = 0; i < 10; i++) printf("%d ", arr[i]);
    printf("\n");

    free(arr);
    return 0;
}
```

## 関連項目
`brk(2)`, `sbrk(2)`, `mmap(2)`, `posix_memalign(3)`, `malloc_info(3)`, `calloc(3)`, `realloc(3)`

## コロフォン（COLOPHON）
このページは Linux man-pages プロジェクト（リリース 5.10）の一部である。
プロジェクトの説明、バグ報告、および最新版の入手については：  
<https://www.kernel.org/doc/man-pages/>

---

## 解説（実務的補足）
- **glibc 実装**：`malloc()` は内部的に `brk(2)` または `mmap(2)` によりヒープ領域を拡張して確保する。
  大きなブロックは匿名マッピングとして確保される。
- **断片化**：頻繁な `malloc()` / `free()` によりヒープが断片化する。
  短寿命データにはアロケータプールを導入すると効率的。
- **安全性**：`reallocarray()` により整数オーバーフローを防ぐ。
  `free()` 後のポインタは NULL に設定して再利用を防止する。
- **tcache（スレッドキャッシュ）**：glibc 2.26 以降ではスレッドローカルなキャッシュを利用し、
  小サイズの確保/解放を高速化している。
- **診断**：`malloc_stats()` や `mallinfo(3)` により使用状況を調査できる。

---

*原文: Linux man-pages project version 5.10 — malloc(3)*
