#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

void solve() {
  const int mod = 998244353;
  int n, q; cin >> n >> q;
  vector<vector<array<int, 3>>> p(n);
  for (auto &&v : p) {
    int m; cin >> m;
    v.resize(m);
    for (auto &&[a, b, c] : v) cin >> a >> b >> c;
  }

  vector f(n, vector<vector<int>>(401, vector<int>(401, 1e9)));
  for (int i = 0; i < n; i++) {
    for (const auto &[a, b, c] : p[i]) {
      f[i][a][b] = min(f[i][a][b], c);
    }
    for (int a = 1; a <= 400; a++) {
      for (int b = 1; b <= 400; b++) {
        f[i][a][b] = min(f[i][a][b - 1], f[i][a][b]);
      }
    }
    for (int a = 1; a <= 400; a++) {
      for (int b = 1; b <= 400; b++) {
        f[i][a][b] = min(f[i][a - 1][b], f[i][a][b]);
      }
    }
  }

  auto calc = [&](int a, int b, int c) -> int {
    int res = 0;
    for (int i = 0; i < n; i++) {
      res += c >= f[i][a][b];
    }
    return res;
  };

  ll ans = 0;
  int seed; cin >> seed;
  vector<ll> pw(q);
  for (int i = pw[0] = 1; i < q; i++) {
    pw[i] = pw[i - 1] * seed % mod;
  }
  std::mt19937 rng(seed);
  std::uniform_int_distribution<> u(1, 400);
  int lastans = 0;
  for (int i = 1; i <= q; i++) {
    int IQ = (u(rng) ^ lastans) % 400 + 1;  // The IQ of the i-th friend
    int EQ = (u(rng) ^ lastans) % 400 + 1;  // The EQ of the i-th friend
    int AQ = (u(rng) ^ lastans) % 400 + 1;  // The AQ of the i-th friend
    lastans = calc(IQ, EQ, AQ);            // The answer to the i-th friend
    ans = (ans + lastans * pw[q - i] % mod) % mod;
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
