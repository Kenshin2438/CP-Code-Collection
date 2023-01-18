#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

struct FenwickTree {
  vector<ll> s, d;

  FenwickTree() = default;
  FenwickTree(int n) : s(n), d(n) {}

  void add(int p, ll dif) {
    ll val = (p + 1) * dif;
    for (; p < s.size(); p |= p + 1) {
      s[p] += val, d[p] += dif;
    }
  }
  ll query(int i) {
    ll S = 0LL, D = 0LL;
    for (int p = i; p > 0; p &= p - 1) {
      S += s[p - 1], D += d[p - 1];
    }
    return D * (i + 1) - S;
  }
  void range_add(int l, int r, ll val) {  // [l, r)
    add(l, val), add(r, -val);
  }
  ll range_query(int l, int r) {  // [l, r)
    return query(r) - query(l);
  }
};

void solve() {
  int n; cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  sort(all(a));
  vector<int> cnt = {1};
  for (int i = 1; i < n; i++) {
    if (a[i] == a[i - 1]) {
      cnt.back() += 1;
    } else {
      cnt.emplace_back(1);
    }
  }
  debug(cnt);
  FenwickTree ft(n + 1);
  vector<ll> ans(n + 1);
  for (const int &x : cnt) {
    ft.range_add(x, n + 1, x);
    // debug(x, n + 1, x);
    for (int k = 1; k < x; k++) {
      ans[k] += max(0, k - 1);
    }
  }
  for (int i = 1; i <= n; i++) {
    ans[i] += ft.range_query(i, i + 1);
    cout << ans[i] << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}