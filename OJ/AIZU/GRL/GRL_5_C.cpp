#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

#define PII pair<int, int>
#define vec vector
#define str string
#define fi first
#define se second
#define all(a) (a).begin(), (a).end()
#define SZ(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

template <typename T, T (*f)(T, T)> struct ST {
  vec<vec<T>> st;

  ST() {}
  ST(const vec<T> &v) : st(1, v) {
    for (int pw = 1, k = 1; (pw << 1) <= SZ(v); pw <<= 1, k++) {
      st.emplace_back(SZ(v) - (pw << 1) + 1);
      for (int i = 0; i < SZ(st[k]); i++) {
        st[k][i] = f(st[k - 1][i], st[k - 1][i + pw]);
      }
    }
  }
  T query(int l, int r) {  // query [l, r)
    int dep = 31 - __builtin_clz(r - l);
    return f(st[dep][l], st[dep][r - (1 << dep)]);
  }
};
template <typename T> T Min(T a, T b) { return min<T>(a, b); }

struct Graph {
  vec<PII> euler_tour;
  vec<int> dfn;
  ST<PII, Min<PII>> st;

  int n, rt;
  vec<vec<int>> G;

  Graph(int _, int _rt = 0) : n(_), rt(_rt), G(_) {
    for (int i = 0; i < n; i++) {
      int m, x; cin >> m;
      while (m--) {
        cin >> x;
        G[i].emplace_back(x);
      }
    }
    dfn.assign(n, 0);
    auto dfs = [&](auto &&self, int u, int fa) -> void {
      dfn[u] = SZ(euler_tour);
      euler_tour.emplace_back(dfn[u], u);
      for (const int &v : G[u]) {
        if (v == fa) continue;
        self(self, v, u);
        euler_tour.emplace_back(dfn[u], u);
      }
    };
    dfs(dfs, rt, -1);
    st = ST<PII, Min<PII>>(euler_tour);
  }

  int lca(int u, int v) {
    int l = dfn[u], r = dfn[v];
    if (l > r) swap(l, r);
    return st.query(l, r + 1).se;
  }
};

void SingleTest(int TestCase) {
  int n; cin >> n;
  Graph tree(n);
  int Q; cin >> Q;
  for (int u, v; Q--;) {
    cin >> u >> v;
    cout << tree.lca(u, v) << '\n';
  }
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  // cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
