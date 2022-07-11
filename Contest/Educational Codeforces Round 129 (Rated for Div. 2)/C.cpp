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

void SingleTest(__attribute__((unused)) int TestCase) {
  int n; cin >> n;
  vec<PII> p(n), ans;
  for (auto &&[a, b] : p) cin >> a;
  for (auto &&[a, b] : p) cin >> b;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (p[i] > p[j]) {
        swap(p[i], p[j]);
        ans.push_back(PII{i + 1, j + 1});
      }
    }
  }
  vec<int> a, b;
  for (const auto &[_, b] : p) a.push_back(_);
  for (const auto &[a, _] : p) b.push_back(_);
  if (is_sorted(all(a)) && is_sorted(all(b))) {
    cout << SZ(ans) << '\n';
    for (auto [x, y] : ans) cout << x << ' ' << y << '\n';
  } else cout << "-1\n";
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
