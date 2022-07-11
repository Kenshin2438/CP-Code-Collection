#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

const int mod = 1e9 + 7;

ll qpow(ll x, ll n, ll mod) {
  ll res = 1LL;
  for (x %= mod; n; n >>= 1, x = x * x % mod) {
    if (n & 1LL) res = res * x % mod;
  }
  return (res + mod) % mod;
}
ll inv(ll x) { return qpow(x, mod - 2, mod); }

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  ll n, k; cin >> n >> k;
  vector<ll> p(n);
  for (ll &x : p) cin >> x;

  ll ans = 1LL, M = *max_element(all(p)) + 1;
  if (M <= 2e5) {
    vector<ll> pw(M + 1, 0LL);
    for (int i = 1; i <= M; i++) {
      pw[i] = (qpow(i, k, mod) + pw[i - 1]) % mod;
    }
    for (ll &x : p) ans = ans * pw[x + 1] % mod;
  } else {
    vector<int> x(k + 3), y(k + 3);
    for (int i = 1; i <= k + 2; i++) {
      x[i] = i;
      y[i] = (y[i - 1] + qpow(i, k, mod)) % mod;
    }
    const auto lagrange = [&](ll N) -> ll {
      ll res = 0LL;
      for (int i = 1; i <= k + 2; i++) {
        ll tmp = y[i];
        for (int j = 1; j <= k + 2; j++) {
          if (i == j) continue;
          tmp = (N - x[j]) % mod * inv(x[i] - x[j]) % mod * tmp % mod;
        }
        res = (res + mod + tmp) % mod;
      }
      return res;
    };
    for (ll &x : p) ans = ans * lagrange(x + 1) % mod;
  }
  cout << ans << '\n';
  return 0;
}