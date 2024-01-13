#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <unordered_map>
#include <utility>
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

  static constexpr i64 N = 30'005, M = 90'677;
  const auto hash = [](i64 x, i64 y) { return x * M + y; };

  std::unordered_map<i64, int> Mp;
  std::vector<std::pair<int, int>> ps;
  for (int i = 0; i < n; i++) {
    i64 x, y;
    std::cin >> x >> y;
    x += N, y += N;
    Mp[hash(x, y)] += 1;
    ps.emplace_back(x, y);
  }
  std::sort(std::begin(ps), std::end(ps));
  ps.erase(std::unique(std::begin(ps), std::end(ps)), std::end(ps));

  std::unordered_map<i64, std::unordered_map<i64, i64>> cnt;
  i64 ans = 0;
  for (int i = 0; i < (int)ps.size(); i++) {
    for (int j = 0; j < i; j++) {
      const auto ax = ps[i].first, ay = ps[i].second;
      const auto bx = ps[j].first, by = ps[j].second;
      i64 dis = (ax - bx) * (ax - bx) + (ay - by) * (ay - by);
      auto midHash = hash(ax + bx, ay + by);
      ans += cnt[midHash][dis] * Mp[hash(ax, ay)] * Mp[hash(bx, by)];
      cnt[midHash][dis] += Mp[hash(ax, ay)] * 1LL * Mp[hash(bx, by)];
    }
  }
  std::cout << ans << "\n";
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