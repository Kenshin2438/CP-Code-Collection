#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

const int mod = 1e9 + 7;

ll qpow(ll x, ll n, ll mod) {
  ll res = 1LL;
  for (x %= mod; n; n >>= 1, x = x * x % mod) {
    if (n & 1LL) res = res * x % mod;
  }
  return res;
}

void solve() {
  int n, m; cin >> n >> m;
  string s; cin >> s;
  int l = count(all(s), '(');
  int r = count(all(s), ')');
  if (m & 1) return cout << "0\n", void();
  int mm = m / 2;
  if (l > mm || r > mm) return cout << "0\n", void();
  vector<int> p;
  for (int i = 0; i < n; i++) {
    if (s[i] == ')') p.push_back(i);
  }
  ll ans = 1LL;
  vector<vector<int>> dp(n, vector<int>(m));
  for (int i = 1; i < )
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
