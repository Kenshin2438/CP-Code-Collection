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
  vec<int> a(n), ans(n);
  for (int &x : a) cin >> x;
  ans[0] = 1;
  for (int i = 1; i < n; i++) {
    if (a[i] >= a[i - 1]) {
      ans[i] = ans[i - 1];
    } else {
      ans[i] = ans[i - 1] + 1;
    }
  }
  cout << ans[n - 1] << '\n';
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
