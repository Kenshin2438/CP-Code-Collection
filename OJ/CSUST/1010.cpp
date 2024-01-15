#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <numeric>
#include <vector>

#if defined(KENSHIN)
  #define DBG_MACRO_NO_WARNING
  #include "dbg/dbg.h"
#else
  #define dbg(...) (__VA_ARGS__)
#endif

using i64 = long long;

auto solve() -> void {
  int n;
  std::cin >> n;

  std::vector<int> a(n), pos(n);
  for (auto &&x : a) std::cin >> x;
  std::iota(std::begin(pos), std::end(pos), 0);
  std::sort(std::begin(pos), std::end(pos), [&](int pa, int pb) {
    return a[pa] == a[pb] ? pa < pb : a[pa] > a[pb];
  });  // 由于(0 < a[i] < 1E6)，排序部分实际可以用桶完成。

  std::vector<int> ans(n);
  for (int i = 0, last = -1; i < n; i++) {
    if (pos[i] < last)
      ans[pos[i]] = last - pos[i];
    else
      last = pos[i];
  }
  for (int i = 0; i < n; i++) {
    std::cout << ans[i] << " \n"[i + 1 == n];
  }
}

auto main() -> int {
  std::ios_base::sync_with_stdio(false);
  std::cin.exceptions(std::istream::failbit);
  std::cin.tie(nullptr);

  std::cout << std::fixed << std::setprecision(15);

  int testCase = 1;
  // std::cin >> testCase;
  while (testCase--) solve();

  return 0;
}