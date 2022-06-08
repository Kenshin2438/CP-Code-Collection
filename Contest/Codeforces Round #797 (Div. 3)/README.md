## A. Print a Pedestal (Codeforces logo?)

暴力枚举

## B. Array Decrements

所以数必须操作的次数： $\max_i (a[i] - b[i])$

特判不可能的情况

## C. Restoring the Duration of Tasks

先求 $s[i]$ 的实际值 $max(s[i], f[i - 1])$，然后没了

## D. Black and White Stripe

枚举所有大小为 k 的区间的和，双指针或者前缀和都行

## E. Price Maximization

贪心

$\lfloor \frac{x+y}{k} \rfloor$ 中会影响答案的其实只有：$x \% k, y \% k$。

如果 $x \% k + y \% k \geq k$ 则加 $1$，存下所有$a[i]\% k$，然后双指针扫一遍即可。

## F. Shifting String

~~和今年澳门站那题简直一模一样。~~

想象一下建图的样子，显然就是一系列的独立的环，那么答案就是每个环的最小操作数（使用 KMP 去求）的 $\mathrm{lcm}$。

## G. Count the Trains

珂朵莉树裸题。。。这也能放G？