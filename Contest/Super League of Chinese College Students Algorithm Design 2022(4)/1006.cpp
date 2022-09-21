#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

void solve() {
  int n; cin >> n;
  vector<int> a(n);
  for (auto &&x : a) cin >> x;
  {
    double S = 0;
    for (const auto &x : a) {
      if (S >= 200) S += x * 0.5;
      else if (S >= 100) {
        double cur = 1.25 * (200 - S);
        if (x >= cur) {
          S = 200 + (x - cur) * 0.5;
        } else {
          S += x * 0.8;
        }
      } else {
        double cur = (100 - S);
        if (x >= cur) {
          if (x - cur >= 125) {
            S = 200 + (x - cur - 125) * 0.5;
          } else {
            S = 100 + (x - cur) * 0.8;
          }
        } else {
          S += x;
        }
      }
    }
    cout << S << ' ';
  }
  {
    double S = 0;
    for (const auto &x : a) {
      if (S >= 200) S += x * 0.5;
      else if (S >= 100) S += x * 0.8;
      else S += x;
    }
    cout << S << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(3);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
