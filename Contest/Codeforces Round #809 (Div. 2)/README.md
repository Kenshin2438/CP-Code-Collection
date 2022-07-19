## A	Another String Minimization Problem

## B	Making Towers

对于每个$r$，存下下标，找奇偶交替的最长长度。

## C	Qpwoeirut And The City

$n$为奇数，答案的位置固定。
$n$为偶数，每两个数中必然有一个有贡献，枚举中间点。( 01010...|...01010 )

## D1/D2	Chopping Carrots

考虑整除分块，每个数整出后的可能取值为$O(\sqrt{a_i})$。

考虑枚举最大值$M$，将大于它的数都移动到小于$M$的位置，同时为了保证时间复杂度，我们倒序枚举$M$，每个数只跳**最近**的下一个整除分块的值。

+ `clear`, `resize`, `reverse`, `pop/pop_back` 并不会回收动态内存。应该使用如下方式：

```cpp
vector<Typename>().swap(v); // 在当前轮结束后，执行析构函数，回收这一片内存
```

## E	Qpwoeirut and Vertices

启发式合并 + RMQ

求出 x 和 x + 1 联通的要求，记为 val[x]。则 [l, r] 联通的要求为 max(val[l], ..., val[r - 1])。