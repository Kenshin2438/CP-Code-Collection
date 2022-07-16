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
  int n, m, p1, p2;
  cin >> n >> m >> p1 >> p2;
  vector<int> k(n);
  for (int &x : k) cin >> x;
  vector<array<int, 5>> Q;

  vector<ll> ans(m);
  for (int i = 0; i < m; i++) {
    int l, r; cin >> l >> r;
    --l, --r;
    ans[i] = (r - l) * 1LL * p1;
    Q.push_back({r, i, l, r, 1});
    if (l == 0) continue;
    Q.push_back({l - 1, i, l, r, -1});
  }
  sort(all(Q));

  vector<int> L(n), R(n);
  {
    stack<int> S;
    for (int i = 0; i < n; i++) {
      while (!S.empty() && k[S.top()] <= k[i]) S.pop();
      L[i] = S.empty() ? -1 : S.top();
      S.push(i);
    }
  }
  {
    stack<int> S;
    for (int i = n - 1; i >= 0; i--) {
      while (!S.empty() && k[S.top()] <= k[i]) S.pop();
      R[i] = S.empty() ? n : S.top();
      S.push(i);
    }
  }
  vector<vector<array<int, 3>>> Col(n);
  for (int i = 0; i < n; i++) {
    debug(i, L[i], R[i]);
    if (L[i] != -1 && R[i] != n) {
      Col[L[i]].push_back({R[i], R[i], p1});
    }
    if (L[i] != -1 && R[i] > i + 1) {
      Col[L[i]].push_back({i + 1, R[i] - 1, p2});
    }
    if (R[i] != n && L[i] < i - 1) {
      Col[R[i]].push_back({L[i] + 1, i - 1, p2});
    }
  }
  {
    FenwickTree ft(n);
    int pos = 0;
    for (const auto &[lim, idx, pl, pr, op] : Q) {
      // debug(lim, idx, pl, pr, op);
      while (pos <= lim) {
        for (auto &[l, r, v] : Col[pos]) {
          ft.range_add(l, r + 1, v);
        }
        pos++;
      }
      ans[idx] += op * ft.range_query(pl, pr + 1);
    }
  }
  for (const ll &x : ans) cout << x << '\n';
  return 0;
}