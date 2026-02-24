ERRNO(3) — Linux Programmer's Manual
名前

errno - 最後のエラー番号

書式
#include <errno.h>

説明

<errno.h> ヘッダーファイルは整数変数 errno を定義する。この変数は、システムコールや一部のライブラリ関数でエラーが発生した場合に設定され、何が問題であったかを示す。

errno

errno の値は、呼び出しの戻り値がエラーを示している場合（すなわち、ほとんどのシステムコールでは -1、ほとんどのライブラリ関数では -1 または NULL）にのみ意味を持つ。成功した関数は errno を変更してもよい。いかなるシステムコールやライブラリ関数も errno の値を 0 に設定することはない。

一部のシステムコールやライブラリ関数（例：getpriority(2)）では、-1 が成功時の正当な戻り値である。そのような場合、成功とエラーの戻りを区別するには、呼び出しの前に errno を 0 に設定し、呼び出し後、戻り値がエラーが発生した可能性を示すものであれば、errno が非 0 の値かどうかを確認する。

errno は ISO C 規格により、変更可能な int 型の左辺値（lvalue）であると定義され、明示的に宣言してはならない；errno はマクロである場合がある。errno はスレッドローカルであり、あるスレッドで設定しても他のスレッドの値には影響しない。

エラー番号と名前

有効なエラー番号はすべて正の数である。<errno.h> ヘッダーファイルは、errno に現れ得るそれぞれの可能なエラー番号に対応するシンボリック名を定義する。

POSIX.1 で規定されたすべてのエラー名は、EAGAIN と EWOULDBLOCK を例外として、互いに異なる値を持たなければならない。EAGAIN と EWOULDBLOCK は同じ値であってもよい。Linux では、これら 2 つはすべてのアーキテクチャで同じ値である。

各シンボリック名に対応するエラー番号は、UNIX 系システム間、さらには Linux の異なるアーキテクチャ間でも異なる。したがって、以下のエラー名の一覧の一部として数値値は含めない。perror(3) および strerror(3) 関数を用いて、これらの名前を対応するテキスト形式のエラーメッセージに変換できる。

特定の Linux システム上では、すべてのシンボリックエラー名と対応するエラー番号の一覧を errno(1) コマンド（moreutils パッケージの一部）を用いて取得できる。

$ errno -l
EPERM 1 Operation not permitted
ENOENT 2 No such file or directory
ESRCH 3 No such process
EINTR 4 Interrupted system call
EIO 5 Input/output error
...


errno(1) コマンドは、個別のエラー番号や名前の検索、およびエラー説明文字列を用いた検索にも利用できる。次の例のとおりである：

$ errno 2
ENOENT 2 No such file or directory
$ errno ESRCH
ESRCH 3 No such process
$ errno -s permission
EACCES 13 Permission denied

エラー名の一覧

以下のシンボリックエラー名の一覧では、各名称は次のように区別される：

POSIX.1-2001: 名称は POSIX.1-2001 により定義され、特段の記載がない限り、以降の POSIX.1 でも定義されている。

POSIX.1-2008: 名称は POSIX.1-2008 で定義され、以前の POSIX.1 規格には存在しなかった。

C99: 名称は C99 により定義されている。

以下は、Linux で定義されているシンボリックエラー名の一覧である。

E2BIG 引数リストが長すぎる (POSIX.1-2001).

EACCES 許可が拒否された (POSIX.1-2001).

EADDRINUSE アドレスは既に使用中 (POSIX.1-2001).

EADDRNOTAVAIL アドレスが利用できない (POSIX.1-2001).

EAFNOSUPPORT アドレスファミリがサポートされていない (POSIX.1-2001).

EAGAIN 資源が一時的に利用不可（EWOULDBLOCK と同じ値である場合がある）(POSIX.1-2001).

EALREADY 接続処理は既に進行中 (POSIX.1-2001).

EBADE 不正な交換（Invalid exchange）.

EBADF 不正なファイル記述子 (POSIX.1-2001).

EBADFD ファイル記述子の状態が不正.

EBADMSG 不正なメッセージ (POSIX.1-2001).

EBADR 不正な要求記述子.

EBADRQC 不正な要求コード.

EBADSLT 不正なスロット.

EBUSY デバイスまたは資源が使用中 (POSIX.1-2001).

ECANCELED 操作が取り消された (POSIX.1-2001).

ECHILD 子プロセスがない (POSIX.1-2001).

ECHRNG チャネル番号が範囲外.

ECOMM 送信で通信エラー.

ECONNABORTED 接続が中止された (POSIX.1-2001).

ECONNREFUSED 接続が拒否された (POSIX.1-2001).

ECONNRESET 接続がリセットされた (POSIX.1-2001).

EDEADLK 資源のデッドロックを回避した (POSIX.1-2001).

EDEADLOCK ほとんどのアーキテクチャでは EDEADLK の同義語。いくつかのアーキテクチャ（例：Linux MIPS, PowerPC, SPARC）では、別のエラーコード「ファイルロックのデッドロックエラー」。

