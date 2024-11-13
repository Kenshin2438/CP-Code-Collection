#pragma once

#include <vector>

namespace kenshin::DS {
  class DisjointSetUnion {
   private:
    std::vector<int> p;

   public:
    explicit DisjointSetUnion(int n) : p(n, -1) {}

    auto find(int x) -> int { return p[x] < 0 ? x : p[x] = find(p[x]); }
    auto size(int x) -> int { return -p[find(x)]; }
    auto same(int u, int v) -> bool { return find(u) == find(v); }
    auto merge(int u, int v) -> bool {
      u = find(u), v = find(v);
      if (u == v) return false;
      p[u] += p[v], p[v] = u;
      return true;
    }
  };
}  // namespace kenshin::DS