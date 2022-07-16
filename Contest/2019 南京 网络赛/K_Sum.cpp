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
const int iv6 = 166666668;
const int N = 1e6 + 10;

ll F[N];
unordered_map<ll, ll> S;

void init() {
  bitset<N> ntp;
  vector<int> p;

  F[1] = 1;
  for (int i = 2; i < N; i++) {
    if (ntp[i] == 0) {
      p.emplace_back(i);
      F[i] = (i * 1LL * i + mod - 1) % mod;
    }
    for (const int &pr : p) {
      if (pr * 1LL * i >= N) break;
      ntp[pr * i] = 1;
      if (i % pr == 0) {
        F[pr * i] = F[i] * (pr * 1LL * pr % mod) % mod;
        break;
      } else {
        F[pr * i] = F[i] * 1LL * F[pr] % mod;
      }
    }
  }
  for (int i = 2; i < N; i++) {
    F[i] = (F[i - 1] + F[i]) % mod;
  }
}

int stringMod(const string &s, int mod) {
  int res = 0;
  for (const char &c : s) {
    res = (res * 10LL + c - '0') % mod;
  }
  return res;
}

ll qpow(ll x, ll n, ll mod) {
  ll res = 1LL;
  for (x %= mod; n; n >>= 1, x = x * x % mod) {
    if (n & 1LL) res = res * x % mod;
  }
  return (res + mod) % mod;
}
ll inv(ll n) { return qpow(n, mod - 2, mod); }

ll sum2(ll n) {
  n %= mod;
  return n * (n + 1) % mod * (2 * n + 1) % mod * iv6 % mod;
}

ll sieve(ll n) {
  if (n < N) return F[n];
  if (S.count(n)) return S[n];
  ll res = sum2(n);
  for (ll l = 2, r; l <= n; l = r + 1) {
    r = n / (n / l);
    res = (res - (r - l + 1) % mod * sieve(n / l) % mod + mod) % mod;
  }
  return S[n] = res;
}

void solve() {
  int n; cin >> n;
  string s; cin >> s;

  int sk = (stringMod(s, mod) + mod - 1) % mod;
  int pw = stringMod(s, mod - 1);

  ll ans = 0LL;
  for (ll l = 1, r, bn; l <= n; l = r + 1) {
    r = n / (bn = n / l);
    if (bn == 1) {
      bn = sk;
    } else {
      bn = bn * (qpow(bn, pw, mod) + mod - bn) % mod * inv(bn - 1) % mod; 
    }
    ans = (ans + (sieve(r) - sieve(l - 1) + mod) % mod * bn % mod);
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  
  assert(iv6 == qpow(6, mod - 2, mod));

  init();
  int T; cin >> T;
  while (T--) solve();

  return 0;
}