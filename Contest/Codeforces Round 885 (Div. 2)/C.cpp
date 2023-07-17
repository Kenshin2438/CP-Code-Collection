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

auto solve() -> void {
  int n;
  std::cin >> n;

  std::vector<int> a(n), b(n);
  for (auto &x : a) std::cin >> x;
  for (auto &x : b) std::cin >> x;

  if (std::all_of(all(a), [](int x) { return x == 0; }) or
      std::all_of(all(b), [](int x) { return x == 0; }) or a == b) {
    std::cout << "YES\n";
    return;
  }

  auto count = [](int A, int B) -> int {
    int G = std::gcd(A, B);
    A /= G, B /= G;

    if (A & B & 1) {
      return 1;
    } else if (A & 1) {
      return 0;
    } else {
      return 2;
    }
  };

  std::set<int> S;
  for (int i = 0; i < n; i++) {
    if (a[i] == b[i] and a[i] == 0) continue;
    S.insert(count(a[i], b[i]));
  }
  std::cout << (S.size() == 1 ? "YES" : "NO") << '\n';
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