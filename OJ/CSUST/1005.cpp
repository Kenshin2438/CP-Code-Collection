#include <cassert>
#include <functional>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>

#if defined(KENSHIN)
  #define DBG_MACRO_NO_WARNING
  #include "dbg/dbg.h"
#else
  #define dbg(...) (__VA_ARGS__)
#endif

using i64 = long long;

template <typename T, typename E, class F, class G, class H>
struct LazySegmentTree {
 private:
  int N, _log;
  std::vector<T> dat;
  std::vector<E> laz;
  const F f;
  const G g;
  const H h;
  const T ti;
  const E ei;
  auto init(int n) -> void {
    N = 1, _log = 0;
    while (N < n) N <<= 1, _log++;
    dat.assign(N << 1, ti);
    laz.assign(N << 1, ei);
  }
  auto build(const std::vector<T> &v) -> void {
    int n = (int)v.size();
    init(n);
    for (int i = 0; i < n; i++) dat[i + N] = v[i];
    for (int i = N - 1; i > 0; i--) {
      dat[i] = f(dat[i << 1 | 0], dat[i << 1 | 1]);
    }
  }

  inline auto reflect(int t) const -> T {
    return laz[t] == ei ? dat[t] : g(dat[t], laz[t]);
  }
  inline auto push(int t) -> void {
    if (laz[t] == ei) return;
    laz[t << 1 | 0] = h(laz[t << 1 | 0], laz[t]);
    laz[t << 1 | 1] = h(laz[t << 1 | 1], laz[t]);
    dat[t] = g(dat[t], laz[t]);
    laz[t] = ei;
  }
  inline auto thrust(int t) -> void {
    for (int i = _log; i > 0; i--) push(t >> i);
  }
  inline auto recalc(int t) -> void {
    while (t >>= 1) dat[t] = f(reflect(t << 1 | 0), reflect(t << 1 | 1));
  }

 public:
  LazySegmentTree(int n, F _f, G _g, H _h, T _ti, E _ei)
      : f(_f), g(_g), h(_h), ti(_ti), ei(_ei) {
    init(n);
  }
  LazySegmentTree(const std::vector<T> &v, F _f, G _g, H _h, T _ti, E _ei)
      : f(_f), g(_g), h(_h), ti(_ti), ei(_ei) {
    build(v);
  }

  auto set(int p, const T &val) -> void {
    thrust(p += N);
    dat[p] = val;
    laz[p] = ei;
    recalc(p);
  }
  auto get(int p) -> T {
    thrust(p += N);
    return reflect(p);
  }
  auto update(int l, int r, const E &dif) -> void {  // [l, r)
    if (l >= r) return;
    l += N, r += N;
    thrust(l), thrust(r - 1);
    for (int a = l, b = r; a < b; a >>= 1, b >>= 1) {
      if (a & 1) laz[a] = h(laz[a], dif), a++;
      if (b & 1) --b, laz[b] = h(laz[b], dif);
    }
    recalc(l), recalc(r - 1);
  }
  auto query(int l, int r) -> T {  // [l, r)
    if (l >= r) return ti;
    l += N, r += N;
    thrust(l), thrust(r - 1);
    T L = ti, R = ti;
    for (int a = l, b = r; a < b; a >>= 1, b >>= 1) {
      if (a & 1) L = f(L, reflect(a++));
      if (b & 1) R = f(reflect(--b), R);
    }
    return f(L, R);
  }
};

auto solve() -> void {
  int n, m;
  while (std::cin >> n >> m) {
    std::vector<i64> attack(n);
    for (auto &&x : attack) std::cin >> x;

    std::vector<std::vector<int>> tree(n);
    for (int i = 0; i < n - 1; i++) {
      int u, v;
      std::cin >> u >> v;
      u--, v--;
      tree[u].emplace_back(v);
      tree[v].emplace_back(u);
    }

    std::vector<int> par(n), dep(n), siz(n, 1), heavy(n, -1);
    const std::function<void(int)> dfs = [&](int u) {
      for (const int &v : tree[u]) {
        if (v == par[u]) continue;
        dep[v] = dep[u] + 1, par[v] = u;
        dfs(v);
        siz[u] += siz[v];
        if (heavy[u] == -1 or siz[heavy[u]] < siz[v]) heavy[u] = v;
      }
    };
    dfs(0);

    std::vector<int> pos(n), head(n);
    int _idx = 0;
    const std::function<void(int, int)> decompose = [&](int u, int h) {
      pos[u] = _idx++, head[u] = h;
      if (heavy[u] != -1) decompose(heavy[u], h);
      for (const int &v : tree[u]) {
        if (v == par[u] or v == heavy[u]) continue;
        decompose(v, v);
      }
    };
    decompose(0, 0);

    using T = std::pair<i64, i64>;
    using E = i64;
    std::vector<T> data(n);
    for (int i = 0; i < n; i++) data[pos[i]] = {attack[i], 1};
    auto f = [](T a, T b) -> T {
      return T{a.first + b.first, a.second + b.second};
    };
    auto g = [](T a, E b) -> T { return T{a.first + a.second * b, a.second}; };
    auto h = [](E a, E b) -> E { return a + b; };
    using Tree = LazySegmentTree<T, i64, decltype(f), decltype(g), decltype(h)>;
    Tree seg(data, f, g, h, T{0, 0}, 0LL);

    std::vector<std::vector<int>> Q(m);

    for (int i = 0; i < m; i++) {
      int op;
      std::cin >> op;
      Q[i].emplace_back(op);

      if (op == 1) {
        int u, X;
        std::cin >> u >> X;
        u--;
        Q[i].emplace_back(u);
        Q[i].emplace_back(X);

        seg.update(pos[u], pos[u] + siz[u], X);
      } else if (op == 2) {
        int u, v, X;
        std::cin >> u >> v >> X;
        u--, v--;
        Q[i].emplace_back(u);
        Q[i].emplace_back(v);
        Q[i].emplace_back(X);

        while (head[u] != head[v]) {
          if (dep[head[u]] < dep[head[v]]) std::swap(u, v);
          seg.update(pos[head[u]], pos[u] + 1, X);
          u = par[head[u]];
        }
        if (dep[u] < dep[v]) std::swap(u, v);
        seg.update(pos[v], pos[u] + 1, X);
      } else if (op == 3) {
        int t;
        std::cin >> t;
        t--;
        if (Q[t][0] == 1) {
          int u = Q[t][1], X = -Q[t][2];
          seg.update(pos[u], pos[u] + siz[u], X);
        } else if (Q[t][0] == 2) {
          int u = Q[t][1], v = Q[t][2], X = -Q[t][3];
          while (head[u] != head[v]) {
            if (dep[head[u]] < dep[head[v]]) std::swap(u, v);
            seg.update(pos[head[u]], pos[u] + 1, X);
            u = par[head[u]];
          }
          if (dep[u] < dep[v]) std::swap(u, v);
          seg.update(pos[v], pos[u] + 1, X);
        } else {
          assert(false);
        }
      } else {
        int u;
        std::cin >> u;
        u--;
        std::cout << seg.get(pos[u]).first << "\n";
      }
    }
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