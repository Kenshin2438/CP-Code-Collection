根据数据大小，动态使用`std::bitset<>`，基本原理是利用`template<size_t N>`进行的判断和递归。

```cpp
// https://codeforces.com/contest/1856/problem/E2
constexpr size_t MAXN = 1 << 20;

template <size_t N = 1>
auto closest(const size_t &M, const std::vector<int> &S) -> i64 {
  if (N <= M) return closest<std::min(MAXN, N * 2)>(M, S);
  using BS = std::bitset<N>;

  BS dp;

  dp.set(0, true);
  for (const auto &val : S) dp |= dp << val;
  int res = 0, diff = int(M);
  for (int i = 0; i <= int(M); i++) {
    if (dp.test(i)) {
      auto d = std::abs(i - int(M - i));
      if (d < diff) {
        diff = d, res = i;
      }
    }
  }

  return res;
}
```