#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

#define PII pair<int, int>
#define vec vector
#define str string
#define fi first
#define se second
#define all(a) (a).begin(), (a).end()
#define SZ(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

const int inf = 2e9;
const int N = (int) 2e5 + 10;

PII tree[N << 2];

#define ld nd << 1
#define rd nd << 1 | 1

void merge(int nd) {
  tree[nd].fi = min(tree[ld].fi, tree[rd].fi);
  if (tree[nd].fi == tree[ld].fi) {
    tree[nd].se = tree[ld].se;
  } else {
    tree[nd].se = tree[rd].se;
  }
}

void build(int s, int t, int nd) {
  if (s == t) {
    cin >> tree[nd].fi, tree[nd].se = s;
    return ;
  }
  int m = (s + t) >> 1;
  build(s, m, ld), build(m + 1, t, rd), merge(nd);
}

void update(int s, int t, int nd, int p, int val) {
  if (p > t || p < s) return ;
  if (s == t) return tree[nd].fi = val, void();
  int m = (s + t) >> 1;
  update(s, m, ld, p, val), update(m + 1, t, rd, p, val);
  merge(nd);
}

PII lower_bound(int s, int t, int nd, int LIM) {
  if (s == t) return tree[nd];
  int m = (s + t) >> 1;
  if (tree[ld].fi <= LIM) return lower_bound(s, m, ld, LIM);
  if (tree[rd].fi <= LIM) return lower_bound(m + 1, t, rd, LIM);
  return {inf, -1};
}

void SingleTest(int TestCase) {
  int n; cin >> n;
  build(1, n, 1);
  int m; cin >> m;
  for (int c; m--; ) {
    cin >> c;
    vec<int> ans;
    while (true) {
      auto [minValue, position] = lower_bound(1, n, 1, c);
      if (position == -1 || minValue == inf) break;
      c -= minValue;
      update(1, n, 1, position, inf);
      ans.push_back(position);
    }
    cout << SZ(ans);
    sort(all(ans));
    for (int p : ans) cout << ' ' << p;
    cout << '\n';
  }
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  // cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
