PRINTF(3) — Linux Programmer’s Manual
名前（NAME）

printf, fprintf, sprintf, snprintf, vprintf, vfprintf, vsprintf, vsnprintf —
書式付き出力関数

書式（SYNOPSIS）
#include <stdio.h>

int fprintf(FILE *stream, const char *format, ...);
int printf(const char *format, ...);
int sprintf(char *str, const char *format, ...);
int snprintf(char *str, size_t size, const char *format, ...);

#include <stdarg.h>

int vfprintf(FILE *stream, const char *format, va_list ap);
int vprintf(const char *format, va_list ap);
int vsprintf(char *str, const char *format, va_list ap);
int vsnprintf(char *str, size_t size, const char *format, va_list ap);

説明（DESCRIPTION）

これらの関数は、フォーマット指定文字列 format に従って出力を生成する。
関数間の違いは、出力先と引数の受け渡し方式である。

関数	出力先
fprintf()	ファイルストリーム stream に出力
printf()	標準出力に出力
sprintf()	文字配列 str に出力（終端 '\0' を自動追加）
snprintf()	同上だが size バイトを上限として出力
vfprintf()	可変引数リスト va_list を取る
vprintf()	同上、出力先は標準出力
vsprintf()	可変引数 va_list を使用し文字配列に出力
vsnprintf()	同上、出力長に size 制限あり
フォーマット文字列の形式（Format of the format string）

format 文字列は通常の文字列と、% で始まる変換指定子（conversion specification）を含む。
変換指定子は次の一般形式を取る。

%[flags][width][.precision][length]specifier


各部分の意味は以下の通りである。

flags — 出力の配置や符号、ゼロ埋め、代替形式などを制御する。

width — 最小フィールド幅を指定する整数値または *。

precision — 小数点以下桁数や文字列長上限などを指定。

length — 引数の型修飾子（例： h, l, ll など）。

specifier — 実際の変換対象（整数、浮動小数点、文字列など）。

フラグ文字（Flag characters）

% に続けて指定できるフラグ文字は、出力の配置・表示方法を制御する。

フラグ	意味
-	出力をフィールド内で左寄せにする（既定は右寄せ）
+	正数にも明示的に符号（+ または -）を付ける
（空白）	正数の前に空白を挿入（+ フラグが優先される）
#	代替形式を使用する（例：0x を付与）
0	数値の左側をゼロで埋める（- フラグ指定時は無効）
幅指定（Field width）

出力の最小フィールド幅を指定する整数。
幅が実際の出力より大きい場合、空白またはゼロで埋められる。

幅に * を指定した場合、次の引数から値を取得する。
例：

printf("%*d", 5, 42);  /* 出力は "   42" */

精度指定（Precision）

. に続けて整数を指定する。意味は変換指定子により異なる：

指定対象	精度の意味
整数	出力の最小桁数（不足分はゼロ埋め）
浮動小数点	小数点以下の桁数
文字列	最大出力文字数
g / G	有効桁数全体を指定

* により精度値を引数から取得することもできる。
例：printf("%.*f", 3, 1.23456); → 1.235

長さ修飾子（Length modifiers）

引数の型を修飾する。主な指定は次の通り：

修飾子	意味
hh	signed char または unsigned char として扱う
h	short または unsigned short
l	long または unsigned long
ll	long long または unsigned long long
j	intmax_t または uintmax_t
z	size_t
t	ptrdiff_t
L	long double（浮動小数点型）
変換指定子（Conversion specifiers）
指定子	意味
%d, %i	符号付き 10 進整数を出力
%o	符号なし 8 進整数を出力
%u	符号なし 10 進整数を出力
%x, %X	符号なし 16 進整数を出力（小文字／大文字）
%f, %F	固定小数点形式で出力
%e, %E	指数表記で出力
%g, %G	%f または %e を自動選択
%a, %A	16 進浮動小数点形式（C99）
%c	単一文字を出力
%s	文字列を出力
%p	ポインタ値を実装依存の形式で出力
%n	これまでに出力された文字数を対応する int * に格納
%%	リテラル % を出力

ChatGPT:

了解しました。
では、man_printf.txt の Part 3（RETURN VALUE〜COLOPHON＋解説） を、
原文構造を完全保持して Linux JM 準拠の文体で逐語翻訳します。

戻り値（RETURN VALUE）

正常終了時、これらの関数は 実際に出力された文字数（終端のヌル文字を除く）を返す。

エラーが発生した場合、負の値が返される。
errno の内容は出力ストリームの状態に依存する（通常 EPIPE, ENOMEM など）。

snprintf() および vsnprintf() がバッファサイズより大きい出力を要求された場合、
結果の文字列を切り詰めるが、戻り値には「出力に必要だった合計文字数」が格納される（終端のヌル文字を含まない）。
したがって、戻り値が size 以上の場合、出力が切り詰められたことを意味する。

エラー（ERRORS）
エラー	意味
EILSEQ	無効なマルチバイト文字シーケンス（ロケール依存）
ENOMEM	内部バッファの確保に失敗した
EPIPE	出力先パイプが切断されている
EOVERFLOW	出力サイズが表現範囲を超えた
属性（ATTRIBUTES）
インタフェース	属性	値
printf() 系列	スレッド安全性	MT-Safe locale
準拠（CONFORMING TO）

C89, C99, POSIX.1-2001, POSIX.1-2008。
snprintf() および vsnprintf() は C99 で追加された。

注意（NOTES）

printf() ファミリのすべての関数はバッファリングされた I/O を使用する。
出力を即座に反映させたい場合は fflush(stdout) を呼び出す。

snprintf() は、バッファサイズを超過する書き込みを防止できる安全な代替として推奨される。

sprintf() はサイズ指定を行わないため、バッファオーバーフローを引き起こす可能性がある。
したがって、安全なコードでは使用しないこと。

精度や幅に * を使用する際は、対応する引数が int 型である必要がある。

例（EXAMPLES）
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char buf[128];
    int x = 42;

    snprintf(buf, sizeof(buf), "Value: %d\n", x);
    printf("%s", buf);

    return 0;
}


出力：

Value: 42

関連項目（SEE ALSO）

printf(1), fprintf(3), sprintf(3), snprintf(3),
strerror(3), setlocale(3), write(2)

コロフォン（COLOPHON）

このページは Linux man-pages プロジェクトの一部である。
プロジェクトの説明、バグ報告、および最新版の入手方法については：
https://www.kernel.org/doc/man-pages/

解説（実務的補足）

安全なフォーマット出力
バッファサイズを指定できる snprintf() / vsnprintf() を使用することで、
スタック破壊やメモリ破壊を防止できる。

ロケールの影響
浮動小数点変換（%f, %g など）では小数点文字が LC_NUMERIC に依存する。
多言語環境では出力形式の変化に注意。

出力バッファリング
標準出力は通常行バッファリングされるため、パイプやファイルへのリダイレクト時には
明示的に fflush(stdout) を呼び出すのが安全。

可変長引数の扱い
関数ライブラリ内で可変引数を渡す場合、va_start, va_copy, va_end とともに
vfprintf() / vsnprintf() を使用すると安全である。