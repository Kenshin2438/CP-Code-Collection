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
  int n, m, k;
  std::cin >> n >> m >> k;

  int x, y;
  std::cin >> x >> y;

  bool ans = true;
  for (int i = 0; i < k; i++) {
    int xi, yi;
    std::cin >> xi >> yi;

    if ((xi - x + yi - y) % 2 == 0) ans = false;
  }

  std::cout << (ans ? "YES" : "NO") << "\n";
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