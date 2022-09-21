#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) static_cast<int>((x).size())

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

void solve() {
  int n, q; cin >> n >> q;
  vector<vector<int>> tree(n);
  for (int i = 1; i < n; i++) {
    int x; cin >> x; --x;
    tree[x].push_back(i);
  }
  vector<set<int>> A(n), B(n), C(n);
  for (int i = 0; i < q; i++) {
    int As, Bs, Cs;
    cin >> As >> Bs >> Cs;
    while (As--) {
      int x; cin >> x; --x;
      A[x].insert(i);
    }
    while (Bs--) {
      int x; cin >> x; --x;
      B[x].insert(i);
    }
    while (Cs--) {
      int x; cin >> x; --x;
      C[x].insert(i);
    }
  }
  vector<int> dep(n), ans(q);
  vector<map<int, int>> Q(n);
  function<void(int)> dfs = [&](int u) {
    for (const int &v : tree[u]) {
      dep[v] = dep[u] + 1;
      dfs(v);
      { // merge set A
        if (sz(A[u]) < sz(A[v])) swap(A[u], A[v]);
        A[u].merge(A[v]);
      }
      { // merge set B
        if (sz(B[u]) < sz(B[v])) swap(B[u], B[v]);
        B[u].merge(B[v]);
      }
      { // merge map of Queries
        
      }
    }

    for (const int &x : C[u]) {
      auto it = Q[u].lower_bound(x);
      if (it != Q[u].end() && (it->first == x)) {
        ans[x] += it->second - dep[u] + 1;
        it->second = dep[u] - 1;
      }
    }

    debug(u + 1, Q[u]);
    debug(A[u]);
    debug(B[u]);
  };
  dfs(0);
  for (const int &x : ans) cout << x << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}

/**
1
7 1
1 1 2 2 3 3
2 1 1
4 5
6
1
**/
