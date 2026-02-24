FREE(3) — Linux Programmer's Manual
名前

calloc, malloc, free, realloc — 動的メモリ割り当て

書式
#include <stdlib.h>

void *calloc(size_t nmemb, size_t size);
void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);

説明

これらの関数はヒープ領域における動的メモリ割り当てを行う。

malloc() は、呼び出し元に対し size バイトのメモリブロックを割り当てる。
このメモリ領域の内容は未定義（未初期化）である。

calloc() は、nmemb 個の要素からなる配列を割り当て、各要素のサイズを size バイトとする。
この関数は nmemb * size バイトのメモリ領域を確保し、そのすべてをゼロで初期化する。

realloc() は、ptr が指すメモリブロックのサイズを size バイトに変更する。
元のブロックの内容のうち、
新しいサイズで表現できる範囲は保持される（縮小時は切り詰められる）。
新しい領域が元の場所に確保できない場合、
新しいブロックを確保して内容をコピーし、古いブロックを解放する。

free() は、ptr が指すメモリブロックを解放する。
ptr は以前に malloc(), calloc(), または realloc() により返されたポインタでなければならない。
ptr が NULL の場合、free() は何も行わない。

メモリ確保に失敗した場合、これらの関数は NULL を返す。
また、その際には errno が ENOMEM に設定される。

返り値

成功時、
malloc()、calloc()、および realloc() は、要求されたメモリブロックの先頭を指すポインタを返す。
失敗時は NULL を返し、errno を ENOMEM に設定する。
失敗後に返されるポインタの値は未定義である。
free() は値を返さない。

エラー

ENOMEM — 十分なメモリを確保できなかった。

属性
インタフェース	属性	値
malloc(), calloc(), realloc(), free()	スレッド安全性	MT-Safe （スレッドセーフ）
準拠

C89, C99, POSIX.1-2001, POSIX.1-2008。

注記（NOTES）

malloc() などの関数は、オペレーティングシステムのヒープ管理機構に依存する。

返されたポインタは、アラインメント要件を満たしている。

free() は、既に解放済みのポインタを再び解放したり、動的割り当てによって得られなかったポインタを解放した場合の動作を未定義とする。

realloc() の呼び出しにおいて size == 0 である場合、実装によっては free(ptr) を呼び出した後に NULL を返す。

例

以下のコードは、calloc(), malloc(), realloc(), および free() の基本的な使用例を示す。

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *array;
    size_t n = 10;

    array = calloc(n, sizeof(*array));
    if (array == NULL) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }

    for (size_t i = 0; i < n; i++)
        array[i] = i;

    int *tmp = realloc(array, n * 2 * sizeof(*array));
    if (tmp == NULL) {
        perror("realloc");
        free(array);
        exit(EXIT_FAILURE);
    }
    array = tmp;

    for (size_t i = n; i < n * 2; i++)
        array[i] = i;

    for (size_t i = 0; i < n * 2; i++)
        printf("%d ", array[i]);
    printf("\n");

    free(array);
    return 0;
}

関連項目

brk(2), mmap(2), alloca(3), malloc_usable_size(3), posix_memalign(3),
reallocarray(3), strdup(3), strndup(3)

コロフォン

このページは Linux man-pages プロジェクトの一部である。
プロジェクトの説明、バグ報告、最新版の入手方法については：
https://www.kernel.org/doc/man-pages/

解説（実務的補足）

メモリ管理の原則
malloc()・calloc()・realloc() で確保したメモリは、必ず free() によって解放する。
ポインタを NULL に設定することで、二重解放を防止できる。

ゼロ初期化の違い
calloc() は領域をゼロで初期化するが、malloc() は初期化を行わない。
安全性を重視する場合は calloc() の使用が推奨される。

メモリ不足対策
errno == ENOMEM を検出したら、ログ出力や再試行などの明確な処理を行うこと。
ヒープ断片化による失敗もあり得る。

realloc() の安全な使用法
realloc() の結果を直接元のポインタに代入せず、一時ポインタに格納してから更新するのが安全である。
失敗した場合に元のポインタが保持されるため、メモリリークを防げる。