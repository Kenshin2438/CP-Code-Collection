#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

void solve() {
  int n, k; cin >> n >> k;
  vector<int> p(n + 2);
  for (int i = 1; i <= n; i++) {
    cin >> p[i];
  }

  if (p[k] < 0) return cout << "NO\n", void();

  {
    ll cur = 0, lmost = 0; int oth = k + 1;
    bool ok = true;
    for (int i = k; i >= 0; i--) {
      if (cur + p[i] >= 0) {
        cur += p[i];
      } else {
        for (ll tmp = 0, rmost = 0; oth <= n;) {
          tmp += p[oth]; oth += 1;
          rmost = min(tmp, rmost);
          if (tmp > 0) {
            if (lmost + rmost >= 0) {
              lmost += tmp, cur += tmp;
              if (cur + p[i] >= 0) break;
              else tmp = 0, rmost = 0;
            } else {
              ok = false; break;
            }
          }
        }
        if (cur + p[i] >= 0) cur += p[i];
        else { ok = false; break; }
      }
      lmost = max(lmost, cur);
    }
    if (ok) return cout << "YES\n", void();
  }
  {
    ll cur = 0, lmost = 0; int oth = k - 1;
    bool ok = true;
    for (int i = k; i <= n; i++) {
      if (cur + p[i] >= 0) {
        cur += p[i];
      } else {
        for (ll tmp = 0, rmost = 0; oth >= 0;) {
          tmp += p[oth]; oth -= 1;
          rmost = min(tmp, rmost);
          if (tmp > 0) {
            if (lmost + rmost >= 0) {
              lmost += tmp, cur += tmp;
              if (cur + p[i] >= 0) break;
              else tmp = 0, rmost = 0;
            } else {
              ok = false; break;
            }
          }
        }
        if (cur + p[i] >= 0) cur += p[i];
        else { ok = false; break; }
      }
      lmost = max(lmost, cur);
    }
    if (ok) return cout << "YES\n", void();
  }
  cout << "NO\n";
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
