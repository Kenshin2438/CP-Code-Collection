#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

ll qpow(ll x, ll n, ll mod) {
  ll res = 1LL;
  for (x %= mod; n > 0LL; n >>= 1, x = x * x % mod) {
    if (n & 1LL) res = res * x % mod;
  }
  return (res + mod) % mod;
}

// a^x EQUIV n (MOD mod), and gcd(a, mod) = 1
ll BSGS(ll a, ll n, ll mod) {
  a %= mod, n %= mod;
  if (n == 1LL || mod == 1LL) return 0LL;

  unordered_map<ll, ll> bs;
  ll S = sqrt(mod) + 1;

  ll base = n;
  for (ll k = 0, val = base; k <= S; k++) {
    bs[val] = k, val = val * a % mod;
  }
  base = qpow(a, S, mod);
  for (ll x = 1, val = base; x <= S; x++) {
    if (bs.count(val)) return x * S - bs[val];
    val = val * base % mod;
  }
  return -1;  // No solution
}

tuple<ll, ll> exgcd(ll a, ll b) {
  ll x = 1, y = 0, r = 0, s = 1;
  while (b != 0LL) {
    ll t = a / b;
    r ^= x ^= r ^= x -= t * r;
    s ^= y ^= s ^= y -= t * s;
    b ^= a ^= b ^= a %= b;
  }
  return {a, x};
}

void solve() {
  ll a, b, p;
  cin >> p >> a >> b;

  ll phi = p - 1;  // p is a prime number

  b %= p, a %= phi;

  vector<int> fact = [](int n) {
    vector<int> res;
    for (int i = 2; i * i <= n; i++) {
      if (n % i == 0) {
        res.push_back(i);
        while (n % i == 0) n /= i;
      }
    }
    if (n != 1) res.push_back(n);
    return res;
  }(phi);

  ll root = [&fact, &phi](int p) {
    for (ll res = 2; res < p; res++) {
      bool ok = true;
      for (const ll &x : fact) {
        if (qpow(res, phi / x, p) != 1) continue;
        ok = false;
        break;
      }
      if (ok) return res;
    }
    return -1LL;
  }(p);

  ll L = BSGS(root, b, p);
  auto [g, inv] = exgcd(a, phi);
  /**
   * root^log(b) \equiv b (mod p)
   * 
   * a * log(ans) \equiv log(b) (mod phi)
   **/
  if (L % g != 0) return cout << "No Solution\n", void();

  a /= g, L /= g;
  ll mod = phi / g;

  L = (inv * L % mod + mod) % mod;

  vector<ll> ans;
  for (; L < phi; L += mod) {
    ans.push_back(qpow(root, L, p));
  }

  sort(all(ans));
  for (const ll &x : ans) cout << x << ' ';

  cout << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T;
  cin >> T;

  while (T--) solve();
  return 0;
}