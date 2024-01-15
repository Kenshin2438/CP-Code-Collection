#include <iomanip>
#include <iostream>
#include <queue>
#include <tuple>
#include <utility>

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
  std::priority_queue<std::pair<i64, i64>> snack;
  for (int i = 0; i < n; i++) {
    i64 w, d;
    std::cin >> w >> d;
    snack.emplace(d, w);
  }
  i64 ans = 0;
  int time = 0;
  while (!snack.empty()) {
    i64 d, w;
    std::tie(d, w) = snack.top();
    snack.pop();
    auto res = w - d * time;
    if (res <= 0) continue;
    if (res >= d) {
      ans += res, time += 1;
    } else {
      snack.emplace(res, (time + 1) * res);
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