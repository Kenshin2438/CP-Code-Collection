#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

template<int mod = 998244353>
struct Basis {
  vector<vector<int>> B;

  Basis(int n) { B.resize(n, vector<int>(n)); }
  int inv(int x) {
    return x == 1 ? 1 : (mod - mod / x) * 1LL * inv(mod % x) % mod;
  }
  bool insert(vector<int> v) {
    for (int i = v.size() - 1; i >= 0; i--) {
      if (v[i] == 0) continue;
      if (B[i][i] == 0) {
        B[i] = v;
        return true;
      }
      int t = v[i] * 1LL * inv(B[i][i]) % mod;
      for (int j = i; j >= 0; j--) {
        v[j] = (v[j] - B[i][j] * 1LL * t % mod + mod) % mod;
      }
    }
    return false;
  }
};

void solve() {
  int n, m; cin >> n >> m;
  vector<pair<int, vector<int>>> a(n);
  for (auto &&p : a) {
    p.second.resize(m);
    for (auto &&x : p.second) cin >> x;
  }
  for (auto &&p : a) cin >> p.first;
  sort(all(a));
  Basis B(m);
  int ans = 0, cnt = 0;
  for (const auto &[cost, v] : a) {
    if (B.insert(v)) ans += cost, cnt += 1;
  }
  cout << cnt << ' ' << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
