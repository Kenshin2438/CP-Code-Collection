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
  vector<int> s;

  FenwickTree(int n) : s(n) {};
  void update(int p, int d) {
    for (; p < sz(s); p |= p + 1) s[p] += d;
  }
  int query(int p) { // [0, pos)
    int res = 0;
    for (; p > 0; p &= p - 1) res += s[p - 1];
    return res;
  }
};

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  const int N = 200000 + 10;
  vector<int> p;
  {
    bitset<N> ntp;
    for (int i = 2; i < N; i++) {
      if (ntp.test(i) == false) p.emplace_back(i);
      for (const int &pr : p) {
        if (pr * 1LL * i >= N) break;
        ntp[pr * i] = 1;
        if (i % pr == 0) break;
      }
    }
  }
  vector<int> pos(N);

  for (int n, m; cin >> n >> m; ) {
    if (!n && !m) break;

    vector<int> a(n);
    for (int &x : a) cin >> x;

    const int inf = 1e9;
    vector<int> l(n, -inf), r(n, inf);
    pos.assign(N, -1);
    for (int i = 0; i < n; i++) {
      int x = a[i];
      for (const int &pr : p) {
        if (pr * 1LL * pr > x) break;
        if (x % pr == 0) {
          if (pos[pr] != -1) l[i] = max(l[i], pos[pr] + 1);
          while (x % pr == 0) x /= pr;
          pos[pr] = i;
        }
      }
      if (x != 1) {
        if (pos[x] != -1) l[i] = max(l[i], pos[x] + 1);
        pos[x] = i;
      }

      if (l[i] == -inf) l[i] = 0;
    }
    pos.assign(N, -1);
    for (int i = n - 1; i >= 0; i--) {
      int x = a[i];
      for (const int &pr : p) {
        if (pr * 1LL * pr > x) break;
        if (x % pr == 0) {
          if (pos[pr] != -1) r[i] = min(r[i], pos[pr] - 1);
          while (x % pr == 0) x /= pr;
          pos[pr] = i;
        }
      }
      if (x != 1) {
        if (pos[x] != -1) r[i] = min(r[i], pos[x] - 1);
        pos[x] = i;
      }

      if (r[i] == inf) r[i] = n - 1;
    }

    vector<vector<array<int, 3>>> ops(n + 1);
    for (int i = 0; i < n; i++) {
      ops[i].push_back({+1, l[i], i});
      ops[r[i] + 1].push_back({-1, l[i], i});
    }

    vector<vector<pair<int, int>>> Q(n);
    for (int i = 0; i < m; i++) {
      int l, r; cin >> l >> r;
      --l, --r;
      Q[r].emplace_back(l, i);
    }

    vector<int> ans(m);

    FenwickTree ft(n + 1);
    for (int i = 0; i < n; i++) {
      for (const auto &op : ops[i]) {
        ft.update(op[1], op[0]);
        ft.update(op[2] + 1, - op[0]);
      }

      for (const auto &P : Q[i]) {
        int l = P.first, id = P.second;
        ans[id] = ft.query(l + 1);
      }
    }
    for (int &x : ans) cout << x << '\n';
  }
  return 0;
}
