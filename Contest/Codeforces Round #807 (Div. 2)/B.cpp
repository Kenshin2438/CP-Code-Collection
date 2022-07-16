#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

void solve() {
  int n; cin >> n;
  vector<ll> a(n);
  for (ll &x : a) cin >> x;

  ll ans = 0;

  int p = 0;
  while (p < n && a[p] == 0) p++;

  ll S = 0;
  for (int i = p; i < n - 1; i++) {
    if (a[i] == 0) {
      ans += 1;
    } else {
      S += a[i];
    }
  }
  cout << ans + S << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T; cin >> T;
  while (T--) solve();

  return 0;
}