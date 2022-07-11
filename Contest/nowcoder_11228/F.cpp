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

void SingleTest(__attribute__((unused)) int TestCase) {
  int n; cin >> n;
  vec<ll> a(n);
  for (ll &x : a) cin >> x;

  vec<ll> s(n + 1, 0), t(n + 1);
  partial_sum(all(a), next(begin(s), 1));
  partial_sum(all(s), begin(t));

  const int mod = (int) 1e9 + 7;
  vec<ll> inv(n + 1, 1);
  for (int i = 2; i <= n; i++) {
    inv[i] = inv[mod % i] * (mod - mod / i) % mod;  
  }

  /**
   * 
   * ans = \sum_{i=1}^{n}\sum_{j=i}^{n} (pre[j] - pre[j - i]) * inv(i)
   *     = \sum_{i=1}^{n} [(S[n] - S[i - 1]) - (S[n - i])] * inv(i) 
   * 
   **/

  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    ans = (ans + (t[n] - t[i - 1] - t[n - i] + mod) % mod * inv[i] % mod) % mod;
  }
  cout << ans << '\n';
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  // cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}