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

using ull = unsigned long long;

void solve() {
  ull P, Q, q; cin >> P >> Q >> q;
  for (ull a, b; q--; ) {
    cin >> a >> b;
    vector<int> pos(Q, -1);
    pos[a % Q] = 0;

    vector<ull> p; p.push_back(a % P);
    for (int i = 1, x = a % Q; true; i++) {
      ull px = (p[i - 1] * p[i - 1] % P + b % P) % P;
      ull qx = (x * 1LL * x % Q + b % Q) % Q;
      if (pos[qx] != -1) {
        ull D = (px - p[pos[qx]] + P) % P;
        if (__gcd(D, P) == Q) cout << 1;
        else cout << 0;
        break;
      }
      p.push_back(px), pos[qx] = i, x = qx;
    }
  }
  cout << '\n';
}

signed main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
