SYSTEM_DATA_TYPES(7) — Linux Programmer’s Manual
名前（NAME）

system_data_types — 各種システムで使用される標準的なデータ型の概要

概要（SYNOPSIS）

このページでは、POSIX、ISO C、BSD、および System V 系システムで
広く使用される共通データ型の意味を概説する。
これらの型は通常、標準ヘッダファイルに定義されている。

説明（DESCRIPTION）

このマニュアルページでは、UNIX 系システムプログラミングで登場する
標準データ型を簡潔にまとめる。
これらは <sys/types.h>、<stddef.h>、<stdint.h> などの
標準ヘッダに含まれることが多い。

以下の型の定義は実装依存であるが、一般的な用途と範囲は共通している。

aiocb

非同期 I/O 操作を制御する構造体型。
<aio.h> で定義され、aio_read(), aio_write() などの関数で使用される。

blkcnt_t

ブロック数を表す符号付き整数型。
ファイルサイズやディスク使用量など、ブロック単位の量を示すために用いられる。

blksize_t

ファイルシステムのブロックサイズを表す符号付き整数型。
st_blksize フィールドなどで使用される。

clock_t

プロセスの CPU 使用時間を表す型。
clock() 関数により取得され、単位は実装依存（通常はクロックティック数）。

clockid_t

POSIX タイマーで使用されるクロック識別子型。
clock_gettime(), clock_settime() などで利用される。

dev_t

デバイス番号を表す符号なし整数型。
主デバイス番号（major number）と副デバイス番号（minor number）を
符号化して格納する。

div_t

整数の除算結果を格納する構造体型。
div() 関数によって返され、quot（商）と rem（余り）の2つのフィールドを持つ。

double_t, float_t

C99 標準の <math.h> に定義される浮動小数点演算用の内部型。
FLT_EVAL_METHOD に応じて、float または double として定義される。

fd_set

ファイルディスクリプタ集合を表す構造体。
select() システムコールで監視対象ファイルディスクリプタを指定する際に使用される。

fpos_t

ファイルストリーム内での位置を表す型。
fgetpos() および fsetpos() 関数で使用される。
単純なオフセットではなく、実装依存の構造体として定義されることが多い。

gid_t

グループ ID を表す型。
getgid(), setgid(), getgroups() などの関数で使用される。
通常は符号なし整数型。

id_t

プロセス、セッション、グループなどの識別番号を一般化して表す型。
waitid() や msgctl() などの関数で使用される。

ino_t

i-node 番号を表す符号なし整数型。
ファイルシステム内でファイルを一意に識別する。
stat(2) 構造体の st_ino フィールドで使用される。

key_t

System V IPC（メッセージキュー、セマフォ、共有メモリ）で
IPC オブジェクトを識別するためのキー型。
ftok() 関数により生成される。

mode_t

ファイルのアクセスモードや型を表す型。
chmod(), mkdir(), open() などで使用され、
S_IRUSR, S_IWUSR, S_IFREG 等のビットマスク値と組み合わせて使う。

nlink_t

ファイルのハードリンク数を表す符号なし整数型。
stat(2) 構造体の st_nlink フィールドに格納される。

off_t

ファイル内オフセット（位置）を表す符号付き整数型。
lseek(), pread(), mmap() などで使用される。
POSIX では 64 ビット（off64_t）の拡張型も定義されている。

pid_t

プロセス ID を表す符号付き整数型。
getpid(), fork(), waitpid(), kill() などの関数で使用される。

pthread_t

POSIX スレッド識別子型。
pthread_create() により生成され、スレッドを一意に識別する。

ptrdiff_t

ポインタ差分（2つのポインタ間の距離）を表す符号付き整数型。
<stddef.h> に定義され、配列インデックス計算などに使用される。

rlim_t

リソース制限値を表す符号なし整数型。
getrlimit() および setrlimit() 関数で使用される。

sa_family_t

ソケットアドレス構造体（例：struct sockaddr）内で
アドレスファミリ（AF_INET, AF_UNIX など）を示すための型。

sig_atomic_t

シグナルハンドラ内で安全にアクセスできる整数型。
通常はアトミックな読み書きが保証される整数として定義される。

sigset_t

シグナル集合を表す型。
sigprocmask(), sigpending(), sigaction() などで使用される。

size_t

オブジェクトのサイズやメモリブロックの長さを表す符号なし整数型。
sizeof 演算子の返り値型としても用いられる。

ssize_t

size_t の符号付き版で、読み書き操作の戻り値型として使用される。
read(), write() などが返す値の型である。

suseconds_t

マイクロ秒単位の時間を表す符号付き整数型。
struct timeval 構造体のフィールドとして用いられる。

time_t

時間を表す整数型（UNIX Epoch からの経過秒数）。
time(), ctime(), difftime() などで使用される。

timer_t

POSIX タイマーを識別する型。
timer_create(), timer_settime(), timer_delete() で使用される。

uid_t

ユーザ ID を表す型。
getuid(), setuid(), geteuid() などで使用される。

void *

汎用ポインタ型。
任意のデータ型のアドレスを格納できる。
malloc(), realloc(), memcpy() などで広く使用される。

注記（NOTES）

各型の具体的なビット幅や符号有無はアーキテクチャや実装に依存する。
POSIX 標準では意味的な保証のみが与えられる。

64ビットシステムでは、off_t, size_t, time_t などが 64 ビット幅で定義されている場合が多い。

<stdint.h> には固定幅整数型（int32_t, uint64_t など）も定義されており、
バイナリ互換性が必要な場面で推奨される。

関連項目（SEE ALSO）

types.h(0P), unistd.h(0P), stdint.h(0P), stddef.h(0P),
aio(7), signal(7), time(7)

コロフォン（COLOPHON）

このページは Linux man-pages プロジェクトの一部である。
プロジェクトの説明、バグ報告、および最新版の入手方法については：
https://www.kernel.org/doc/man-pages/

解説（実務的補足）

符号とビット幅の確認
開発環境で sizeof() を使って型サイズを確認し、
アーキテクチャ依存の差異を明示的に把握することが重要である。

ポータビリティ（移植性）
型の意味を前提として使用し、ビット幅に依存したコードを避ける。
固定長整数を使う場合は <stdint.h> を利用する。

64ビット対応
大規模ファイル操作では off64_t などの拡張型を使用する。
_FILE_OFFSET_BITS=64 を定義してビルドすることで、
既存の off_t を自動的に 64 ビット化できる。

シグナルとアトミック型
シグナルハンドラで共有データを扱う際は、volatile sig_atomic_t を使用して
中断安全な操作を保証する。

POSIX タイマーと時間精度
timer_t や clockid_t を使うタイマー API はリアルタイム性の高いアプリケーションで重要であり、
高精度な時刻制御を行う場合に利用する。