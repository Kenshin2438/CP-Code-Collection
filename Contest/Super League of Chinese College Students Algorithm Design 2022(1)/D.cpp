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

bitset<N> isp;
void init() {
  isp[0] = isp[1] = 1;
  for (int i = 2; i < N; i++) 
    if (!isp[i])
      for (ll j = i * 1LL * i; j < N; j += i)
        isp[j] = 1;
  isp.flip();
}

void solve() {
  int n, m; cin >> n >> m;
  vector<int> x(n), y(n);
  for (int i = 0; i < n; i++) {
    cin >> x[i] >> y[i];
  }
  vector<array<int, 3>> p;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      int d = abs(x[i] - x[j]) + abs(y[i] - y[j]);
      p.push_back({d, i, j});
    }
  }
  sort(all(p));
  vector<bitset<2000>> f(n);
  ll ans = 0;
  for (const array<int, 3> &a : p) {
    if (isp[ a[0] ]) {
      ans += (f[ a[1] ] ^ f[ a[2] ]).count();
    }
    f[ a[1] ][ a[2] ] = f[ a[2] ][ a[1] ] = 1;
  } 
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  init();
  int T; cin >> T;
  while (T--) solve();
  
  return 0;
}