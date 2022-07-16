#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

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

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int n, m; cin >> n >> m;
  FenwickTree ft(n);
  for (int i = 0, pre = 0; i < n; i++) {
    int x; cin >> x;
    ft.add(i, x - pre);
    pre = x;
  }
  while (m--) {
    int op; cin >> op;
    switch (op) {
      case 1: {
        int l, r, k; cin >> l >> r >> k;
        ft.range_add(l - 1, r, k);
        break;
      }
      case 2: {
        int l, r; cin >> l >> r;
        cout << ft.range_query(l - 1, r) << '\n';
      }
    }
  }
  return 0;
}