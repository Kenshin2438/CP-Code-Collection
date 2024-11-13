#pragma once

#include <vector>

namespace kenshin::DS {
  class tree_hash {
   private:
    using Tree = std::vector<std::vector<int>>;
    Tree tree;

    using ull = unsigned long long;
    std::vector<ull> H, G;
    // H(u) -> Hash value of subtree(u)
    // G(u) -> Hash value of tree(u-rooted)

   private:
    static constexpr auto splitmix64(ull x) -> ull {
      // http://xorshift.di.unimi.it/splitmix64.c
      x += 0x9e3779b97f4a7c15;
      x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
      x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
      return x ^ (x >> 31);
    }

   public:
    constexpr explicit tree_hash(const Tree &Z) noexcept
      : tree(Z), H(Z.size(), 1ULL), G(Z.size(), 0ULL) {};

    constexpr void build() {
      const auto dfs = [this](this auto &&dfs, int u, int fa) -> void {
        for (const int &v : tree[u]) {
          if (v == fa) continue;
          dfs(v, u);
          H[u] += splitmix64(H[v]);
        }
      };
      dfs(0, 0);
      const auto sol = [this](this auto sol, int u, int fa) -> void {
        for (const int &v : tree[u]) {
          if (v == fa) continue;
          G[v] = H[v] + splitmix64(G[u] - splitmix64(H[v]));
          sol(v, u);
        }
      };
      G[0] = H[0];
      sol(0, 0);
    }
  };
}  // namespace kenshin::DS