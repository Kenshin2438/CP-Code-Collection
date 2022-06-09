#include <bits/stdc++.h>
using namespace std;

using ll = long long;

ll qpow(ll x, ll n, ll mod) {
  ll res = 1LL;
  for (x %= mod; n > 0LL; n >>= 1, x = x * x % mod) {
    if (n & 1LL) res = res * x % mod;
  }
  return (res + mod) % mod;
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  ll a, b, c; cin >> a >> b >> c;

  cout << qpow(a, b, c) << '\n';
  return 0;
}