EDESTADDRREQ 宛先アドレスが必要 (POSIX.1-2001).

EDOM 数学関数の引数が関数の定義域外 (POSIX.1, C99).

EDQUOT ディスククォータ超過 (POSIX.1-2001).

EEXIST ファイルが存在する (POSIX.1-2001).

EFAULT 不正なアドレス (POSIX.1-2001).

EFBIG ファイルが大きすぎる (POSIX.1-2001).

EHOSTDOWN ホストがダウンしている.

EHOSTUNREACH ホストに到達不能 (POSIX.1-2001).

EHWPOISON メモリページにハードウェアエラーがある.

EIDRM 識別子が削除された (POSIX.1-2001).

EILSEQ 不正または不完全なマルチバイト／ワイド文字 (POSIX.1, C99).

             ここに示されている文言は glibc のエラー記述であり、POSIX.1 ではこのエラーは
             “Illegal byte sequence” と記述されている。


EINPROGRESS 操作は進行中 (POSIX.1-2001).

EINTR 関数呼び出しが割り込まれた (POSIX.1-2001); signal(7) を参照。

EINVAL 無効な引数 (POSIX.1-2001).

EIO 入出力エラー (POSIX.1-2001).

EISCONN ソケットは接続済み (POSIX.1-2001).

EISDIR ディレクトリである (POSIX.1-2001).

EISNAM 名前付き型ファイルである.

EKEYEXPIRED 鍵の有効期限が切れている.

EKEYREJECTED 鍵がサービスにより拒否された.

EKEYREVOKED 鍵が失効している.

EL2HLT レベル 2 が停止した.

EL2NSYNC レベル 2 が非同期.

EL3HLT レベル 3 が停止した.

EL3RST レベル 3 がリセットされた.

ELIBACC 必要な共有ライブラリにアクセスできない.

ELIBBAD 破損した共有ライブラリへアクセス中.

ELIBMAX 共有ライブラリをリンクし過ぎようとしている.

ELIBSCN a.out の .lib セクションが破損.

ELIBEXEC 共有ライブラリを直接 exec できない.

ELNRANGE リンク番号が範囲外.

ELOOP シンボリックリンクの階層が多すぎる (POSIX.1-2001).

EMEDIUMTYPE 媒体の種類が誤っている.

EMFILE オープンファイルが多すぎる (POSIX.1-2001). しばしば getrlimit(2) で記述される
RLIMIT_NOFILE 資源制限の超過が原因。/proc/sys/fs/nr_open に指定された上限の
超過が原因のこともある。

EMLINK リンク数が多すぎる (POSIX.1-2001).

EMSGSIZE メッセージが長すぎる (POSIX.1-2001).

EMULTIHOP マルチホップが行われた (POSIX.1-2001).

ENAMETOOLONG ファイル名が長すぎる (POSIX.1-2001).

ENETDOWN ネットワークがダウンしている (POSIX.1-2001).

ENETRESET ネットワークにより接続が中止された (POSIX.1-2001).

ENETUNREACH ネットワーク到達不能 (POSIX.1-2001).

ENFILE システムでオープンされているファイルが多すぎる (POSIX.1-2001).
Linux では、おそらく /proc/sys/fs/file-max の上限に達した結果（proc(5) 参照）。

ENOANO アノードがない.

ENOBUFS バッファ空きがない (POSIX.1 (XSI STREAMS オプション)).

ENODATA STREAM ヘッドの読み出しキューにメッセージがない (POSIX.1-2001).

ENODEV そのようなデバイスはない (POSIX.1-2001).

ENOENT そのようなファイルまたはディレクトリはない (POSIX.1-2001).

             典型的には、指定したパス名が存在しない場合、あるいはパス名のディレクトリ
             接頭辞の構成要素の一つが存在しない場合、または指定したパス名が宙ぶらりんの
             シンボリックリンクである場合に、このエラーが発生する。


ENOEXEC 実行形式のエラー (POSIX.1-2001).

ENOKEY 必要な鍵が利用できない.

ENOLCK ロックが利用できない (POSIX.1-2001).

ENOLINK リンクが切断された (POSIX.1-2001).

ENOMEDIUM 媒体が見つからない.

ENOMEM 空きが足りない／メモリを確保できない (POSIX.1-2001).

ENOMSG 望む型のメッセージがない (POSIX.1-2001).

ENONET マシンがネットワーク上にない.

ENOPKG パッケージがインストールされていない.

ENOPROTOOPT プロトコルが利用できない (POSIX.1-2001).

ENOSPC デバイスに空き領域がない (POSIX.1-2001).

ENOSR STREAM 資源がない (POSIX.1 (XSI STREAMS オプション)).

ENOSTR STREAM ではない (POSIX.1 (XSI STREAMS オプション)).

ENOSYS 関数が実装されていない (POSIX.1-2001).

ENOTBLK ブロックデバイスが必要.

