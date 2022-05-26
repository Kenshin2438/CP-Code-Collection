#define PROBLEM "http://oj.daimayuan.top/course/10/problem/452"

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
#define pb push_back
#define all(a) a.begin(), a.end()

typedef double db;
typedef long long ll;

void SingleTest(int TestCase) {
  int n, q; cin >> n >> q;
  vec<tuple<int, int, int>> ops;
  for (int i = 1; i <= n; i++) {
    int x; cin >> x;
    ops.emplace_back(1, i, x);
  }
  for (int i = 1; i <= q; i++) {
    int op; cin >> op;
    if (op == 1) {
      int x, y; cin >> x >> y;
      ops.emplace_back(op, x, y);
    } else {
      int y; cin >> y;
      ops.emplace_back(op, 0, y);
    }
  }
  // reverse(all(ops));
  vec<int> ans(n + 1, 0);
  vec<int> vis(n + 1, 0);
  int tmp = -1;
  while (!ops.empty()) {
    int op = get<0>(ops.back());
    int x  = get<1>(ops.back());
    int y  = get<2>(ops.back());
    ops.pop_back();

    if (op == 2) tmp = max(tmp, y);
    else {
      if (vis[x]) continue;
      vis[x] = 1, ans[x] = max(y, tmp);
    }
  }
  for (int i = 1; i <= n; i++) cout << ans[i] << " \n"[i == n];
}

void init() { }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  // cin >> T;
  for (init(); T--; ) SingleTest(++TestCase);
  return 0;
}
