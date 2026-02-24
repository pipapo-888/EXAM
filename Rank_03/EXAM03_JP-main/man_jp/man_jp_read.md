READ(3POSIX) — POSIX Programmer's Manual
プロローグ（PROLOG）
このページは POSIX Programmer’s Manual の一部であり、
POSIX 標準に準拠したシステムインタフェースを定義する。

名前（NAME）
read, pread — ファイルからデータを読み込む

書式（SYNOPSIS）
c
￼コードをコピーする
#include <unistd.h>

ssize_t read(int fildes, void *buf, size_t nbyte);
ssize_t pread(int fildes, void *buf, size_t nbyte, off_t offset);
説明（DESCRIPTION）
read() 関数は、ファイル記述子 fildes によって参照されるオープン済みファイルから、
最大 nbyte バイトのデータをバッファ buf に読み込む。

読み込み開始位置は、ファイルオフセットによって決定される。
このオフセットは、read() により実際に読み取られたバイト数だけ自動的に増加する。

ファイルの終端に達した場合、それ以上のデータは読み取られず、
関数は 0 を返す。
これは「EOF（End Of File）」を示す。

標準入力とパイプ
read() は、パイプ、FIFO、ソケットなどのファイルディスクリプタにも適用できる。
その場合、オフセットの概念は存在しない。
入力が存在しない場合、呼び出しは入力が到着するまでブロックされる。
ただし、ファイルが非ブロッキングモードで開かれている場合（O_NONBLOCK）、
データが利用できなければ read() は直ちに -1 を返し、errno に EAGAIN または EWOULDBLOCK を設定する。

部分読み込み
read() が要求したバイト数より少ないデータを返す場合がある。
これはエラーではなく、以下のような状況で発生する：

ファイル終端に到達した場合

ソケットやパイプで、一時的に利用可能なデータが少ない場合

割り込みやシグナルで呼び出しが中断された場合

メモリの配置
buf が指すメモリアドレスは、プロセスのアドレス空間内で有効であり、
書き込み可能でなければならない。
nbyte が 0 の場合、read() は何も読み取らず、エラーも発生せずに 0 を返す。

位置指定読み込み（pread）
pread() 関数は、read() と同様の動作を行うが、ファイルオフセットを変更しない点が異なる。
すなわち、呼び出しのたびに offset 引数で指定された位置から読み込みが行われる。

この関数はスレッドセーフであり、同一ファイルディスクリプタを複数スレッドが同時に使用しても、
ファイルオフセットの競合を回避できる。

pread() の呼び出しにおいて、ファイルがシーク可能でない（例：パイプ、ソケットなど）場合、
エラー ESPIPE が発生する。

入力端末での動作
入力端末（tty）から読み取る場合、read() は通常、1 行単位で入力が完了した時点でデータを返す。
端末のモード設定（canonical/non-canonical）によってこの動作は変化する。
端末制御の詳細は termios(3) を参照。

シグナルによる中断
read() がブロッキング状態のときにシグナルを受け取ると、
シグナルハンドラが設定されている場合には、システムコールは中断され、
errno に EINTR が設定される。
ハンドラに SA_RESTART フラグが設定されていれば、システムコールは自動的に再開される。

大きな読み込み要求
一部の実装では、read() が一度に処理可能なバイト数に制限がある。
POSIX.1 ではこの制限を明示的に定義していない。
実際に読み取られるサイズは、ファイルシステムやドライバに依存する。

返り値（RETURN VALUE）
read() および pread() は、正常終了時に実際に読み取られたバイト数を返す。
この値は 0 以上である。

ファイルの終端に達した場合、返り値は 0 となる。
エラーが発生した場合、-1 が返され、errno にエラー内容を示す値が設定される。

エラー（ERRORS）

read() および pread() は、次のいずれかの理由で失敗し、errno に対応する値を設定する。

エラー	説明
EAGAIN または EWOULDBLOCK	ファイルが非ブロッキングモードであり、読み取るデータが現在利用できない。
EBADF	ファイル記述子が有効でないか、読み込み用に開かれていない。
EFAULT	buf が指すアドレスがプロセスの有効なアドレス空間外にある。
EINTR	シグナルにより呼び出しが中断された。
EINVAL	fildes がシーク不能なファイルであり、pread() が使用された。
EIO	入出力エラー。ハードウェア障害やドライバエラーを含む。
EISDIR	指定されたファイルがディレクトリである。
ENOBUFS または ENOMEM	カーネルが内部バッファを確保できなかった。
ENOSPC	（特殊デバイスに対して）領域が不足している。
ESPIPE	pread() がパイプ、FIFO、ソケットに対して呼び出された。
属性（ATTRIBUTES）
インタフェース	属性	値
read(), pread()	スレッド安全性	MT-Safe
準拠（CONFORMING TO）

POSIX.1-2001, POSIX.1-2008。

注意（NOTES）

read() が部分的な読み込みを行っても、それはエラーではない。
常に返り値を確認し、必要に応じて再試行する必要がある。

パイプやソケットでは、受信データが到着するまでブロックされる。
非ブロッキングモードを使用する場合は、返り値が -1 かつ errno == EAGAIN の条件で再試行する。

pread() はファイルオフセットを変更しないため、複数スレッドによる安全なランダムアクセスを可能にする。

例（EXAMPLES）
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int fd;
    ssize_t nread;
    char buf[100];

    fd = open("file.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    nread = read(fd, buf, sizeof(buf)-1);
    if (nread == -1) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    buf[nread] = '\0';
    printf("Read %zd bytes: %s\n", nread, buf);

    close(fd);
    return 0;
}

関連項目（SEE ALSO）

open(2), close(2), write(2), lseek(2), readlink(2), select(2), errno(3)

コロフォン（COLOPHON）

このページは Linux man-pages プロジェクトの一部である。
プロジェクトの説明、バグ報告、および最新版の入手方法については：
https://www.kernel.org/doc/man-pages/

解説（実務的補足）

部分読み込みへの対応
read() は要求サイズより少ないバイト数しか返さないことがあるため、
ループで繰り返し読み取るのが安全。

非ブロッキング I/O
ソケット通信などでは O_NONBLOCK を指定し、返り値が -1 かつ errno == EAGAIN の場合は、
後で再試行する制御を行うのが一般的。

pread() の活用
並行アクセスを行う場合、スレッド間でファイルオフセットを共有せずに
個別の位置から読み込むために pread() を用いる。
データベースエンジンや並列ファイル処理などで広く使用される。

EOF 判定
返り値が 0 のときは EOF。これはエラーではなく、単に読み取るデータがないことを示す。