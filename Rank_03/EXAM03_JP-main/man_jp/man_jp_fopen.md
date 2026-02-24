# FOPEN(3) — Linux Programmer's Manual

## 名前
fopen, fdopen, freopen — ストリームを開く／関連付ける

## 書式
```c
#include <stdio.h>

FILE *fopen(const char *restrict pathname, const char *restrict mode);
FILE *fdopen(int fd, const char *mode);
FILE *freopen(const char *restrict pathname, const char *restrict mode,
              FILE *restrict stream);
```

## 説明
`fopen()` はパス `pathname` をモード `mode` で開き、バッファ付きストリーム `FILE *` を返す。
`mode` は以下の文字の組み合わせで指定する：

| 主要モード | 意味 |
|---|---|
| `"r"` | 既存ファイルを読み取り用で開く |
| `"w"` | 書き込み用で新規作成（存在すれば切り詰め） |
| `"a"` | 追記用で開く（常に末尾に書く） |

修飾子：`"+"`（更新：読み書き可）、`"b"`（バイナリ、POSIX では意味は限定的）、
実装拡張で `"x"`（排他的作成）などがある。

`fdopen()` は、既存のファイル記述子 `fd` をストリームに関連付ける。
`freopen()` は、既存のストリームを閉じて別のファイルに再関連付けする。

## 返り値
成功時：新しい `FILE *`。  
失敗時：`NULL`（`errno` が設定される）。

## エラー
代表例：`EACCES`, `EISDIR`, `EMFILE`, `ENFILE`, `ENOENT`, `ENOSPC`, `EROFS`, `EOVERFLOW` など。

## 属性
| インタフェース | 属性 | 値 |
|---|---|---|
| `fopen()`, `fdopen()`, `freopen()` | スレッド安全性 | MT-Safe |

## 準拠
C89, C99, POSIX.1-2001, POSIX.1-2008。

## 注記（NOTES）
- `"w"` は既存ファイルを **長さ 0 に切り詰める**。上書き事故に注意。  
- `"a"` はファイル位置を末尾へ強制し、並行書き込みで追記が保証される（OS 依存）。  
- `fdopen()` の `mode` は `fd` のアクセス許可と整合していなければならない。  
- テキスト／バイナリ差は POSIX では小さく、`"b"` は移植性のために残されている。

## 例
```c
#include <stdio.h>

int main(void) {
    FILE *fp = fopen("out.txt", "w");
    if (!fp) return 1;
    fputs("hello\n", fp);
    fclose(fp);
    return 0;
}
```

## 関連項目
`open(2)`, `close(2)`, `fclose(3)`, `fflush(3)`, `fileno(3)`

## コロフォン（COLOPHON）
このページは Linux man-pages プロジェクトの一部である。プロジェクトの説明、バグ報告、および最新版の入手方法：  
<https://www.kernel.org/doc/man-pages/>

---

## 解説（実務的補足）
- **排他的作成**：既存ファイルを上書きしたくない場合、`open(2)` の `O_CREAT|O_EXCL` と `fdopen()` の組み合わせを使う。  
- **バッファ同期**：`dup2(2)` や `write(2)` と混在させるときは `fflush()`／`fseek()` で同期を取る。  
- **一時ファイル**：削除忘れ回避には `tmpfile(3)` も有用（自動削除）。
