#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <vector>

#if defined(KENSHIN)
  #define DBG_MACRO_NO_WARNING
  #include "dbg/dbg.h"
#else
  #define dbg(...) (__VA_ARGS__)
#endif

using i64 = long long;

auto solve() -> void {
  int n, k;
  std::cin >> n >> k;

  std::vector<i64> w(2 * n + k);
  for (auto &&x : w) std::cin >> x;
  std::sort(begin(w), end(w));

  static constexpr i64 INF = std::numeric_limits<i64>::max();
  std::vector<std::vector<i64>> dp(2 * n + k + 1, std::vector<i64>(k + 1, INF));
  dp[0][0] = 0;  // dp[i][j] := 前i个物品，其中j个用货车搬运
  for (int i = 1; i <= 2 * n + k; i++) {
    for (int j = 0; j <= std::min(k, i); j++) {
      if ((i - j) % 2 != 0) continue;
      if (j > 0) dp[i][j] = std::min(dp[i][j], dp[i - 1][j - 1]);
      for (int now = i - 1, pre = now - 1; pre >= 0; pre--) {
        int delta = now - pre - 1;     // 中间需要装上货车的物品数
        if (now - pre - 1 > j) break;  // 最多循环k次
        if (pre < (j - delta) or (pre - (j - delta)) % 2 != 0) continue;
        dp[i][j] = std::min(dp[i][j], dp[pre][j - delta] + w[now] - w[pre]);
      }
    }
  }
  std::cout << dp[2 * n + k][k] << "\n";
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