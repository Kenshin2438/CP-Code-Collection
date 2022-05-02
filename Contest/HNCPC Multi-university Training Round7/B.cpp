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
  int n; cin >> n;
  vec<PII> a(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i].fi; a[i].se = i;
  }
  vec<PII> ans;
  sort(1 + all(a), greater<PII>());
  for (int i = 1; i <= n; i++) {
    // debug(a);
    for (int j = i + 1; j <= n; j++) {
      if (a[j].fi && a[i].fi) {
        a[j].fi--, a[i].fi--;
        ans.push_back(PII{ a[i].se, a[j].se });
      }
    }
    if (a[i].fi) return cout << "-1\n", void();
    sort(i + 1 + all(a), greater<PII>());
    // debug(a);
  }
  for (int i = 1; i <= n; i++) {
    if (a[i].fi) return cout << "-1\n", void();
  }
  cout << SZ(ans) << '\n';
  for (auto [u, v] : ans) cout << u << ' ' << v << '\n';
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
