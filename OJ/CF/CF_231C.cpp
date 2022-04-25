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
  int n, k; cin >> n >> k;
  vec<ll> a(n + 1), s(n + 1, 0);
  for (int i = 1; i <= n; i++) cin >> a[i];
  sort(1 + all(a));
  for (int i = 1; i <= n; i++) {
    s[i] = s[i - 1] + a[i];
  }
  int l = 1, r = n, num = 0, ans;
  while (l <= r) {
    const auto check = [&](const int &x) -> bool {
      for (int i = x; i <= n; i++) {
        if (x * a[i] - (s[i] - s[i - x]) <= k) {
          ans = a[i];
          return true;
        }
      }
      return false;
    };
    int m = (l + r) >> 1;
    if (check(m)) {
      l = m + 1, num = m;
    } else {
      r = m - 1;
    }
  }
  cout << num << ' ' << ans << '\n';
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
