#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#define sz(x) static_cast<int>((x).size())

template <typename T>
struct ST {
  vector<vector<T>> st;
  T f(const T &a, const T &b) { 
    return max<T>(a, b);
  }

  ST() = default;
  ST(const vector<T> &v) : st(1, v) {
    for (int pw = 1, k = 1; (pw << 1) <= sz(v); pw <<= 1, k++) {
      st.emplace_back(sz(v) - (pw << 1) + 1);
      for (int i = 0; i < sz(st[k]); i++) {
        st[k][i] = f(st[k - 1][i], st[k - 1][i + pw]);
      }
    }
  }
  ~ST() = default;

  T query(int l, int r) {  // query [l, r)
    if (l >= r) return -1;
    int dep = 31 - __builtin_clz(r - l);
    return f(st[dep][l], st[dep][r - (1 << dep)]);
  }
};

struct DSU {
  vector<int> p, pre;
  vector<vector<int>> a;
  ST<int> st;

  DSU() = default;
  DSU(int n) : p(n, -1), pre(n, 0), a(n) {
    for (int i = 0; i < n; i++) a[i].push_back(i);
  }
  ~DSU() = default;

  int find(int x) { return p[x] < 0 ? x : p[x] = find(p[x]); }
  int size(int x) { return -p[find(x)]; }
  bool same(int u, int v) { return find(u) == find(v); }
  bool merge(int u, int v, int val) {
    u = find(u), v = find(v);
    if (u == v) return false;

    if (sz(a[u]) > sz(a[v])) swap(u, v);
    for (const int &x : a[u]) {
      if (x + 1 < a.size() && find(x + 1) == v) {
        pre[x] = val;
      }
      if (x - 1 >= 0 && find(x - 1) == v) {
        pre[x - 1] = val;
      }
      a[v].emplace_back(x);
    }

    p[v] += p[u], p[u] = v;
    return true;
  }
  void init_rmq() { st = ST<int>(pre); }
};

void solve() {
  int n, m, q; cin >> n >> m >> q;
  DSU dsu(n);
  for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v;
    dsu.merge(--u, --v, i);
  }
  dsu.init_rmq();
  while (q--) {
    int l, r; cin >> l >> r;
    --l, --r;
    cout << dsu.st.query(l, r) + 1 << ' ';
  }
  cout << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T; cin >> T;
  while (T--) solve(); 
 
  return 0;
}