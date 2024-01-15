#include <functional>
#include <iomanip>
#include <iostream>
#include <unordered_set>
#include <vector>

#if defined(KENSHIN)
  #define DBG_MACRO_NO_WARNING
  #include "dbg/dbg.h"
#else
  #define dbg(...) (__VA_ARGS__)
#endif

using i64 = long long;

using u64 = unsigned long long;
auto splitmix64(u64 x) -> u64 {
  // http://xorshift.di.unimi.it/splitmix64.c
  x += 0x9e3779b97f4a7c15;
  x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
  x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
  return x ^ (x >> 31);
}
auto SEED = __builtin_ia32_rdtsc();

auto solve() -> void {
  int n, m;
  std::cin >> n >> m;

  std::unordered_set<u64> S;
  for (int _ = 0; _ < n; _++) {
    int k;
    std::cin >> k;
    u64 H = 0;
    for (int i = 0; i < k; i++) {
      int x;
      std::cin >> x;
      H += splitmix64(x ^ SEED);
      S.emplace(H);
    }
  }

  std::vector<int> ch(m);
  for (auto &&x : ch) std::cin >> x;
  std::vector<std::vector<int>> tree(m);
  for (int i = 0; i < m - 1; i++) {
    int u, v;
    std::cin >> u >> v;
    u--, v--;
    tree[u].emplace_back(v);
    tree[v].emplace_back(u);
  }

  bool ans = true;
  std::vector<u64> G(m);
  const std::function<void(int, int)> dfs = [&](int u, int fa) {
    G[u] = G[fa] + splitmix64(ch[u] ^ SEED);
    if (S.find(G[u]) == S.end()) ans = false;
    for (const auto &v : tree[u]) {
      if (v == fa) continue;
      dfs(v, u);
    }
  };
  dfs(0, 0);
  std::cout << (ans ? "YES" : "NO") << "\n";
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