FPRINTF(3) — Linux Programmer's Manual
名前

fprintf, printf, sprintf, snprintf, vprintf, vfprintf, vsprintf, vsnprintf — 書式付き出力関数群

書式
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

説明

これらの関数群は、printf(3) ファミリとして知られており、フォーマット指定文字列 format に基づいて書式化した出力を生成する。
それぞれの関数は、最初の引数として出力先を異にする：

関数	出力先
fprintf()	stream に指定されたファイルストリーム
printf()	標準出力（stdout）
sprintf()	str が指す文字配列
snprintf()	str が指す文字配列（ただし最大 size バイトまで）

同様に、vfprintf(), vprintf(), vsprintf(), vsnprintf() は、可変引数リストを va_list 型で受け取るバリアントである。

フォーマット指定子

format 文字列には、通常の文字列と、% で始まる「変換指定子（conversion specification）」を含むことができる。
変換指定子は次の形式を取る：

%[flags][width][.precision][length]specifier


各要素の意味は以下の通りである：

フラグ（flags）
フラグ	意味
-	左寄せ
+	常に符号を出力
（空白）	正数の場合に空白を出力
#	代替形式（例：0x 付き16進など）
0	幅指定時にゼロ埋め
幅（width）

出力フィールドの最小幅。
整数値で指定するか、または * により引数から取得する。

精度（precision）

. に続けて整数値を指定するか、* により引数から取得する。
数値の場合は小数点以下桁数、文字列の場合は最大出力長を指定する。

長さ修飾子（length）
修飾子	意味
hh	char 型として扱う
h	short 型
l	long 型
ll	long long 型
j	intmax_t 型
z	size_t 型
t	ptrdiff_t 型
L	long double 型
変換指定子（specifier）
指定子	出力対象と形式
d, i	符号付き10進整数
o	符号なし8進整数
u	符号なし10進整数
x, X	符号なし16進整数（小文字／大文字）
f, F	固定小数点表示
e, E	指数表示
g, G	自動選択（f または e）
a, A	16進浮動小数点
c	単一文字
s	文字列
p	ポインタ（実装定義の形式）
%	リテラル %