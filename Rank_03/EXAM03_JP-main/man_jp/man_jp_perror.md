PERROR(3) — Linux Programmer's Manual
名前（NAME）

perror - システムエラーメッセージを出力する

書式（SYNOPSIS）
#include <stdio.h>

void perror(const char *s);

#include <errno.h>

const char * const sys_errlist[];
int sys_nerr;
int errno;       /* 実際にはこのように宣言されているわけではない。詳細は errno(3) を参照。 */

glibc の機能テストマクロ要件（Feature Test Macro Requirements for glibc）

sys_errlist, sys_nerr の使用には次のマクロが必要：

glibc バージョン	マクロ
2.19〜2.31	_DEFAULT_SOURCE
2.19 以前	_BSD_SOURCE
説明（DESCRIPTION）

perror() 関数は、直前のシステムコールまたはライブラリ関数で発生した
最後のエラーを説明するメッセージを標準エラー出力に出力する。

s が NULL でなく、かつ先頭文字がヌル文字 ('\0') でない場合、
まず引数文字列 s が出力され、続けてコロンと空白が出力される。
その後、現在の errno の値に対応するエラーメッセージと改行文字が出力される。

この関数を最も有効に利用するには、s にはエラーを発生させた関数名などを含めるのが望ましい。

sys_errlist と sys_nerr

グローバルエラーリスト sys_errlist[] は、errno をインデックスとして
対応するエラーメッセージ文字列を取得できる配列である。
テーブル内で提供される最大のメッセージ番号は sys_nerr - 1 である。

この配列に直接アクセスする場合、新しいエラー値が
sys_errlist[] に追加されていない可能性がある点に注意すること。
sys_errlist[] の使用は現在では非推奨であり、代わりに strerror(3) を使用することが推奨される。

errno と perror() の関係

システムコールが失敗した場合、通常は -1 を返し、
グローバル変数 errno にエラー内容を表す値を設定する。
この値は <errno.h> に定義されている。
多くのライブラリ関数も同様の動作を行う。

perror() 関数は、このエラーコードを人間が読める形式のメッセージに変換して表示する。

システムコールやライブラリ関数が成功した場合、errno の値は未定義である。
成功した呼び出しが内部で別のライブラリ関数を使用し、その関数が失敗した場合、
errno が変更されることがあるためである。
したがって、失敗した呼び出しの直後に perror() を呼ばない場合、
errno の値を一時的に保存しておく必要がある。

バージョン（VERSIONS）

glibc 2.32 以降では、sys_errlist および sys_nerr の宣言は <stdio.h> から削除された。

属性（ATTRIBUTES）
インタフェース	属性	値
perror()	スレッド安全性	MT-Safe race:stderr
準拠（CONFORMING TO）

perror(), errno: POSIX.1-2001, POSIX.1-2008, C89, C99, 4.3BSD に準拠。
外部変数 sys_nerr および sys_errlist は BSD 由来であり、POSIX.1 では規定されていない。

注意（NOTES）

sys_nerr および sys_errlist は glibc により <stdio.h> 内で定義されている。
ただし、これらの使用は非推奨であり、将来的な互換性は保証されない。
代替として strerror(3) または strerror_r(3) の使用を推奨する。

関連項目（SEE ALSO）

err(3), errno(3), error(3), strerror(3)

コロフォン（COLOPHON）

このページは Linux man-pages プロジェクト リリース 5.10 の一部である。
プロジェクトの説明、バグ報告、および最新版の入手方法については：
https://www.kernel.org/doc/man-pages/

解説（実務的補足）

典型的な使用法

FILE *fp = fopen("data.txt", "r");
if (fp == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
}


このように、失敗した関数名を引数 s に与えることで、
標準エラー出力に「fopen: No such file or directory」などの明確な診断を出力できる。

errno の保存
複数の関数呼び出しを行う前に、失敗したシステムコールのエラー情報を保持したい場合、
int saved_errno = errno; として保存しておくことが重要。
これは printf() などの内部呼び出しが errno を上書きする可能性があるためである。

スレッド安全性
perror() 自体はスレッドセーフだが、stderr を共有している複数スレッドが同時に出力すると
メッセージが混在する可能性がある。必要に応じてロック制御を行うこと。