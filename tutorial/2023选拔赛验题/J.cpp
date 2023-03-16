#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

struct DSU {
  vector<int> p;

  DSU() = default;
  DSU(int n) : p(n, -1) {}
  ~DSU() = default;

  int find(int x) { return p[x] < 0 ? x : p[x] = find(p[x]); }
  int size(int x) { return -p[find(x)]; }
  bool same(int u, int v) { return find(u) == find(v); }
  bool merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;

    p[u] += p[v], p[v] = u;
    return true;
  }
};

struct FenwickTree {
 private:
  vector<ll> s, d;

  void add(int p, ll dif) {
    ll val = (p + 1) * dif;
    for (; p < sz(s); p |= p + 1) {
      s[p] += val, d[p] += dif;
    }
  }
  ll query(int i) {
    ll S = 0LL, D = 0LL;
    for (int p = i; p > 0; p &= p - 1) {
      S += s[p - 1], D += d[p - 1];
    }
    return D * (i + 1) - S;
  }

 public:
  FenwickTree() = default;
  FenwickTree(int n) : s(n), d(n) {}

  void range_add(int l, int r, ll val) {  // [l, r)
    add(l, val), add(r, -val);
  }
  ll range_query(int l, int r) {  // [l, r)
    return query(r) - query(l);
  }
};

void solve() {
  int n, q; cin >> n >> q;
  assert(1 <= n && n <= (int) 1e5);
  assert(1 <= q && q <= (int) 1e5);
  vector<ll> a(n);
  for (auto &&x : a) {
    cin >> x;
    assert((int) -1e9 <= x && x <= (int) 1e9);
  }

  DSU dsu(n);

  vector<vector<int>> tree(n);
  for (int _ = 0; _ < n - 1; _++) {
    int u, v; cin >> u >> v;
    assert(1 <= u && u <= n);
    assert(1 <= v && v <= n);
    --u, --v;
    tree[u].emplace_back(v);
    tree[v].emplace_back(u);

    if (dsu.merge(u, v) == false) {
      assert(false);
    }
  }

  assert(dsu.size(0) == n);

  vector<int> euler_tour;
  vector<int> L(n), R(n);
  const function<void(int, int)> dfs = [&](int u, int fa) {
    L[u] = sz(euler_tour);
    euler_tour.emplace_back(u);
    for (const int &v : tree[u]) {
      if (v == fa) continue;
      dfs(v, u);
    }
    R[u] = sz(euler_tour);
  };
  dfs(0, 0);

  FenwickTree ft(n);
  for (int _ = 0; _ < q; _++) {
    int op, pos; cin >> op >> pos;
    assert(op == 1 || op == 2);
    assert(1 <= pos && pos <= n);
    --pos;

    if (op == 1) {
      ll d; cin >> d;
      assert((int) -1e9 <= d && d <= (int) 1e9);
      ft.range_add(L[pos], R[pos], -d);
    } else {
      cout << ft.range_query(L[pos], L[pos] + 1) + a[pos] << "\n";
    }
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}