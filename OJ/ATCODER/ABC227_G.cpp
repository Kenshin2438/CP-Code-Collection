#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

constexpr int LIM = 1e6 + 10;
vector<int> eratosthenes() {
  constexpr int S = 1e3, R = LIM / 2;
  vector<int> pr = {2}, sieve(S + 1);
  pr.reserve(int(LIM / log(LIM) * 1.1));
  vector<pair<int, int> > cp;
  for (int i = 3; i <= S; i += 2)
    if (!sieve[i]) {
      cp.push_back({i, i * i / 2});
      for (int j = i * i; j <= S; j += 2 * i) sieve[j] = 1;
    }
  for (int L = 1; L <= R; L += S) {
    array<bool, S> block{};
    for (auto &[p, idx] : cp)
      for (int i = idx; i < S + L; idx = (i += p)) block[i - L] = 1;
    for (int i = 0; i < min(S, R - L); i++)
      if (!block[i]) pr.push_back((L + i) * 2 + 1);
  }
  return pr;
}

const int mod = 998244353;

ll pot(ll p, ll n) {
  ll res = 0;
  while (n) res += n /= p;
  return res;
}

void solve() {
  ll n, k; cin >> n >> k;
  auto prime = eratosthenes();

  unordered_map<ll, ll> e;
  for (const int &p : prime)
    e[p] = pot(p, n) - pot(p, n - k) - pot(p, k);
  bitset<LIM> isp; isp.set();
  {
    ll l = max(2LL, n - k + 1), r = n;
    for (const int &p : prime) {
      for (ll x = max(2LL, (l + p - 1) / p) * p; x <= r; x += p) {
        isp[x - l] = false;
      }
    }
    for (ll x = l; x <= r; x++) if (isp[x - l] && x > prime.back()) {
      e[x] += 1;
    }
  }
  ll ans = 1;
  for (auto [_, t] : e) ans = (t + 1) % mod * ans % mod;
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
