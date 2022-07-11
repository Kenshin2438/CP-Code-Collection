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

void SingleTest(int TestCase) {
  int n, m, k; cin >> n >> m >> k;
  vec<PII> p(k);
  for (auto &&[x, y] : p) cin >> x >> y;
  vec<PII> q = p;
  sort(all(q));
  // [x1, x2], [y1, y2], pos;
  vec<array<int, 5>> b;

  int idx = 0;

  int preX = 1, preY = 1;
  for (int i = 0; i < k; i++) {
    auto [x, y] = q[i];
    if (i == 0) {
      b.emplace_back(preX, x, preY, y, ++ idx);
    } else {
      
    }
  }

  vec<int> ans(k, 0);
  for (int i = k - 1; i >= 0; i--) {
    auto [x, y] = p[i];
    vec<int> parent = {
      get(x + 1, y),
      get(x - 1, y),
      get(x, y + 1),
      get(x, y - 1)
    };
    ans[i] = int(SZ(set<int>(all(parent))) > 1);
    for (int u : parent) {
      if (u == -1) continue;
      merge(u, get(x, y));
    }
  }
  for (int x : ans) cout << x;
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
