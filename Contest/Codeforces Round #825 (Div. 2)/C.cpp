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

void solve1() {
  int n; cin >> n;
  vector<int> a(n);
  for (int &x : a) cin >> x;

  ll ans = 0;
  for (int l = 0, r = 0; l < n; l++) {
    while (r < n && a[r] >= (r - l + 1)) r++;
    ans += r - l;
  }
  cout << ans << "\n";
}

void solve2() {
  int n; cin >> n;
  vector<ll> a(n + 1);
  for (int i = 1; i <= n; i++) cin >> a[i];

  vector<ll> S1(n + 1), S2(n + 1);
  vector<int> f(n + 1), s(n + 1);
  for (int l = 1, r = 1, t = 1; l <= n; l++) {
    while (r <= n && a[r] >= r - l + 1) f[r] = l, r++;

    t = min(max(t, r + 1), n + 1);
    while (t <= n && a[t] >= t - l + 1) t += 1;

    if (s[r] == 0) s[r] = l;
    S1[l] = S1[l - 1] + (r - l);
    S2[l] = S2[l - 1] + (t - l);
  }

  int q; cin >> q;
  while (q--) {
    int p, x; cin >> p >> x;
    ll ans = S1[n];
    if (x < a[p] && f[p] <= p - x) {
      ans -= S1[p - x] - S1[f[p] - 1];
      ans += (p - x - f[p] + 1) * 1LL * (x + p - f[p]) / 2;
    } else if (x > a[p] && s[p]) {
      ans -= S1[f[p] - 1] - S1[max(p - x, s[p] - 1)];
      ans += S2[f[p] - 1] - S2[max(p - x, s[p] - 1)];
    }
    cout << ans << "\n";
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  // int T = 1;
  // cin >> T;
  // while (T--) solve1();

  int T = 1;
  // cin >> T;
  while (T--) solve2();

  return 0;
}
