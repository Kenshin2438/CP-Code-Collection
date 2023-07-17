#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <numeric>
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

std::vector<i64> S(10);

auto solve() -> void {
  i64 s, k;
  std::cin >> s >> k;

  if (s % 10 == 0 or k == 1) {
    std::cout << s * k << '\n';
    return;
  }

  if (s % 10 == 5) {
    std::cout << std::max(s * k, (s + 5) * (k - 1)) << '\n';
    return;
  }

  i64 ans = s * k;

  /**

  1->2  9->8
     2->4->8->6->2
     7->4  3->6

  5->0

  */

  if (s % 2 == 1) {
    s += s % 10;
    k -= 1;
    ans = std::max(ans, s * k);
  }

  // (s + 20t) * (k - 4t) = -80t^2 + (20k - 4s)t + sk
  const auto f = [](i64 ss, i64 kk, i64 t) -> i64 {
    return (ss + 20 * t) * (kk - 4 * t);
  };
  for (int i = 0; i < 4; i++) {
    i64 mid = (5 * k - s) / 40;

    if (mid > 0) {
      ans = std::max(ans, f(s, k, mid));
    }
    if (mid + 1 > 0) {
      ans = std::max(ans, f(s, k, mid + 1));
    }

    s += s % 10;
    k -= 1;
    ans = std::max(ans, s * k);

    if (k == 1 or k == 0) break;
  }

  std::cout << ans << '\n';
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