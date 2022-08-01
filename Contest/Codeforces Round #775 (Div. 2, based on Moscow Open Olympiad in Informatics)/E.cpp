#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

const int mod = 998244353;
const int N = 2e5 + 10;

ll fac[N], cnt[N];

struct FenwickTree {
#define SZ(a) static_cast<int>((a).size())
  vector<ll> s;
  FenwickTree(int n) : s(n) {}
  void update(int pos, ll dif) {
    for (; pos < SZ(s); pos |= pos + 1) s[pos] += dif;
  }
  ll query(int pos) {
    ll res = 0;
    for (; pos > 0; pos &= pos - 1) res += s[pos - 1];
    return res;
  }
};

ll inv(ll x) {
  return x == 1 ? x : (mod - mod / x) * inv(mod % x) % mod;
}

void solve() {
  int n, m; cin >> n >> m;
  for (int i = 1; i <= n; i++) {
    int x; cin >> x; cnt[x] += 1;
  }
  FenwickTree FT(N);

  ll D = 1;
  for (int i = 1; i <= 2e5; i++) {
    D = D * fac[cnt[i]] % mod;
    FT.update(i, cnt[i]);
  }
  D = inv(D);

  ll ans = 0, num = n;
  for (int i = 0; i < m; i++) {
    int t; cin >> t;
    if (num - 1 < 0) continue;
    debug(FT.query(t));
    ans = (ans + D * FT.query(t) % mod * fac[num - 1] % mod) % mod;
    // debug(ans);
    if (cnt[t]) {
      D = D * cnt[t] % mod;
      cnt[t] -= 1;
      num -= 1;
      FT.update(t, -1);
    } else break;
  }
  if (num == 0 && n < m) (ans += 1) %= mod;
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  for (int i = fac[0] = 1; i < N; i++) fac[i] = fac[i - 1] * i % mod;

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
