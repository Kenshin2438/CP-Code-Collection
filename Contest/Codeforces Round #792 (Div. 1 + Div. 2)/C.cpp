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
  int n, m; cin >> n >> m;
  vec<vec<int>> g(n, vec<int>(m));
  for (auto &v : g) for (int &x : v) cin >> x;

  bool ok = true;
  for (const auto &v : g) ok &= is_sorted(all(v));
  if (ok) return cout << "1 1\n", void();

  vec<PII> ans;
  for (const auto &v : g) {
    vec<int> u = v;
    sort(all(u));
    vec<int> dif;
    for (int i = 0; i < m; i++) {
      if (u[i] == v[i]) continue;
      dif.push_back(i);
    }
    if (dif.empty()) continue;
    if (SZ(dif) == 2) {
      int p = dif[0], q = dif[1];

      bool chk = true;
      for (int i = 0; i < n; i++) {
        if (g[i][p] < g[i][q]) chk = false;
      }

      if (chk) ans.push_back(PII{p + 1, q + 1});
      else return cout << "-1\n", void();
    } else {
      return cout << "-1\n", void();
    }
  }
  sort(all(ans));
  ans.erase(unique(all(ans)), ans.end());
  if (SZ(ans) != 1) return cout << "-1\n", void();
  cout << ans[0].fi << ' ' << ans[0].se << '\n';
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
