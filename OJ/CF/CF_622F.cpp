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

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, k; cin >> n >> k;

  vector<ll> y(k + 3, 0); 
  for (int i = 1; i <= k + 2; i++) {
    y[i] = (y[i - 1] + qpow(i, k, mod)) % mod;
  }
  if (n <= k + 2) return cout << y[n] << '\n', 0; 

  vector<ll> inv(k + 3, 1);
  for (int i = 2; i <= k + 2; i++) {
    inv[i] = inv[mod % i] * (mod - mod / i) % mod;
  } 
  for (int i = 2; i <= k + 2; i++) {
    inv[i] = inv[i - 1] * inv[i] % mod;
  }

  vector<ll> pre(k + 4, 1), suf(k + 4, 1);
  for (int i = 1; i <= k + 2; i++) pre[i] = pre[i - 1] * (n - i) % mod;
  for (int i = k + 2; i >= 1; i--) suf[i] = suf[i + 1] * (n - i) % mod;

  ll ans = 0;
  for (int i = 1; i <= k + 2; i++) {
    ll P = inv[i - 1] * inv[k + 2 - i] % mod * y[i] % mod;
    ll Q = pre[i - 1] * suf[i + 1] % mod;
    if ((k + 2 - i) & 1) Q = mod - Q;
    ans = (ans + P * Q % mod) % mod;
  }
  cout << ans << '\n';
  return 0;
}