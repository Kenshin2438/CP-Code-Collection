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
  vec<ll> a(n);
  for (auto && x : a) cin >> x;
  sort(all(a));
  if (a[0] + a[1] >= m) return cout << n << '\n', void();
  if (a[n - 1] + a[n - 2] < m) return cout << 0 << '\n', void();
  int ans = 0;
  for (int i = 1; i < n; i++) {
    if (a[i] + a[i - 1] >= m) {
      ans = i; break;
    }
  }
  cout << (n - ans + 1) << '\n';
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
