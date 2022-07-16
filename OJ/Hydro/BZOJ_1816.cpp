#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  
  int n, m; cin >> n >> m;
  vector<ll> c(n);
  for (ll &x : c) cin >> x;

  auto check = [&](ll M) -> bool {
    ll S = 0;
    for (const ll &x : c) S += max(0LL, M - x);
    if (S > m || S > M) return false;
    return true;
  };

  ll l = 0, r = 1e9, ans = -1;
  while (l <= r) {
    ll mid = (l + r) >> 1;

    if (check(mid)) {
      ans = mid, l = mid + 1;
    } else {
      r = mid - 1;
    }

  }
  cout << ans << '\n';
  return 0;
}