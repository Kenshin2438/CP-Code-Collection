#include <algorithm>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <set>
#include <vector>

#if defined(KENSHIN)
  #define DBG_MACRO_NO_WARNING
  #include "dbg/dbg.h"
#else
  #define dbg(...) (__VA_ARGS__)
#endif

using i64 = long long;

auto solve() -> void {
  int n, p;
  std::cin >> n >> p;

  std::vector<int> a(n);
  for (auto &&x : a) std::cin >> x;
  auto b = a;
  std::sort(std::begin(b), std::end(b));

  for (int i = 0; i < n; i++) {
    int ans = (a[i] + (a[i] == b[n - 1] ? b[n - 2] : b[n - 1])) % p;
    int l = 0, r = n - 1, pos = -1;
    while (l <= r) {
      int m = (l + r) / 2;
      if (a[i] + b[m] < p) {
        pos = m;
        l = m + 1;
      } else {
        r = m - 1;
      }
    }
    // 事实上：如果按照a[i]递增的顺序枚举，相应的pos值会一直递减，可使用双指针
    if (pos != -1) {
      if (b[pos] == a[i]) {
        if (pos - 1 >= 0) ans = std::max(ans, (a[i] + b[pos - 1]) % p);
      } else {
        ans = std::max(ans, (a[i] + b[pos]) % p);
      }
    }
    std::cout << ans << " \n"[i + 1 == n];
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