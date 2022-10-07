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
  FenwickTree(int n = 0) : s(n) {}
  void add(int p, int dif) {
    for (; p < sz(s); p |= p + 1) s[p] += dif;
  }
  int query(int p) { // [0, p)
    int res = 0;
    for (; p > 0; p &= p - 1) res += s[p - 1];
    return res;
  }
  int lower_bound(int S) { // [0, p] >= S
    int p = 0;
    for (int pw = 1 << 25; pw; pw >>= 1) {
      if (p + pw <= sz(s) && s[p + pw - 1] < S) {
        p += pw, S -= s[p - 1];
      }
    }
    return p;
  }
};

void solve() {
  int n; cin >> n;
  vector<int> p(n);
  for (int i = 0; i < n; i++) {
    int x; cin >> x; p[x - 1] = i;
  }
  int q; cin >> q;
  vector<vector<pair<int, int>>> Q(n + 1);
  for (int i = 0; i < q; i++) {
    int x, y; cin >> x >> y;
    Q[y].emplace_back(x, );
  }

}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
