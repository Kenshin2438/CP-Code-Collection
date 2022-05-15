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
  vec<int> a(n), b(n);
  for (int &x : a) cin >> x;
  for (int &x : b) cin >> x;
  auto check = [&](const ll &num) -> bool {
    vec<int> _a;
    for (int x : a) {
      if (x <= num) continue;
      _a.emplace_back(x);
    }
    vec<int> _b;
    for (int x : b) {
      if (x <= num) continue;
      _b.emplace_back(x);
    }
    bool ok_a = true, ok_b = true;
    if (SZ(_a) & 1) ok_a = false;
    for (int pre = -1, i = 0; i < SZ(_a); i++) {
      if (pre == -1) pre = _a[i];
      else {
        if (pre == _a[i]) pre = -1;
        else ok_a = false;
      }
    }
    if (SZ(_b) & 1) ok_b = false;
    for (int pre = -1, i = 0; i < SZ(_b); i++) {
      if (pre == -1) pre = _b[i];
      else {
        if (pre == _b[i]) pre = -1;
        else ok_b = false;
      }
    }
    return ok_a && ok_b;
  };
  ll l = 0, r = 1e9, ans = -1;
  while (l <= r) {
    ll m = (l + r) >> 1;
    if (check(m)) {
      ans = m, r = m - 1;
    } else {
      l = m + 1;
    }
  }
  cout << ans << '\n';
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
