#include <iomanip>
#include <iostream>
#include <map>
#include <string>

#if defined(KENSHIN)
  #define DBG_MACRO_NO_WARNING
  #include "dbg/dbg.h"
#else
  #define dbg(...) (__VA_ARGS__)
#endif

using i64 = long long;

auto solve() -> void {
  int n;
  std::string a, b;
  std::cin >> n >> a >> b;

  int ans = 0;
  for (int i = 0, j = n - 1; i <= j; i++, j--) {
    if (i == j) {
      ans += (a[i] != b[i]);
    } else {
      std::map<char, int> Mp;
      Mp[a[i]] ^= 1;
      Mp[a[j]] ^= 1;
      Mp[b[i]] ^= 1;
      Mp[b[j]] ^= 1;
      int count = 0;
      for (const auto &item : Mp) count += item.second;
      ans += count / 2;
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