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

struct FenwickTree {
  vector<ll> s;
  FenwickTree(int n) : s(n) {}
  void update(int pos, ll dif) {
    for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
  }
  ll query(int pos) { // [0, pos)
    ll res = 0;
    for (; pos > 0; pos &= pos - 1) res += s[pos - 1];
    return res;
  }
};

void solve() {
  int n, m; cin >> n >> m;
  vector<pair<int, int> > x(n);
  for (int i = 0; i < n; i++) {
    cin >> x[i].first, x[i].second = i;
  }
  sort(all(x), [&](pair<int, int> &a, pair<int, int> &b){
    return a.first == b.first ? a.second < b.second : a.first < b.first;
  });

  FenwickTree FT(n);
  vector<ll> ans(n);
  ll S = 0;
  for (int i = 0, j = 0; i < n; i = j) {
    while (j < n && x[j].first == x[i].first) j++;
    S += x[i].first * 1LL * (j - i);
    for (int k = i; k < j; k++) {
      ans[x[k].second] = x[i].first * 1LL * j - S + FT.query(x[k].second);
      FT.update(x[k].second, 1);
    }
  }
  for (int i = 0; i < n; i++) {
    cout << (ans[i] >= m - 1 ? -1 : ans[i])  << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
