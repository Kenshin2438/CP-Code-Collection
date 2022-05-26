#define PROBLEM "http://oj.daimayuan.top/course/10/problem/464"

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
#define pb push_back
#define all(a) a.begin(), a.end()

typedef double db;
typedef long long ll;

const int N = (int) 1e5 + 10;

int n, sq, q, a[N], b[N];

void SingleTest(int TestCase) {
  cin >> n >> q;
  for (int i = 1; i <= n; i++) cin >> a[i];
  sq = sqrt(n) + 1;
  for (int i = 1; i <= n; i++) b[i] = i / sq;
  vec<vec<int>> s(b[n] + 1);
  for (int i = 1; i <= n; i++) s[b[i]].pb(a[i]);
  for (vec<int> &v : s) sort(all(v)), debug(v);
  while (q--) {
    int l, r, h; cin >> l >> r >> h;
    int ans = 0;
    if (b[l] == b[r]) {
      for (int i = l; i <= r; i++) ans += a[i] <= h;
    } else {
      for (int i = l; b[i] == b[l]; i++) ans += a[i] <= h;
      for (int k = b[l] + 1; k < b[r]; k++) {
        ans += int(upper_bound(all(s[k]), h) - s[k].begin());
      }
      for (int i = r; b[i] == b[r]; i--) ans += a[i] <= h;
    }
    cout << ans << " \n"[q == 0];
  }
}

void init() { }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  cin >> T;
  for (init(); T--; ) SingleTest(++TestCase);
  return 0;
}
