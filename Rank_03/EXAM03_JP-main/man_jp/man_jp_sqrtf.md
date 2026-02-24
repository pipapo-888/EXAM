# SQRTF(3) — Linux Programmer's Manual

## 名前
sqrt, sqrtf, sqrtl — 平方根を計算する

## 書式
```c
#include <math.h>

double sqrt(double x);
float sqrtf(float x);
long double sqrtl(long double x);
```

## 説明
`sqrt()`、`sqrtf()`、および `sqrtl()` は、それぞれ引数 `x` の平方根を返す。  
負の引数を与えた場合の動作は定義されておらず、結果は NaN となり、`errno` に `EDOM` が設定される。

`x` が ±0 の場合は +0 を返し、`x` が +∞ の場合は +∞ を返す。  
`x` が NaN の場合は、そのまま NaN を返す。

## 返り値
`x` の平方根を返す。  
もし `x` が負の場合、結果は NaN であり、`errno` は `EDOM` に設定される。

## エラー
`EDOM` — 引数 `x` が負である（定義域エラー）。  
`ERANGE` — 結果が表現範囲外（ほぼ発生しない）。

## 属性
| インタフェース | 属性 | 値 |
|---|---|---|
| `sqrt()`, `sqrtf()`, `sqrtl()` | スレッド安全性 | MT-Safe |

## 準拠
C89, C99, POSIX.1-2001, POSIX.1-2008。

## 注記（NOTES）
- C99 以降では、型に応じて自動的に `sqrt()`, `sqrtf()`, `sqrtl()` を選択するジェネリックマクロが利用できる。  
- 負数の平方根を扱いたい場合は、複素数版の `csqrt(3)` を使用する。  
- IEEE754 環境では、`sqrt()` はハードウェア命令（例：x86 の `fsqrt`）として実装されており、例外発生は厳密に定義されている。

## 例
```c
#include <stdio.h>
#include <math.h>
#include <errno.h>

int main(void) {
    double val = -4.0;
    errno = 0;
    double res = sqrt(val);

    if (errno == EDOM)
        perror("sqrt");

    printf("sqrt(%f) = %f\n", val, res);
    return 0;
}
```

## 関連項目
`csqrt(3)`, `cbrt(3)`, `pow(3)`, `fabs(3)`, `math_error(7)`

## コロフォン（COLOPHON）
このページは Linux man-pages プロジェクトの一部である。プロジェクトの説明、バグ報告、および最新版の入手方法については：  
<https://www.kernel.org/doc/man-pages/>

---

## 解説（実務的補足）
- **実装**：多くのCPUはハードウェア命令による高速平方根演算を持つ（x86: `fsqrt`, ARM: `vsqrt`）。  
- **数値安定性**：`sqrt()` は IEEE754 で丸め誤差が規定され、再現性が高い。  
- **用途**：距離計算、統計量（分散・標準偏差）などで広く利用される。  
- **代替実装**：平方根の近似には Newton-Raphson 法やバイナリサーチ法が使われるが、`sqrt()` は最適化済みで推奨される。