ENOTCONN ソケットが接続されていない (POSIX.1-2001).

ENOTDIR ディレクトリではない (POSIX.1-2001).

ENOTEMPTY ディレクトリが空でない (POSIX.1-2001).

ENOTRECOVERABLE 状態が回復不能 (POSIX.1-2008).

ENOTSOCK ソケットではない (POSIX.1-2001).

ENOTSUP 操作はサポートされていない (POSIX.1-2001).

ENOTTY 不適切な I/O 制御操作 (POSIX.1-2001).

ENOTUNIQ ネットワーク上で名前が一意でない.

ENXIO そのようなデバイスまたはアドレスはない (POSIX.1-2001).

EOPNOTSUPP ソケット上でサポートされていない操作 (POSIX.1-2001).

             （ENOTSUP と EOPNOTSUPP は Linux では同じ値だが、POSIX.1 によれば
             これらのエラー値は区別されるべきである。）


EOVERFLOW 値がデータ型に格納するには大きすぎる (POSIX.1-2001).

EOWNERDEAD 所有者が死亡 (POSIX.1-2008).

EPERM 操作は許可されていない (POSIX.1-2001).

EPFNOSUPPORT プロトコルファミリがサポートされていない.

EPIPE パイプが破損 (POSIX.1-2001).

EPROTO プロトコルエラー (POSIX.1-2001).

EPROTONOSUPPORT プロトコルがサポートされていない (POSIX.1-2001).

EPROTOTYPE ソケットに対してプロトコルの型が不適切 (POSIX.1-2001).

ERANGE 結果が大きすぎる (POSIX.1, C99).

EREMCHG リモートアドレスが変更された.

EREMOTE オブジェクトはリモート.

EREMOTEIO リモート I/O エラー.

ERESTART 割り込まれたシステムコールは再始動すべき.

ERFKILL RF-kill により操作が不可能.

EROFS 読み出し専用ファイルシステム (POSIX.1-2001).

ESHUTDOWN 転送終端がシャットダウン後で送信できない.

ESPIPE 無効なシーク (POSIX.1-2001).

ESOCKTNOSUPPORT ソケット型がサポートされていない.

ESRCH そのようなプロセスはない (POSIX.1-2001).

ESTALE 不整合なファイルハンドル (POSIX.1-2001).

             このエラーは NFS や他のファイルシステムで発生することがある。


ESTRPIPE ストリームパイプのエラー.

ETIME タイマ期限切れ (POSIX.1 (XSI STREAMS オプション)).

             （POSIX.1 は「STREAM ioctl(2) タイムアウト」と記す。）


ETIMEDOUT 接続タイムアウト (POSIX.1-2001).

ETOOMANYREFS 参照が多すぎる：splice できない。

ETXTBSY テキストファイルがビジー (POSIX.1-2001).

EUCLEAN 構造体のクリーンアップが必要.

EUNATCH プロトコルドライバが接続されていない.

EUSERS ユーザが多すぎる.

EWOULDBLOCK 操作はブロックする（EAGAIN と同じ値である場合がある）(POSIX.1-2001).

EXDEV 不適切なリンク (POSIX.1-2001).

EXFULL 交換領域がいっぱい（Exchange full）.

注記

次のようにするのはよくある誤りである：

if (somecall() == -1) {
    printf("somecall() failed\n");
    if (errno == ...) { ... }
}


この場合、somecall() から戻った時点の errno の値を保持している必要はもはやない（すなわち、printf(3) によって変更されている可能性がある）。ライブラリ呼び出しの間で errno の値を保持すべきであれば、保存しなければならない：

if (somecall() == -1) {
    int errsv = errno;
    printf("somecall() failed\n");
    if (errsv == ...) { ... }
}


POSIX スレッド API はエラー時に errno を設定しないことに注意する。代わりに、失敗時にはエラー番号を関数の戻り値として返す。これらのエラー番号は、他の API において errno に返されるエラー番号と同じ意味を持つ。

古いシステムの中には、<errno.h> が存在しなかったり errno を宣言していなかったりしたものがあり、そのため extern int errno のように手動で errno を宣言する必要があった。しかし、これは行ってはならない。必要がなくなってから久しく、現代の C ライブラリのバージョンでは問題を引き起こす。

関連項目

errno(1), err(3), error(3), perror(3), strerror(3)

コロフォン

このページは Linux man-pages プロジェクト リリース 5.10 の一部である。プロジェクトの説明、バグ報告、ならびにこのページの最新版は以下を参照：
https://www.kernel.org/doc/man-pages/

                          2020-11-01                      ERRNO(3)

解説

errno は戻り値がエラーを示した直後に読むのが鉄則。ログ出力等で別関数を挟む場合は int saved = errno; で保存してから処理する。

EAGAIN/EWOULDBLOCK は同値の実装もあるため、ポータブルな分岐では両方を等価に扱う。

Pthreads など**errno 非依存の API** では、戻り値のエラー番号をそのまま strerror_r() 等で処理する。