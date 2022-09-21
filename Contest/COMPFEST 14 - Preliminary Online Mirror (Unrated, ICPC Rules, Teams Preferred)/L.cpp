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
  int n; cin >> n;
  vector<ll> a(n);
  for (ll &x : a) cin >> x;

  partial_sum(all(a), begin(a));
  ll SUM = a.back();

  if (*min_element(all(a)) < 0 || *max_element(all(a)) > SUM) {
    return cout << -1 << '\n', void();
  }

  vector<pair<ll, int>> ID(n - 1);
  for (int i = 0; i < sz(ID); i++) {
    ID[i].first = a[i], ID[i].second = i;
  }
  sort(all(ID));

  FenwickTree ft(sz(ID));
  ll invNumber = 0;
  for (const auto &[val, id] : ID) {
    invNumber += id - ft.query(id);
    ft.update(id, 1);
  }
  cout << invNumber << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
