#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

const int N = 2e5 + 10;

int n, a[N], p[N];
int find(int x) { return x == p[x] ? x : p[x] = find(p[x]); }

void solve() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    p[i] = i;
  }
  for (int i = 1; i <= n; i++) {
    int d; cin >> d;
    if (i - d >= 1) p[find(a[i])] = find(a[i - d]);
    if (i + d <= n) p[find(a[i])] = find(a[i + d]);
  }
  bool ans = true;
  for (int i = 1; i <= n; i++) {
    if (find(i) != find(a[i])) ans = false;
  }
  cout << (ans ? "YES" : "NO") << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
