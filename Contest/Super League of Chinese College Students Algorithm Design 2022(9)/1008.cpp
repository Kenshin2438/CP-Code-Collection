#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

const int mod = 998244353, N = 1e7;

int mu[N + 10];
bitset<N + 10> ntp;
vector<int> p;

void init() {
  // clock_t S = clock();

  ntp[0] = ntp[1] = 1;

  mu[1] = 1;
  for (int i = 2; i <= N; i++) {
    if (!ntp[i]) p.emplace_back(i), mu[i] = mod - 1;
    for (const int &pr : p) {
      if (pr * 1LL * i > N) break;
      ntp[pr * i] = 1;
      if (i % pr == 0) break;
      mu[pr * i] = mod - mu[i];
    }
  }

  // clock_t T = clock();
  // debug(double(T - S) / 1000);
}

void solve() {
  int n; cin >> n;
  int q; cin >> q;

  for (int a, b; q--; ) {
    cin >> a >> b;

    int g = __gcd(a, b);
    if (g == 1) {
      cout << "1 1\n";
      continue;
    }

    vector<int> d;
    for (const int &pr : p) {
      if (pr * 1LL * pr > max(a, b)) break;
      if (a % pr == 0 || b % pr == 0) {
        // debug(pr);
        d.emplace_back(pr);
        while (a % pr == 0) a /= pr;
        while (b % pr == 0) b /= pr;
      }
    }

    if (a == b) {
      if (ntp[a] == 0) d.emplace_back(a);
    } else {
      if (ntp[a] == 0) d.emplace_back(a);
      if (ntp[b] == 0) d.emplace_back(b);
    }

    vector<ll> D(1 << sz(d)); D[0] = 1;
    for (int i = 0; i < sz(d); i++) D[1 << i] = d[i];
    for (int mask = 0; mask < (1 << sz(d)); mask += 1) {
      D[mask] = D[mask ^ (mask & -mask)] * D[mask & -mask];
    }

    ll ans = 0;
    for (const ll &x : D) {
      if (x <= n) ans = (ans + (n / x) * 1LL * mu[x] % mod) % mod;
    }
    cout << 2 << ' ' << (ans + (g == 2)) % mod << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  init();

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
