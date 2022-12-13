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
  int n; cin >> n;
  vector<int> a(n + 1), b(n + 1);
  for (int i = 1; i <= n; i++) cin >> a[i];
  b[0] = a[1], b[n] = a[n];
  const auto lcm = [&](int a, int b) { return a / __gcd(a, b) * b; };
  for (int i = 1; i + 1 <= n; i++) {
    b[i] = lcm(a[i], a[i + 1]);
  }
  bool ans = true;
  for (int i = 1; i <= n; i++) {
    if (a[i] % gcd(b[i], b[i - 1])) ans = false;
  }
  cout << (ans ? "YES" : "NO") << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
