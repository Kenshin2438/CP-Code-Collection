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
  int n; cin >> n;
  vector<int> d(n - 1), t(n);
  for (auto &x : d) cin >> x;
  for (auto &x : t) cin >> x;

  vector<pair<ll, ll>> a(n), b(n);
  a.front() = {0, t.front()};
  for (int i = 1; i < n; i++) {
    a[i].first = a[i - 1].second + d[i - 1];
    a[i].second = a[i].first + t[i];
  }
  b.back() = {0, t.back()};
  for (int i = n - 2; i >= 0; i--) {
    b[i].first = b[i + 1].second + d[i];
    b[i].second = b[i].first + t[i];
  }
  debug(a), debug(b);
  const auto U = [](pair<ll, ll> a, pair<ll, ll> b) -> ll {
    return max(0LL, min(a.second, b.second) - max(a.first, b.first));
  };

  ll ans = 0;
  for (int i = 0; i < n; i++) {
    ans += U(a[i], b[i]);
  }
  cout << ans << "\n";
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}