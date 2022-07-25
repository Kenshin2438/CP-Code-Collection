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
const int N = 4005;

struct FenwickTree {
#define SZ(a) static_cast<int>((a).size())
  vector<ll> s;
  FenwickTree(int n) : s(n) {}
  void update(int pos, ll dif) {
    for (; pos < SZ(s); pos |= pos + 1) {
      if ((s[pos] += dif) >= mod) s[pos] -= mod;
    }
  }
  ll query(int pos) { // [0, pos)
    ll res = 0;
    for (; pos > 0; pos &= pos - 1) {
      if ((res += s[pos - 1]) >= mod) res -= mod;
    }
    return res;
  }
};

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  
  int n; cin >> n;
  vector<pair<int, int>> p(n);
  for (auto &&[l, r] : p) cin >> l >> r;

  sort(all(p), [&](auto A, auto B) {
    return A.second == B.second
      ? A.first < B.first 
      : A.second < B.second;
  });
  vector<FenwickTree> S(n, FenwickTree(N));
  vector<vector<ll>> f(n, vector<ll>(n));
  for (int i = 0; i < n; i++) S[i].update(0, 1);
  ll ans = n;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      if (p[j].second < p[i].first) continue;
      if (p[j].first <= p[i].first) {
        f[i][j] = S[j].query(p[i].first);
      } else {
        f[i][j] = S[i].query(p[j].first);
      }
      S[i].update(p[j].second, f[i][j]);
      if ((ans += f[i][j]) >= mod) ans -= mod;
    }
  }
  cout << ans << '\n';
  return 0;
}