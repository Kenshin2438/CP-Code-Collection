## D Integral Array
如果$a$不在集合中，且$b$在集合中，则$[a \times b, (a + 1) \times b)$的数不能在集合中。

+ 复杂度 $\mathcal{O}(c\log{c})$

## E Tyler and Strings

`s: *****i...`

`t: *****k...`

上面的情况，方案数：
$$
\begin{aligned}
\sum_{i<k}\frac{A_{len}^{len}}{A_{cnt[i-1]}^{cnt[i]-1}\prod_{j \neq i}A_{cnt[j]}^{cnt[j]}}
& = \sum_{i<k}\frac{cnt[i] \times A_{len}^{len}}{\prod_{j}A_{cnt[j]}^{cnt[j]}} \\
& = \frac{A_{len}^{len}\times\sum_{i<k}cnt[i]}{\prod_{j}A_{cnt[j]}^{cnt[j]}}
\end{aligned}
$$
注意到分母可以直接简单维护一下，分子重点在**动态维护前缀和**，树状数组水一下。

+ 复杂度 $\mathcal{O}\left(m\log{(\max{s_i})}\right)$

## F Serious Business

