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

void solve() {
  int n, m; cin >> n >> m;
  vector<vector<int>> G(n);
  for (int i = 0; i < m; i++) {
    int u, v; cin >> u >> v; 
    --u, --v;
    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }

  vector<pair<int, int>> E;
  for (int root = 0; root < n; root++) {
    if (sz(G[root]) < 4) continue;

    // set<int> vS(all(G[root]));
    // vector<int> vised(n, 0);
    vector<int> pre(n, -1), fpre(n); iota(all(fpre), 0);
    const function<int(int)> f = [&](int x) {
      return x == fpre[x] ? x : fpre[x] = f(fpre[x]);
    };

    queue<int> Q;
    for (const int &x : G[root]) {
      fpre[x] = pre[x] = x; Q.emplace(x); 
    }

    while (!Q.empty()) {
      int U = Q.front(); Q.pop();

      for (int V : G[U]) {
        if (V == root) continue;

        if (pre[V] == -1) {
          fpre[V] = pre[V] = U; Q.emplace(V);
        } else {
          if (f(V) != f(U)) {
            E.emplace_back(V, U);
            while (U != pre[U]) {
              E.emplace_back(U, pre[U]);
              U = pre[U];
            }
            E.emplace_back(root, U);

            while (V != pre[V]) {
              E.emplace_back(V, pre[V]);
              V = pre[V];
            }
            E.emplace_back(root, V);

            int t = 0;
            for (int x : G[root]) {
              if (x == U || x == V) continue;
              E.emplace_back(root, x); t++;
              if (t == 2) break;
            }

            goto END;
          }
        }
      }
    }
  }

END:
  if (E.empty()) {
    cout << "NO\n";
  } else {
    cout << "YES\n" << sz(E) << '\n';
    for (const auto &[u, v] : E) {
      cout << u + 1 << ' ' << v + 1 << '\n';
    }
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}