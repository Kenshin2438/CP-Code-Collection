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
const int N = 34 * 4 - 13;

ll qpow(ll x, ll n, ll mod) {
  ll res = 1LL;
  for (x %= mod; n; n >>= 1, x = x * x % mod) {
    if (n & 1LL) res = res * x % mod;
  }
  return (res + mod) % mod;
}
ll inv(ll x) { return qpow(x, mod - 2, mod); }

ll dp[15][N + 10][15], g[15][N + 10], ans[N];

void init() {
  for (int k = 1; k <= 13; k += 2) {
    dp[k][0][k] = 1;
    for (int i = 1; i <= N; i++) {
      ll iv = inv(N - (i - 1));
      for (int j = 1; j <= k; j += 2) {
        dp[k][i][j] += (dp[k][i - 1][j] * iv % mod * max(0, N - (i - 1) - 3 * j) % mod) * int(N - i + 1 - 3 * j >= 0);
        if (j + 2 <= k) {
          dp[k][i][j] += (dp[k][i - 1][j + 2] * iv % mod * min(3 * (j + 2), N - (i - 1)) % mod) * int(3 * (j + 2) <= N - (i - 1));
        }

        dp[k][i][j] %= mod;
        // debug(k, i, j, dp[k][i][j]);
      }
    }
  }
  for (int num = 1; num <= 13; num += 2) {
    for (int i = 1; i <= N; i++) {
      ans[num] = (ans[num] + dp[num][i - 1][1] * i % mod * inv(N - (i - 1)) % mod * min(3, N - (i - 1)) % mod) % mod;
    }
  }
}

void solve(int id) {
  string s; cin >> s;
  map<string, int> cnt;
  for (int i = 0; i + 1 < (int) s.length(); i += 2) {
    string t = s.substr(i, 2);
    cnt[t] += 1;
  }
  debug(cnt);
  int num = 0;
  for (auto [_, k] : cnt) num += int(k == 1);
  debug(num);
  cout << "Case #" << id << ": ";
  cout << ans[num] << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  init();

  int T, id = 0; cin >> T;
  while (T--) solve( ++ id );
  
  return 0;
}