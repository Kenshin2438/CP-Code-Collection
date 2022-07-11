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
  for (auto &v : g) {
    for (auto &x : v) cin >> x;
    sort(all(v));
  }
  vec<bool> possible(n, true);
  int ans = n;
  for (int i = 1; i <= m; i++) {
    int b; cin >> b;
    if (ans) {
      for (int j = 0; j < n; j++) {
        if (possible[j]) {
          possible[j] = binary_search(all(g[j]), b);
          if (possible[j] == false) ans--;
        }
      }
    }
    cout << ans << " \n"[i == m];
  }
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
