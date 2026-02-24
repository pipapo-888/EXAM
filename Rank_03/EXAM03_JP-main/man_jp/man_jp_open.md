OPEN(3POSIX) — POSIX Programmer's Manual
プロローグ（PROLOG）
このマニュアルページは、POSIX Programmer’s Manual の一部であり、
POSIX 標準に準拠するシステムインタフェースを記述している。

名前（NAME）
open, openat — ファイルを開く、または作成する

書式（SYNOPSIS）
c
￼コードをコピーする
#include <fcntl.h>

int open(const char *path, int oflag, ...);
int openat(int fd, const char *path, int oflag, ...);
説明（DESCRIPTION）
open() 関数は、パス名 path により指定されたファイルを開くか、または O_CREAT フラグが指定されている場合には作成する。

返されるファイル記述子は、ファイルディスクリプタ表の最小の未使用エントリを使用して割り当てられる。
このファイルディスクリプタは、read(), write(), fcntl(), ioctl(), close() などの他の関数で使用される。

oflag 引数
oflag 引数は、以下のビット値をビット単位 OR 演算で指定する。
これらの値は <fcntl.h> に定義されている。

アクセスモード指定
定数	意味
O_RDONLY	読み取り専用で開く
O_WRONLY	書き込み専用で開く
O_RDWR	読み書き両用で開く
￼
アクセスモードは上記のいずれか一つだけが指定されなければならない。

制御フラグ
定数	説明
O_APPEND	書き込みは常にファイルの末尾に追加される
O_CLOEXEC	新しいファイルディスクリプタに FD_CLOEXEC フラグを設定する
O_CREAT	ファイルが存在しない場合に新規作成する（第3引数 mode が必要）
O_DIRECTORY	ディレクトリ以外のファイルに対してはエラーを返す
O_EXCL	O_CREAT と併用された場合、既存のファイルが存在するとエラー
O_NOCTTY	端末デバイスを制御端末として割り当てない
O_NOFOLLOW	シンボリックリンクを辿らない（リンクそのものを開く）
O_NONBLOCK	非ブロッキングモードで開く（O_NDELAY と同義）
O_SYNC	書き込み操作を同期的に行う（データおよびメタデータをディスクへ）
O_TRUNC	ファイルをゼロ長に切り詰める（既存ファイルに対して）
O_TMPFILE	名前を持たない一時ファイルとして作成する（Linux拡張）
O_PATH	ファイルを開かず、パス名解決のみを行う（Linux拡張）
￼
ファイルの作成
O_CREAT が指定され、ファイルが存在しない場合、
関数は新しいファイルを作成し、そのアクセスモードを mode 引数により設定する。

この mode 引数は umask(2) によりマスクされる。
つまり、実際のアクセス権は：

bash
￼コードをコピーする
mode & ~umask
によって決定される。

ディレクトリファイルのオープン

O_DIRECTORY が指定された場合、path がディレクトリ以外であればエラー ENOTDIR が発生する。
このフラグは、open() が誤って通常ファイルやシンボリックリンクを開くことを防ぐために用いられる。

シンボリックリンク

O_NOFOLLOW が指定されている場合、
path がシンボリックリンクを指していればエラー ELOOP を返す。
このフラグを指定しない場合、リンク先を通常どおり解決する。

ファイルの切り詰め

O_TRUNC が指定され、かつファイルが既に存在し、
書き込み許可モード（O_WRONLY または O_RDWR）で開かれた場合、
ファイルの内容は長さ 0 に切り詰められる。

非ブロッキングモード

O_NONBLOCK フラグを指定すると、操作がブロックされずに即時に戻る。
この動作は特にパイプ、FIFO、ソケットなどで意味を持つ。

同期書き込み

O_SYNC フラグが指定された場合、書き込み操作はデータおよびメタデータが
物理ストレージに書き込まれるまで完了しない。
これは信頼性を高めるが、パフォーマンスが低下する。

openat() 関数

openat() は、open() に似ているが、
path が相対パスの場合、その解決基準となるディレクトリを fd で指定する点が異なる。

fd の値	意味
有効なディレクトリディスクリプタ	そのディレクトリを基準として path を解決
AT_FDCWD	現在の作業ディレクトリを基準として解決

path が絶対パスである場合、fd は無視される。

ファイル記述子の継承と FD_CLOEXEC

