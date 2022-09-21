#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

int qpow(int x, int n, int mod) {
  int res = 1;
  for (; n > 0; n >>= 1, x = x * 1LL * x % mod) {
    if (n & 1) res = res * 1LL * x % mod;
  }
  return res;
}

int P, a, n, q;
int inv(int x) { return qpow(x, P - 2, P); }
unordered_map<int, int> BS;

void solve() {
  cin >> P >> a >> n >> q;

  ll val = 1;
  BS.clear();
  for (int i = 0; i <= 2e5; i++) {
    if (!BS.count(val)) BS[val] = i;
    val = val * 1LL * a % P;
  }

  vector<pair<int, int>> tr;
  int zero = 0;
  for (int i = 0; i < n; i++) {
    int s, d; cin >> s >> d;
    if (s == 0) zero += 1;
    else tr.emplace_back(inv(s), d);
  }
  for (int x; q--;) {
    cin >> x;
    if (x == 0) {
      cout << zero << '\n';
    } else {
      int ans = 0;
      for (int i = 0; i < (int)tr.size(); i++) {
        int s = tr[i].first;
        int d = tr[i].second;

        int X = x * 1LL * s % P;
        if (BS.count(X) && BS[X] <= d) ans += 1;
      }
      cout << ans << '\n';
    }
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
