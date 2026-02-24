
# read() 関数の使い方徹底解説ガイド
**対象**: C言語での低レベルI/Oを学びたい人、42課題（filter, pipex, minishellなど）でreadを正しく使いたい人  
**目的**: `read()` システムコールの使い方、戻り値の意味、エラー処理、実装例、落とし穴を整理して理解する。

---

## 1. 概要
`read()` は Unix 系 OS における最も基本的な **低レベル入出力関数** です。  
ファイルディスクリプタから **バイト列を直接読み取る** ために使われます。

```c
#include <unistd.h>

ssize_t read(int fd, void *buf, size_t count);
```

### 引数
| 引数 | 意味 |
|------|------|
| `fd` | ファイルディスクリプタ（例: 0=stdin, 1=stdout, 2=stderr） |
| `buf` | 読み込んだデータを格納するバッファへのポインタ |
| `count` | 読み込む最大バイト数 |

### 戻り値
| 値 | 意味 |
|----|------|
| `> 0` | 実際に読み取ったバイト数 |
| `0` | EOF（ファイルの終端、パイプ/入力の終了） |
| `-1` | エラー発生（`errno` に詳細が設定される） |

---

## 2. 基本的な使い方（標準入力を読む）
```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 64

int main(void) {
    char buf[BUF_SIZE + 1];
    ssize_t n;

    n = read(0, buf, BUF_SIZE); // fd=0 → 標準入力
    if (n < 0) {
        perror("read");
        return 1;
    }
    buf[n] = '\0'; // 終端を忘れずに！
    printf("Read %zd bytes: %s\n", n, buf);
    return 0;
}
```

### 実行例
```bash
$ echo "hello" | ./a.out
Read 6 bytes: hello
```

> 改行も1文字として読み込まれるため、5文字の"hello" + 改行で6バイト。

---

## 3. ファイルを読む例
```c
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF_SIZE 128

int main(void) {
    int fd = open("sample.txt", O_RDONLY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    char buf[BUF_SIZE + 1];
    ssize_t n;

    while ((n = read(fd, buf, BUF_SIZE)) > 0) {
        buf[n] = '\0';
        printf("%s", buf);
    }
    if (n < 0)
        perror("read");

    close(fd);
    return 0;
}
```

### 説明
- `open()` でファイルを開き、`read()` で読み取り。
- EOF で `read()` は 0 を返す → ループ終了。
- 最後に `close(fd)` でファイルディスクリプタを解放。

---

## 4. チャンク読み（filter課題で必須）
`read()` は**すべての入力を一度に読み込む保証がない**ため、ループで繰り返す必要があります。  
`filter` や `pipex` のように標準入力を完全に読み込むには以下のようにします。

```c
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define CHUNK 1024

int main(void) {
    char *buf = malloc(CHUNK);
    if (!buf) return 1;
    ssize_t total = 0;
    ssize_t r;

    while ((r = read(0, buf + total, CHUNK)) > 0) {
        total += r;
        buf = realloc(buf, total + CHUNK);
        if (!buf) { perror("realloc"); return 1; }
    }
    if (r < 0) perror("read");

    buf[total] = '\0';
    printf("Input:\n%s", buf);
    free(buf);
    return 0;
}
```

### ポイント
- `read()` の戻り値を確認し、`r==0`（EOF）で終了。
- `r<0` なら `perror("read")` でエラー表示。
- **複数回 read() を呼ぶ** のが正しい使い方。

---

## 5. エラー処理の流れ
| 条件 | errno | 対応 |
|------|--------|------|
| ファイルが存在しない | ENOENT | `perror("read")` で "No such file" |
| 権限がない | EACCES | "Permission denied" |
| ディスクリプタ不正 | EBADF | open() ミス or close後に使用 |
| シグナル割込み | EINTR | 再試行が必要な場合も（ループ推奨） |

**例: EINTR 対応**
```c
ssize_t safe_read(int fd, void *buf, size_t count) {
    ssize_t r;
    do { r = read(fd, buf, count); }
    while (r < 0 && errno == EINTR);
    return r;
}
```

---

## 6. 注意点・落とし穴
1. **ヌル終端をつけ忘れる**
   - `read()` は「生バイト数」しか返さない。文字列操作前に `buf[n] = '\0'` 必須。
2. **EOF を勘違い**
   - `read()` が 0 を返す = 入力が終わった。
3. **バイナリファイル**
   - `'\0'`（NUL）が途中に含まれる → `strlen()` は使えない。
4. **一度に全部読める保証なし**
   - ソケットやパイプでは部分読み取りが起きる。ループ必須。
5. **バッファ拡張のrealloc忘れ**
   - 入力長が不明な場合は確保し直す。`filter`課題で頻出。

---

## 7. 実践例：標準入力→標準出力へコピー（cat風）
```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUF 4096

int main(void){
    char buf[BUF];
    ssize_t r;
    while ((r = read(0, buf, BUF)) > 0){
        if (write(1, buf, r) != r) { perror("write"); return 1; }
    }
    if (r < 0) perror("read");
    return 0;
}
```

### 実行
```bash
$ echo "hello world" | ./mycat
hello world
```

---

## 8. まとめ
- `read()` は「ファイルディスクリプタから**生バイト列**を読む」低レベルAPI。
- 戻り値の扱い（`>0`, `0`, `<0`）を明確に分ける。
- EOF とエラーを混同しない。
- **ループ・バッファ拡張・ヌル終端**の3点セットを守れば安全。

---

## 9. 関連関数
| 関数 | 説明 |
|------|------|
| `write()` | バイト列をファイルディスクリプタへ出力 |
| `open()`, `close()` | ファイルディスクリプタの取得と解放 |
| `lseek()` | ファイル位置の移動 |
| `readv()`, `pread()` | 複数バッファ・位置指定読み |
| `getline()` | 高レベルAPI（`read`ラップ版） |
| `errno` + `perror()` | エラー処理 |
