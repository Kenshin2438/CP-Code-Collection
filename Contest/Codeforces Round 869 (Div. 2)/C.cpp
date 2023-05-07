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

void solve() {
  int n, q; cin >> n >> q;
  vector<int> a(n);
  for (int &x : a) cin >> x;

  vector<int> ID(n);
  for (int i = 1; i < n; i++) { 
    ID[i] = ID[i - 1] + (a[i] > a[i - 1]); 
  }
  debug(ID);

  vector<pair<int, int>> Q;
  for (int i = 0; i < q; i++) {
    int l, r; cin >> l >> r;
    Q.emplace_back(l - 1, r);
  }

  vector<int> ans(q);

  int L = 0, R = 0, blk = 350, ANS = 0;
  vector<int> cnt(n);
  const auto add = [&](int x) {
    x = ID[x];
    cnt[x] += 1;
    if (cnt[x] == 1 || cnt[x] == 2) ANS += 1;
  };
  const auto del = [&](int x) {
    x = ID[x];
    cnt[x] -= 1;
    if (cnt[x] == 0 || cnt[x] == 1) ANS -= 1;
  };
  const auto calc = [&]() { return ANS; };
#define K(x) pair<int, int>(x.first/blk, x.second ^ -(x.first/blk & 1))
  vector<int> s(q); iota(all(s), 0);
  sort(all(s), [&](int s, int t){ return K(Q[s]) < K(Q[t]); });
  for (const int &qid : s) {
    pair<int, int> q = Q[qid];
    while (L > q.first) add(--L);
    while (R < q.second) add(R++);
    while (L < q.first) del(L++);
    while (R > q.second) del(--R);
    ans[qid] = calc();
  }
  for (const int &x : ans) cout << x << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}