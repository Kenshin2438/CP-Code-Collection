#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

void solve() {
  int n; cin >> n;
  vector<int> a(n * 2);
  for (int &x : a) cin >> x;
  sort(all(a));

  if (n == 1) {
    cout << a[1] - a[0] << "\n";
    return;
  }

  if (n == 2) {
    ll ans = 1e18L;
    {
      ll S = 0;
      vector<int> b = {-1, -1, -1, 2};
      for (int i = 0; i < n * 2; i++) {
        S += abs(a[i] - b[i]);
      }
      ans = min(ans, S);
    }
    {
      ll S = 0;
      vector<int> b = {2, 2, 2, 2};
      for (int i = 0; i < n * 2; i++) {
        S += abs(a[i] - b[i]);
      }
      ans = min(ans, S);
    }
    {
      ll S = 0;
      vector<int> b = {0, 0, 0, 0};
      for (int i = 0; i < n * 2; i++) {
        S += abs(a[i] - b[i]);
      }
      ans = min(ans, S);
    }
    cout << ans << "\n";
    return;
  }

  ll ans = 0;
  for (int i = 0; i < n * 2; i++) {
    ans += abs(a[i]);
  }

  if (n % 2 == 0) {
    ll S = 0;
    for (int i = 0; i < n * 2 - 1; i++) {
      S += abs(a[i] - -1);      
    }
    S += abs(a.back() - n);
    ans = min(ans, S);
  }

  int A = pow(n, 1.0L / (n - 1)), _ = n - 1;
  int tmp = 1;
  while (_--) tmp *= A;
  if (tmp == n) {
    ll S = 0;
    for (int i = 0; i < n * 2; i++) {
      S += abs(a[i] - A);      
    }
    ans = min(ans, S);
  }

  cout << ans << "\n";
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}