ファイルディスクリプタには、プロセスの exec() 呼び出し時に継承されるかどうかを制御するフラグ FD_CLOEXEC がある。
O_CLOEXEC フラグを指定して open() または openat() を呼び出した場合、
ファイルディスクリプタは exec() 実行時に自動的に閉じられる。

一時ファイルの作成

O_TMPFILE は Linux 固有の拡張であり、
一時的な匿名ファイルを作成する。
このファイルには名前が付けられず、リンクされるまでは他のプロセスから参照できない。
このフラグを使用するには、O_RDWR または O_WRONLY を指定し、
さらに open() の path 引数としてディレクトリ名を渡す必要がある。

返り値（RETURN VALUE）

成功時、open() および openat() は新しいファイルディスクリプタ（0 以上の整数値）を返す。
エラーが発生した場合は -1 を返し、errno にエラーの原因を示す値を設定する。

エラー（ERRORS）

open() および openat() は、以下のいずれかの理由で失敗し、errno に対応する値を設定する。

エラー	説明
EACCES	指定したファイルまたはディレクトリへのアクセス権がない。
EEXIST	O_CREAT と O_EXCL が指定されたが、ファイルがすでに存在する。
EFAULT	path が指すメモリアドレスが有効なアドレス空間外である。
EINTR	シグナルにより呼び出しが中断された。
EISDIR	O_WRONLY または O_RDWR で開こうとした対象がディレクトリである。
ELOOP	シンボリックリンクの解決中にループを検出、または O_NOFOLLOW 指定時にリンクに遭遇した。
EMFILE	プロセスでオープン可能なファイル記述子の数上限を超えた。
ENAMETOOLONG	path が許可される最大長を超えている。
ENFILE	システム全体でオープン可能なファイル数の上限を超えた。
ENOENT	指定されたファイルまたはディレクトリが存在しない。
ENOMEM	カーネル空間で必要なメモリを確保できなかった。
ENOSPC	O_CREAT 指定時に新規作成しようとしたが、デバイスに空き容量がない。
ENOTDIR	パス中の構成要素のいずれかがディレクトリではない。
ENXIO	デバイスまたはアドレスが存在しない。
EOPNOTSUPP	要求された操作がサポートされていない。
EOVERFLOW	ファイルサイズが表現範囲を超えている。
EPERM	操作が許可されていない（特権が必要）。
EROFS	読み出し専用ファイルシステム上で書き込みを試みた。
ETXTBSY	実行中のプログラムファイルを開こうとした。
属性（ATTRIBUTES）
インタフェース	属性	値
open(), openat()	スレッド安全性	MT-Safe
準拠（CONFORMING TO）

POSIX.1-2001, POSIX.1-2008。

注意（NOTES）

O_CREAT を使用する場合、第3引数としてモード（mode_t 型）を必ず指定する必要がある。

O_TMPFILE および O_PATH は Linux 固有の拡張であり、他の UNIX 実装ではサポートされない場合がある。

O_NONBLOCK は、非ブロッキング I/O が意味を持たないファイルタイプでは無視される。

openat() は、open() の相対パス解決を拡張したものであり、ディレクトリファイルディスクリプタを利用することで、安全なパス操作を実現する。

例（EXAMPLES）
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int fd = open("example.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    const char *text = "Hello, world!\n";
    write(fd, text, 14);
    close(fd);
    return 0;
}

関連項目（SEE ALSO）

close(2), read(2), write(2), fcntl(2), creat(2), umask(2), stat(2), errno(3)

コロフォン（COLOPHON）

このページは Linux man-pages プロジェクトの一部である。
プロジェクトの説明、バグ報告、および最新版の入手方法については：
https://www.kernel.org/doc/man-pages/

解説（実務的補足）

openat() の利点
ディレクトリファイルディスクリプタを基準に相対パスを解決できるため、
chdir() による作業ディレクトリ変更を行わずに安全なファイル操作を実現できる。
特にサンドボックス環境やファイル探索の安全性向上に有用。

O_CLOEXEC の使用
マルチスレッド環境で fork() 後に exec() を行う場合、
不要なファイルディスクリプタの継承を防ぐため、
O_CLOEXEC を常に使用することが推奨される。

O_SYNC の注意点
同期書き込みはデータ信頼性を高めるが、I/O レイテンシが大幅に増加するため、
頻繁な更新処理では適切に選択する必要がある。

umask の影響
新規作成ファイルのモードは、指定した mode 値から umask でマスクされた結果となる。
セキュリティ上の理由から、必要に応じて umask(2) を調整すること。