FABS(3) — Linux Programmer’s Manual
名前（NAME）

fabs, fabsf, fabsl — 浮動小数点数の絶対値を求める

書式（SYNOPSIS）
#include <math.h>

double fabs(double x);
float fabsf(float x);
long double fabsl(long double x);


リンク時に -lm を指定すること。

glibc の Feature Test Macro 要件（Feature Test Macro Requirements for glibc）
関数	要件
fabsf(), fabsl()	_ISOC99_SOURCE または _POSIX_C_SOURCE >= 200112L または _DEFAULT_SOURCE（glibc 2.19 以降）、または _BSD_SOURCE / _SVID_SOURCE（glibc 2.19 以前）
説明（DESCRIPTION）

これらの関数は、浮動小数点数 x の絶対値を返す。

戻り値（RETURN VALUE）

これらの関数は、x の絶対値を返す。

x が NaN（非数）の場合、NaN が返される。

x が -0 の場合、+0 が返される。

x が -∞ または +∞ の場合、+∞ が返される。

エラー（ERRORS）

エラーは発生しない。

属性（ATTRIBUTES）
インタフェース	属性	値
fabs(), fabsf(), fabsl()	スレッド安全性	MT-Safe
準拠（CONFORMING TO）

C99, POSIX.1-2001, POSIX.1-2008。
double を返すバリアントは SVr4, 4.3BSD, C89 にも準拠している。

関連項目（SEE ALSO）

abs(3), cabs(3), ceil(3), floor(3), labs(3), rint(3)

コロフォン（COLOPHON）

このページは Linux man-pages プロジェクト リリース 5.10 の一部である。
プロジェクトの説明、バグ報告、および最新版の入手方法については：
https://www.kernel.org/doc/man-pages/

解説（実務的補足）

浮動小数点環境でのゼロの扱い
IEEE 754 に準拠した実装では、-0.0 と +0.0 は区別されるが、
fabs() は常に正のゼロ（+0.0）を返す。

NaN の扱い
fabs() は NaN に対して副作用を持たず、入力が NaN なら NaN をそのまま返す。
これはエラーではなく、IEEE 754 に基づく正常動作である。

精度と型選択

fabs() は double 型を処理。

fabsf() は float 型を処理（単精度）。

fabsl() は long double 型を処理（拡張精度）。
型に応じて関数を使い分けることで不要な型変換を避け、性能を最適化できる。

パフォーマンス
多くのアーキテクチャでは、fabs() はビットマスク操作または
ハードウェア命令で実装されるため、分岐や演算を伴わず高速である。