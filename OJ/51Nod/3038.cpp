#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

#define PII pair<int, int>
#define vec vector
#define str string
#define fi first
#define se second
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define sz(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

ll qpow(ll x, ll n, ll mod) {
  ll res = 1LL;
  for (x %= mod; n > 0; n >>= 1, x = x * x % mod) {
    if (n & 1LL) res = res * x % mod;
  }
  return (res + mod) % mod;
}

void SingleTest(__attribute__((unused)) int TestCase) {
  const int mod = 10007;

  int n, k; cin >> n >> k;

  vec<int> pw(mod); iota(all(pw), 0);
  for (int &x : pw) x = qpow(x, k, mod);

  ll ans = 0;
  for (int i = 1; i <= n % mod; i++) {
    ans = (ans + pw[i]) % mod;
  }
  ans = (ans + accumulate(all(pw), 0LL) % mod * (n / mod) % mod) % mod;

  cout << ans << '\n'; 
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
