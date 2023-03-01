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

void answer(int ans) {
  cout << "! " << ans << endl;
}

int query(int x) {
  cout << "- " << x << endl;
  int res; cin >> res;
  return res;
}

void solve() {
  int cnt; cin >> cnt;

  int ans = 0;
  for (int q = 1; cnt; cnt -= 1) {
    int now = query(q);
    ans |= 1 << (now - cnt + 1);
    q = 1 << (now - cnt + 1);
  }
  answer(ans);
}

int main() {
  // cin.tie(nullptr)->sync_with_stdio(false);
  // cout << fixed << setprecision(15);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}