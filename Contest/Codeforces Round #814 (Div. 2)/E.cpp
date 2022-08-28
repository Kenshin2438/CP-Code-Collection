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
  static map<ll, int> Mp { {1, 0}, {2, 1} };
  static vector<ll> fib { 1, 1 };
  static ll pre = 2;
  for (static int id = 0; id < 55; id++) {
    fib.push_back(fib[sz(fib) - 1] + fib[sz(fib) - 2]);
    Mp[pre += fib.back()] = sz(fib) - 1;
  }
  // debug(Mp);

  int n; cin >> n;
  vector<ll> c(n);
  for (ll &x : c) cin >> x;
  ll SUM = accumulate(all(c), 0LL);

  if (Mp.count(SUM) == 0) return cout << "NO\n", void();
  static const function<bool(int, int)> dfs = [&](int now, int last) {
    if (now == -1) return true;
    for (int i = 0; i < n; i++) {
      if (i != last && c[i] >= fib[now]) {
        c[i] -= fib[now];
        if (dfs(now - 1, i)) return true;
        c[i] += fib[now];
      }
    }
    return false;
  };
  cout << (dfs(Mp[SUM], -1) ? "YES" : "NO") << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
