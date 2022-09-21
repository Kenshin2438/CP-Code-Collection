
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

const ll mod = 1e9 + 7;
ll add(ll a, ll b) { return a += b, (a >= mod ? a - mod : a); }
ll sub(ll a, ll b) { return a -= b, (a < 0 ? a + mod : a); }
ll mul(ll a, ll b) {
  // using ull = unsigned long long;
  // // 利用溢出机制 (a * b) \equiv ((a / mod) * b * mod) + R \pmod{2^64}
  // return (a * b - ull((long double)a / mod * b) * mod + mod) % mod;
  return a * b % mod;
}

const int N = 1e6;
vector<int> p, mu(N + 10);
bitset<N + 10> ntp;
void init() {
  mu[1] = 1;
  for (int i = 2; i <= N; i++) {
    if (ntp[i] == 0) p.emplace_back(i), mu[i] = mod - 1;
    for (const int &pr : p) {
      if (pr * 1LL * i > N) break;
      ntp[pr * i] = 1;
      if (i % pr == 0) break;
      mu[pr * i] = mod - mu[i];
    }
  }
  for (int i = 1; i <= N; i++) mu[i] = add(mu[i], mu[i - 1]);
}

unordered_map<int, ll> sm;
ll sieve(int n) {
  if (n <= N) return mu[n];
  if (sm.count(n)) return sm[n];
  ll res = 1;
  for (int l = 2, r, bn; l <= n; l = r + 1) {
    r = n / (bn = n / l);
    res = sub(res, mul(sieve(bn), r - l + 1));
  }
  return sm[n] = res;
}

ll inv(ll x) { return x == 1LL ? x : mul(inv(mod % x), mod - mod / x); }
const ll iv2 = inv(2);
ll G(ll x) { return mul(iv2, mul(x, x + 1)); }
ll H(ll p, ll e, ll pe) { return sub(p, mul(p, p)); }

ll PN(int id, ll n, ll h) {
  ll res = mul(G(n), h);
  for (int i = id; i < (int)p.size(); i++) {
    ll val = n / p[i], pe = p[i], e = 1;
    if (val < p[i]) break;
    while (val >= p[i]) {
      val /= p[i], pe *= p[i], e += 1;
      res = add(res, PN(i + 1, val, mul(H(p[i], e, pe), h)));
    }
  }
  return res;
}

void solve() {
  int n; cin >> n;
  ll ans = PN(0, n, 1);
  ans = mul(ans, ans);
  debug(ans);
  for (int l = 2, r, bn; l <= n; l = r + 1) {
    r = n / (bn = n / l);
    ll S = R(bn, ); S = mul(S, S);
    debug(l, r, bn, S);
    ans = sub(ans, mul(S, sub(sieve(l - 1), sieve(r))));
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  init();

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
