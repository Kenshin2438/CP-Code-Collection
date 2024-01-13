#include <iomanip>
#include <iostream>
#include <stack>
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

  std::vector<int> a(n);
  for (auto &&x : a) std::cin >> x;

  std::vector<int> ans(n);
  std::stack<int> stk;
  for (int i = n - 1; i >= 0; i--) {
    while (!stk.empty() and a[stk.top()] <= a[i]) stk.pop();
    ans[i] = stk.empty() ? 0 : stk.top() - i;
    stk.push(i);
  }
  for (int i = 0; i < n; i++) std::cout << ans[i] << " \n"[i + 1 == n];
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