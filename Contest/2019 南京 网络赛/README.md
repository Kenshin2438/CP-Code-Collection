## The Preliminary Contest for ICPC Asia Nanjing 2019

[link](https://www.jisuanke.com/contest/3004/challenges)

### A. The beautiful values of the palace

模拟 + 树状数组

查询子矩阵和：将询问差分（分成四份），树状数组查询[(1, 1), (x, y)]的和。

### B. super_log

欧拉降幂 （拓展）

**拓展欧拉定理下的 快速幂模板**
```cpp
ll euler_qpow(ll x, ll n, ll mod) {
  ll res = 1, tag = 0;
  if (x >= mod) x %= mod, tag = 1;
  for (; n > 0LL; n >>= 1) {
    if (n & 1LL) {
      if ((res *= x) > mod) res %= mod, tag = 1;
    } 
    if ((x *= x) > mod) x %= mod, tag = 1;
  } 
  return res + mod * tag;
}
```

### C. Tsy's number 5 

NTT + Tonelli_Shanks

$$
\begin{aligned}
Answer 
&= \sum_{i=1}^{n}\sum_{j=1}^{n}\varphi(i)\varphi(j)2^{\varphi(i)\varphi(j)} \\
&= \sum_{i=1}^{n}\sum_{j=1}^{n}ij2^{ij} \times cnt[i]\times cnt[j] \\
&= \sum_{i=1}^{n}\sum_{j=1}^{n}(i\times cnt[i]\times \sqrt{2}^{-i^2})\times(j\times cnt[j]\times \sqrt{2}^{-j^2}) \times \sqrt{2}^{(i+j)^2} \\
&= \sum_{k=2}^{2n}\sqrt{2}^{k^2}\times[x^k]h(x)\\
\end{aligned}
$$

其中 $h(x)=f(x)*f(x), f(x)=\sum_{i=1}^{n}(i\times cnt[i]\times \sqrt{2}^{-i^2})x^i$。

### D. Robots

DAG上概率DP

### E. K Sum

拓展欧拉定理 + 杜教筛

$$
\begin{aligned}
Answer 
&= \sum_{k=2}^{K}\left(\sum_{l_1=1}^{n}\sum_{l_2=1}^{n}\dots\sum_{l_k=1}^{n}\left(\gcd(l_1, l_2, \dots, l_k)^2\right)\right) \\
&= \sum_{k=2}^{K}\left(\sum_{g=1}^{n}g^2\sum_{d=1}^{[\frac{n}{g}]}\mu(d)\times[\frac{n}{gd}]^k\right) \\
&= \sum_{k=2}^{K}\left(\sum_{T=1}^{n}[\frac{n}{T}]^k\sum_{d \mid T}d^2\mu(\frac{T}{d})\right) \\
&= \sum_{T=1}^{n}\left(\sum_{k=2}^{K}[\frac{n}{T}]^k\right)\times(\mu * Id_2)(T) \\
\end{aligned}
$$

卷积部分：

$$
S(m) = \sum_{i=1}^{m}(\mu*Id_2)(i) = \sum_{i=1}^{m}f(i)
$$

由于$\mu * Id_2 * 1 = Id_2$，

$$
1(1) \times S(m) = \sum_{i=1}^{m}Id_2(i)-\sum_{i=2}^{m}1(i)\times S([\frac{m}{i}])
$$

### F. Greedy Sequence

线段树

### G. Quadrilateral

给定四边形 各条边 的取值范围，求能够组成的四边形的个数。

$\mathcal{O}(1)$求不等式 $[1,a]+[1,b]\leq [1,c]$ 的整数解个数。
```cpp
ll F(int l, int r) {
  if (l > r) return 0LL;
  ll S1 = (l + r) * 1LL * (r - l + 1) / 2;

  ll S2r = r * 1LL * (r + 1) * (2 * r + 1) / 6;
  --l;
  ll S2l = l * 1LL * (l + 1) * (2 * l + 1) / 6;
  return (S1 + S2r - S2l) / 2;
}

ll S(int a, int b, int c) {
  if (a < 1 || b < 1 || c < 2) return 0LL;
  // solve [1, a] + [1, b] <= [1, c]
  a = min(a, c - 1), b = min(b, c - 1);
  if (a > b) swap(a, b); // s.t. a <= b
  ll res = 0LL;
  if (c > a + b) {
    res += a * 1LL * b * (c - (a + b));
    c = a + b;
  }
  // c <= a + b, a <= b < c
  res += b * 1LL * (b - 1) / 2 * (c - b);
  res += (c - b) * 1LL * (1 + c - b) / 2 * b;
  res += F(c - a, b - 1);
  return res;
}
```

### H. Holy Grail

最短路

### I. Washing clothes

决策单调性 + CHT优化DP（维护直线集合）