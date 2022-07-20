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
  int n, k; cin >> n >> k;
  vector<bool> vis(3000 + 1, false);
  vector<int> a(n);
  for (int &x : a) {
    cin >> x;
    for (int i = 1; i <= k; i++) {
      vis[x / i] = true;
    }
  }
  int ans = 0x3f3f3f3f;
  int lim = *min_element(all(a));
  for (int l = 0; l <= lim; l++) {
    if (vis[l] == false) continue;
    int r = 0;
    for (int x : a) {
      int L = 1, R = k, t = -1;
      while (L <= R) {
        int M = (L + R) >> 1;
        if (x / M >= l) {
          t = M;
          L = M + 1;
        } else {
          R = M - 1;
        }
      }
      r = max(r, x / t);
    }
    ans = min(ans, r - l);
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T; cin >> T;
  while (T--) solve(); 
 
  return 0;
}