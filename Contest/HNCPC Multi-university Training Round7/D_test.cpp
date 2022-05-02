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
  ll s = 0;
  vec<ll> a(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i], s += a[i];
  }
  ll ans = s, sum = 0;
  vec<int> del(n + 1, 1);
  // for (int _ = 1; _ <= n; _++) {
  //   ll add = -1e18; int pos = -1;
    for (int i = 1; i <= n; i++) {
      ll tmp = 0;
      for (int j = i; j <= n; j += i) {
        if (del[j]) tmp += a[j];
      }
      if (tmp >= 0) {
        sum += tmp;
        for (int j = i; j <= n; j += i) {
          del[j] = 0;
        }
      }
      // if (tmp >= add) pos = i, add = tmp;
    }
  //   debug(add, pos);
  //   if (add >= 0) sum += add;
  //   for (int i = pos; i <= n; i += pos) {
  //     del[i] = 0;
  //   }
  //   ans = max(ans, sum);
  // }
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
