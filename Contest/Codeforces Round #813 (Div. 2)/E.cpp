#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) static_cast<int>(size(x))

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
  ll query(int pos) {
    ll res = 0;
    for (; pos > 0; pos &= pos - 1) res += s[pos - 1];
    return res;
  }
};

void solve() {
  const int N = 2e5;
  vector<vector<int>> d(N << 1 | 1);
  for (int i = 1; i <= N; i++) {
    for (int j = i; j <= sz(d); j += i) {
      d[j].emplace_back(i);
    }
  }

  int q; cin >> q;
  vector<array<int, 3>> Q; // {r, l, id}
  for (int i = 0; i < q; i++) {
    int l, r; cin >> l >> r;
    Q.push_back({ r, l, i });
  }
  sort(all(Q));

  FenwickTree tree(N + 1);
  vector<ll> ans(q);
  for (int k = 1; k <= N; k++) {
    for (const int &j : d[k * 2]) {
      if (j >= k) break;
      if (k % j != 0 && (j % 2 != 0 || k % (j / 2) != 0)) continue;
      for (const int &i : d[k * 2]) {
        if (i >= j) break;
        if (k % j == 0 && k % i == 0) tree.update(i, 1);
        else if (2 * k < i + j + k) tree.update(i, 1);
      }
    }
    for (static int cur = 0; cur < sz(Q) && Q[cur][0] == k; cur++) {
      const auto &[r, l, id] = Q[cur];
      ans[id] = (r - l + 1) * 1LL * (r - l) * (r - l - 1) / 6;
      ans[id] -= tree.query(r) - tree.query(l);
    }
  }
  for (const ll &x : ans) cout << x << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
