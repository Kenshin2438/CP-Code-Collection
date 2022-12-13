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
  int n, x; cin >> n >> x;
  vector<int> a(n);
  for (int &ax : a) cin >> ax;
  sort(all(a), greater<int>());

  bool ok = true;
  ll S = 0LL;
  for (int i = 1; i <= x; i++) {
    if (S % i != 0) { ok = false; break; }
    S /= i;
    while (!a.empty() && a.back() == i) {
      S += 1, a.pop_back();
    }
  }
  cout << (ok ? "Yes" : "No") << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
