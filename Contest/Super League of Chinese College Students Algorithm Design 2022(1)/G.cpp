#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

struct FenwickTree {
#define SZ(a) static_cast<int>((a).size())
  vector<ll> s;
  FenwickTree(int n) : s(n) {}
  void update(int pos, ll dif) {
    for (; pos < SZ(s); pos |= pos + 1) s[pos] += dif;
  }
  ll query(int pos) {
    ll res = 0;
    for (; pos > 0; pos &= pos - 1) res += s[pos - 1];
    return res;
  }
};

void solve() {
  int n, m, q;
  cin >> n >> m >> q;
  vector<int> c(n), val(n);
  vector<vector<int>> type(n);
  for (int i = 0; i < n; i++) {
    cin >> c[i];
    type[--c[i]].push_back(i);
  }
  for (int &x : val) cin >> x;

  vector<array<int, 3>> E(m);
  for (auto &e : E) cin >> e[1] >> e[2] >> e[0];
  sort(all(E));

  vector<int> p(n * 2); iota(all(p), 0);
  function<int(int)> fid = [&](int x) {
    return x == p[x] ? x : p[x] = fid(p[x]);
  };

  vector<vector<int>> tree(n * 2);
  vector<int> cost(n * 2);
  int cur = n;
  for (const auto &e : E) {
    int u = fid(e[1]), v = fid(e[2]);
    if (u == v) continue;
    tree[cur].push_back(v);
    tree[cur].push_back(u);
    cost[cur] = e[0];
    p[u] = p[v] = cur++;
  }
  assert(cur == n * 2 - 1);

  vector<int> siz(n * 2), dfn(n * 2), dep(n * 2), node_of_pos(n * 2);
  int idx = 0;
  const int M = 20;
  vector<array<int, M>> par(n * 2);

  function<void(int, int)> dfs = [&](int u, int fa) {
    dep[u] = dep[fa] + 1, siz[u] = 1;

  };
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  for (int i = 1; i < N; i++) {
    lg[i] = lg[i - 1] + (1 << lg[i - 1] == i);
  }

  int T; cin >> T;
  while (T--) solve();
  
  return 0;
}