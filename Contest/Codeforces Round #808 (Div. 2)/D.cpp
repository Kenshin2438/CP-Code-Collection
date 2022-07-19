#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) static_cast<int>(x.size())

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

void solve() {
  int n; cin >> n;
  vector<int> a(n);
  for (int &x : a) cin >> x;

  for (int o = n; o >= 2; o--) {
    vector<int> b;
    for (int i = 1; i < sz(a); i++) {
      if (a[i] != a[i - 1])
        b.emplace_back(a[i] - a[i - 1]);
    }
    if (sz(a) < o) b.emplace_back(a[0]);
    a = move(b);
    sort(all(a));
    if (sz(a) < 2) break;
  }
  cout << (a.empty() ? 0 : a[0]) << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1; 
  cin >> T;
  while (T--) solve();

  return 0;
}