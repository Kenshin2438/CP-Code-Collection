#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

void solve() {
  int n, m; cin >> n >> m;
  vector<ll> cnt(n + 1, 0);
  vector<int> a(m);
  for (int &x : a) cin >> x, ++ cnt[x];

  ll l = 0, r = 2 * m, ans = -1;
  while (l <= r) {
    ll M = (l + r) >> 1;

    ll T = 0, S = 0;
    for (int i = 1; i <= n; i++) {
      if (M >= cnt[i]) S += (M - cnt[i]) / 2;
      else T += cnt[i] - M;
    }
    bool ok = T <= S;

    if (ok) {
      ans = M, r = M - 1;
    } else {
      l = M + 1;
    }
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T = 1;
  cin >> T;
  while (T--) solve();
  return 0;
}