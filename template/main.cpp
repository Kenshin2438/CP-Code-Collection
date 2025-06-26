#include <bits/stdc++.h>

#if defined(KENSHIN)
  #define DBG_MACRO_NO_WARNING
  #include "dbg/dbg.h" // IWYU pragma: keep
#else
  #define dbg(...) (__VA_ARGS__)
#endif

auto solve() -> void {

}

auto main() -> int {
  std::ios_base::sync_with_stdio(false);
  std::cin.exceptions(std::cin.failbit);
  std::cin.tie(nullptr);

  std::cout << std::fixed << std::setprecision(15);

  int testCase = 1;
  // std::cin >> testCase;
  while (testCase--) solve();

  return 0;
}
