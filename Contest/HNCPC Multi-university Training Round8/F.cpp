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
#define SZ(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

const ll mod = (int) 1e9 + 9;

ll qpow(ll x, ll n, ll mod) {
  ll res = 1LL;
  for (x %= mod; n > 0; n >>= 1, x = x * x % mod) {
    if (n & 1LL) res = res * x % mod;
  }
  return (res + mod) % mod;
}

void SingleTest(int TestCase) {
  str a, b, c; cin >> a >> b >> c;

  int n = max({a.length(), b.length(), c.length()});

  while ((int) a.length() < n) a += "#";
  a = "#" + a;
  while ((int) b.length() < n) b += "#";
  b = "#" + b;
  while ((int) c.length() < n) c += "#";
  c = "#" + c;

  vec<array<ll, 3>> suf(n + 2);
  for (int i = 1; i <= n; i++) {
    suf[i][0] = suf[i + 1][0] + (a[i] == '?');
    suf[i][1] = suf[i + 1][1] + (b[i] == '?');
    suf[i][2] = suf[i + 1][2] + (c[i] == '?');
  }

  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    
  }

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
