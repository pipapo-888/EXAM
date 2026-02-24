# FSEEK(3) — Linux Programmer's Manual

## 名前
fseek, ftell, rewind, fseeko, ftello — ストリームのファイル位置を設定・取得・リセットする

## 書式
```c
#include <stdio.h>

int fseek(FILE *stream, long offset, int whence);
long ftell(FILE *stream);
void rewind(FILE *stream);

#define _LARGEFILE64_SOURCE
#include <stdio.h>

int fseeko(FILE *stream, off_t offset, int whence);
off_t ftello(FILE *stream);
```

## 説明
`fseek()` は、`stream` のファイル位置指示子を、基準点 `whence` から `offset` バイト移動させる。
`whence` には以下の定数を指定する：

| 定数 | 意味 |
|------|------|
| `SEEK_SET` | ファイル先頭からの相対位置 |
| `SEEK_CUR` | 現在位置からの相対位置 |
| `SEEK_END` | ファイル末尾からの相対位置 |

`ftell()` は、現在のファイル位置を返す。  
`rewind()` は、ファイル位置を先頭に戻し、かつ `clearerr(stream)` を呼び出す。

`fseeko()` および `ftello()` は、`off_t` 型を使用して大きなファイル（>2GB）を扱うための関数である。  
`fseek()` / `ftell()` は `long` 型を返すため、32bit 環境では上限に制約がある。

## 返り値
`fseek()` および `fseeko()`：成功時 0、失敗時 `-1`。  
`ftell()` および `ftello()`：成功時 現在位置、失敗時 `-1L`（および `errno` 設定）。

## エラー
- `EINVAL` — `whence` が不正、または `offset` が負でシーク不可。  
- `ESPIPE` — パイプや FIFO、ソケットなどシーク不可能なストリームに対して呼び出された。  
- `EOVERFLOW` — 返り値が `long` の範囲外。  

## 属性
| インタフェース | 属性 | 値 |
|---|---|---|
| `fseek()`, `ftell()`, `rewind()`, `fseeko()`, `ftello()` | スレッド安全性 | MT-Safe |

## 準拠
C89, C99, POSIX.1-2001, POSIX.1-2008。  
`fseeko()` / `ftello()` は POSIX.1-2001 で追加。

## 注記（NOTES）
- `rewind()` はエラーを報告しないため、厳密なエラーハンドリングが必要な場合は `fseek(stream, 0L, SEEK_SET)` を使用する。  
- テキストモードで開かれたファイルでは、改行コード変換によりファイルオフセットが物理的な位置と一致しない可能性がある。  
- 標準出力／入力など端末デバイスではシークできない。  
- 64bit オフセット対応を有効にするには、ソースの先頭に以下を定義する：  
  ```c
  #define _FILE_OFFSET_BITS 64
  ```

## 例
```c
#include <stdio.h>

int main(void) {
    FILE *fp = fopen("data.bin", "rb");
    if (!fp) return 1;

    fseek(fp, 0L, SEEK_END);
    long size = ftell(fp);
    printf("ファイルサイズ: %ld バイト\n", size);

    rewind(fp); /* ファイル先頭へ戻る */
    fclose(fp);
    return 0;
}
```

## 関連項目
`lseek(2)`, `fopen(3)`, `ferror(3)`, `clearerr(3)`

## コロフォン（COLOPHON）
このページは Linux man-pages プロジェクトの一部である。プロジェクトの説明、バグ報告、および最新版の入手方法については：  
<https://www.kernel.org/doc/man-pages/>

---

## 解説（実務的補足）
- **バイナリファイル処理**：`fseek()` + `ftell()` によりファイルサイズを効率的に算出できる。  
- **大規模ファイル対応**：`fseeko()` / `ftello()` を使用することで 2GB 超のファイルを安全に扱える。  
- **注意点**：シークはバッファリング状態に依存する。I/O混在時は `fflush()` または `fseek()` で同期を取る。  
- **パイプ処理**：`ESPIPE` エラーを受けたらストリームを再設計する（シーク不可）。