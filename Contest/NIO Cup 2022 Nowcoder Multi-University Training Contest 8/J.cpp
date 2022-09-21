#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

const int N = 1e4;
vector<int> p;
bitset<N> ntp;
void init() {
  for (int i = 2; i < N; i++) {
    if (ntp[i] == 0) p.emplace_back(i);
    for (const int &pr : p) {
      if (pr * 1LL * i >= N) break;
      ntp[pr * i] = 1;
      if (i % pr == 0) break;
    }
  }
  debug(p.size()); // p.size() >= Vertex number
}

void solve() {
  int n; cin >> n;
  vector<vector<int>> tree(n);
  for (int i = 1; i < n; i++) {
    int u, v; cin >> u >> v;
    --u, --v;
    tree[u].emplace_back(v);
    tree[v].emplace_back(u);
  }

  using ull = unsigned long long;
  vector<int> siz(n);
  vector<ull> H(n);
  static const function<void(int, int)> dfs = [&](int u, int fa) {
    H[u] = 1, siz[u] = 1;
    for (const int &v : tree[u]) {
      if (v != fa) {
        dfs(v, u), siz[u] += siz[v], H[u] += H[v] * p[siz[v]];
      }
    }
  };
  dfs(0, 0);


  int rt1 = -1, rt2 = -1;
  vector<ull> G(n); G[0] = H[0];
  static const function<void(int, int)> sol = [&](int u, int fa) {
    for (const int &v : tree[u]) {
      if (v != fa) {
        G[v] = H[v] + (G[u] - H[v] * p[siz[v]]) * p[n - siz[v]];
        if (G[u] - H[v] * p[siz[v]] == H[v]) rt1 = v, rt2 = u;
        sol(v, u);
      }
    }
  };
  sol(0, 0);

  static const function<void(int, int, int)> S = [&](int u, int fa, int W) {
    if (W == -1) {
      sort(all(tree[u]), [&](int a, int b) { return H[a] < H[b]; });
      for (const int &v : tree[u]) if (v != fa) S(v, u, W);
    } else if (W == +1) {
      sort(all(tree[u]), [&](int a, int b) { return H[a] > H[b]; });
      for (const int &v : tree[u]) if (v != fa) S(v, u, W);
    } else {
      ull cur = 0;
      for (const int &v : tree[u]) if (v != fa) cur ^= H[v];
      
    }
  };

  if (~rt1 && ~rt2) {
    dfs(rt1, rt2), dfs(rt2, rt1);
    S(rt1, rt2, -1), S(rt2, rt1, +1);
    return;
  }

  int rt = -1;
  vector<int> candidate;
  const function<void(int, int)> get = [&](int u, int fa) {
    if (~rt) return;

    unordered_map<ull, int> Mp;
    for (const int &v : tree[u]) {
      if (v == fa) {
        Mp[ G[fa] - H[u] * siz[u] ] += 1;
      } else {
        Mp[ H[v] ] += 1;
      }
    }
    int odd = 0;
    for (const auto &[_, t] : Mp) odd += t & 1;
    if (odd == 0) return rt = u, void();
    if (odd == 1) candidate.emplace_back(u);

    for (const int &v : tree[u]) if (v != fa) get(v, u);
  };
  get(0, 0);

  if (rt == -1) return cout << "NO\n", void();
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  init();

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
