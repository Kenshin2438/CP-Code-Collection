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
  int n, k;
  cin >> n >> k;
  vec<int> a(n + 1);
  for (int i = 1; i <= n; i++) cin >> a[i];
  map<int, int> cnt;
  int num = 0, mx = 0;
  PII ans;
  for (int l = 1, r = 1; r <= n; r++) {
    if (cnt[a[r]] == 0) num++, cnt[a[r]]++;
    else cnt[a[r]]++;

    if (num <= k) {
      if (mx < (r - l + 1)) {
        mx = r - l + 1;
        ans = PII{l, r};
      }
    } else {
      while (num > k) {
        if (cnt[a[l]] == 1) num--, cnt[a[l]]--, l++;
        else cnt[a[l]]--, l++;
      }
    }
  }
  cout << ans.fi << ' ' << ans.se << '\n';
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
