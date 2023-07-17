#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <set>
#include <vector>

#ifdef KENSHIN
  #define DBG_MACRO_NO_WARNING
  #include "dbg/dbg.h"
#else
  #define dbg(...) (__VA_ARGS__)
#endif

using i64 = std::int64_t;
#define all(a) std::begin(a), std::end(a)

auto solve() -> void {
  int n, k;
  std::cin >> n >> k;

  std::vector<std::vector<int>> len(k, {-1});
  std::vector<int> pre(k, -1);
  for (int i = 0; i < n; i++) {
    int c;
    std::cin >> c;
    c--;
    len[c].emplace_back(i - pre[c] - 1);
    pre[c] = i;
  }
  for (int i = 0; i < k; i++) {
    len[i].emplace_back(n - pre[i] - 1);
  }

  int ANS = n / 2;
  for (int i = 0; i < k; i++) {
    if (size(len[i]) == 1) continue;
    std::sort(all(len[i]), std::greater<>());
    ANS = std::min(ANS, std::max(len[i][0] / 2, len[i][1]));
  }
  std::cout << ANS << '\n';
}

auto main() -> int {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::cout << std::fixed << std::setprecision(15);

  int TestCase = 1;
  std::cin >> TestCase;
  while ((TestCase--) != 0) solve();

  return 0;
}