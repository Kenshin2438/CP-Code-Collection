#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

void solve() {
  int n, q; cin >> n >> q;
  vector<ll> a(n);
  for (ll &x : a) cin >> x;

  vector<int> fact;
  {
    int m = n;
    for (int x = 2; x * x <= m; x++) {
      if (m % x == 0) {
        fact.emplace_back(n / x);
        while (m % x == 0) m /= x;
      }
    }
    if (m != 1) fact.emplace_back(n / m);
  }

  vector<vector<ll>> S(sz(fact));
  vector<multiset<ll>> M(sz(S));
  for (int i = 0; i < sz(S); i++) {
    const int d = fact[i];
    S[i].assign(d, 0);
    for (int j = 0; j < n; j++) S[i][j % d] += a[j];
    M[i] = move( multiset<ll>(all(S[i])) );
  }

  const auto modify = [&](int p, int x) {
    for (int i = 0; i < sz(M); i++) {
      const int d = fact[i];
      M[i].erase(M[i].find(S[i][p % d]));
      S[i][p % d] -= a[p] - x;
      M[i].insert(S[i][p % d]);
    }
    a[p] = x;
  };
  const auto query = [&]() {
    ll res = 0;
    for (int i = 0; i < sz(M); i++) {
      const int d = fact[i];
      res = max(res, *M[i].rbegin() * d);
    }
    return res;
  };

  cout << query() << '\n';
  for (int p, x; q--;) {
    cin >> p >> x, --p;
    modify(p, x);
    cout << query() << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
