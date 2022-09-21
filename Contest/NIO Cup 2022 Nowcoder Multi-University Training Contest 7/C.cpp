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

  vector<int> p(n), a(n);
  vector<int> s;
  for (int i = 1; i <= n; i++) {
    cin >> a[i - 1];
    if (a[i - 1] == i) s.emplace_back(i);
    else p[i - 1] = i;
  }
  int m = s.size();
  if (m != 1) {
    for (int i = 0; i < m; i++) {
      p[ s[i] - 1 ] = s[(i + 1) % m];
    }
    cout << "YES\n";
    for (int i = 0; i < n; i++) {
      cout << p[i] << " \n"[i + 1 == n];
    }
  } else {
    p[s[0] - 1] = s[0];
    int val = a[s[0] - 1];
    bool ok = false;
    debug(s[0], a, p);
    for (int i = 0; i < n; i++) {
      if (a[i] == val) continue;
      swap(p[s[0] - 1], p[i]);
      ok = true; break;
    }
    if (ok == false) return cout << "NO\n", void();
    cout << "YES\n";
    for (int i = 0; i < n; i++) {
      cout << p[i] << " \n"[i + 1 == n];
    }
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
