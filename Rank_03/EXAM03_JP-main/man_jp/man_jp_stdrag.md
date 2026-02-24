STDARG(3) — Linux Programmer’s Manual
名前（NAME）

stdarg, va_start, va_arg, va_end, va_copy — 可変長引数リストを扱う

書式（SYNOPSIS）
#include <stdarg.h>

void va_start(va_list ap, last);
type va_arg(va_list ap, type);
void va_end(va_list ap);
void va_copy(va_list dest, va_list src);

説明（DESCRIPTION）

関数は、異なる型および個数の引数を取ることができる。
ヘッダファイル <stdarg.h> は、型 va_list を宣言し、
可変引数リストを操作するための 3 つ（または 4 つ）のマクロを定義している。

これらのマクロを使用することで、呼び出し側の引数の数や型が不明な場合でも、
呼び出された関数がそれらを順に取り出せるようになる。

呼び出された関数は、型 va_list のオブジェクトを宣言し、
va_start(), va_arg(), va_end() マクロを用いて操作する。

va_start()

va_start() マクロは、後続の va_arg() および va_end() のために
引数リスト ap を初期化する。
このマクロは最初に呼び出さなければならない。

引数 last は、可変引数リストの直前の引数名を指定する。
つまり、呼び出し側で型が既知である最後の引数である。

この引数のアドレスが va_start() 内部で使用されることがあるため、
last は レジスタ変数、関数、配列型 として宣言してはならない。

va_arg()

va_arg() マクロは、呼び出しの次の引数の値を、指定された type として展開する。
ap は、va_start() によって初期化された va_list 型の変数である。
va_arg() を呼び出すたびに、ap は次の引数を指すように更新される。

type は引数の型名であり、指定した型に対するポインタ型（type *）を
単に * を付けて得られる形式でなければならない。

最初の va_arg() 呼び出しは va_start() 呼び出しの直後に実行され、
last の次の引数を返す。
その後の呼び出しでは、残りの引数を順に返す。

もし次の引数が存在しない場合、または type が実際の引数型と互換性がない場合
（デフォルト引数昇格規則に従っていない場合）、動作は未定義であり、
ランダムなエラーが発生する。

ap が別の関数に渡され、その関数が va_arg(ap, type) を呼び出した場合、
その関数の戻り後の ap の値は未定義となる。

va_end()

すべての va_start() 呼び出しには、対応する va_end() 呼び出しが
同一関数内で必要である。
va_end(ap) 呼び出し後、変数 ap は未定義となる。

可変引数リストを複数回走査することも可能であり、
各走査は va_start() と va_end() で囲まれていなければならない。

va_end() はマクロまたは関数として実装される。

va_copy()

va_copy() マクロは、すでに初期化済みの可変引数リスト src を dest にコピーする。
動作は、va_start() を dest に適用した後に src の現在位置まで
同数の va_arg() を実行したのと同じ結果となる。

多くの実装では、va_list は可変長関数のスタックフレームを指すポインタとして定義される。
このような環境では次のような代入が動作するように見える：

va_list aq = ap;


しかし、一部のシステムでは va_list が「ポインタ配列（長さ1）」として実装されており、
次のように書く必要がある：

va_list aq;
*aq = *ap;


さらに、レジスタに引数が渡されるアーキテクチャでは、
va_start() がメモリを動的に確保し、引数を保存する必要がある場合がある。
そのため、va_end() によってこのメモリを解放できるようにするため、
C99 では va_copy() マクロが導入された。
これにより、単純な代入の代わりに次のように書ける：

va_list aq;
va_copy(aq, ap);
...
va_end(aq);


va_copy() の呼び出しごとに、同一関数内で対応する va_end() 呼び出しが必要である。
一部のシステムでは va_copy() が提供されておらず、
代わりに __va_copy という名前で実装されている場合がある。

属性（ATTRIBUTES）
インタフェース	属性	値
va_start(), va_end(), va_copy()	スレッド安全性	MT-Safe
va_arg()	スレッド安全性	MT-Safe race:ap
準拠（CONFORMING TO）

va_start(), va_arg(), va_end() マクロは C89 に準拠。
C99 では va_copy() マクロが追加された。

バグ（BUGS）

従来の <varargs.h> に基づくマクロと異なり、<stdarg.h> のマクロでは
「固定引数を持たない関数」を宣言することはできない。
この制限により、古い varargs コードの stdarg への移行時に
修正作業が必要になる場合がある。

また、可変引数関数が受け取ったすべての引数を別の va_list を取る関数
（たとえば vfprintf(3)）へそのまま渡したい場合にも困難が生じる。

例（EXAMPLES）

以下の関数 foo() は、フォーマット文字列に基づいて
各引数を型に応じて出力する。

#include <stdio.h>
#include <stdarg.h>

void
foo(char *fmt, ...)   /* '...' は可変長引数を示す C 構文 */
{
    va_list ap;
    int d;
    char c;
    char *s;

    va_start(ap, fmt);
    while (*fmt)
        switch (*fmt++) {
        case 's':              /* 文字列 */
            s = va_arg(ap, char *);
            printf("string %s\n", s);
            break;
        case 'd':              /* 整数 */
            d = va_arg(ap, int);
            printf("int %d\n", d);
            break;
        case 'c':              /* 文字 */
            /* va_arg() は昇格後の型を取るためキャストが必要 */
            c = (char) va_arg(ap, int);
            printf("char %c\n", c);
            break;
        }
    va_end(ap);
}

関連項目（SEE ALSO）

vprintf(3), vscanf(3), vsyslog(3)

コロフォン（COLOPHON）

このページは Linux man-pages プロジェクト リリース 5.10 の一部である。
プロジェクトの説明、バグ報告、および最新版の入手方法については：
https://www.kernel.org/doc/man-pages/

解説（実務的補足）

可変引数関数の設計上の注意
va_start() で開始したリストは、必ず同一関数内で va_end() により終了すること。
未対応のまま関数を抜けると、未定義動作を引き起こす。

va_copy() の使用理由
引数リストを別の関数に渡す場合や、再度走査したい場合には
va_copy() を用いて複製する必要がある。単純な代入では環境依存の破損を招く。

型昇格の落とし穴
char, short, float などの小さな型は、
関数呼び出し時にそれぞれ int, double に昇格して渡される。
よって va_arg(ap, char) のような呼び出しは未定義であり、
正しくは va_arg(ap, int) として取得しキャストする必要がある。

printf 系関数との関係
vprintf() / vsnprintf() などの “v” 付きバリアントは、
可変引数を直接受け取る代わりに va_list を引数に取る。
これにより、可変長関数を別の可変長関数へ安全に橋渡しできる。