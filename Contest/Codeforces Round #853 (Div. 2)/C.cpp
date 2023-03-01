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
  int n, m; cin >> n >> m;
  vector<int> a(n);
  for (int &x : a) cin >> x;
  
  vector<int> StartPos(n + m + 1, -1);
  vector<int> cnt(n + m + 1, 0);
  for (int i = 0; i < n; i++) {
    if (StartPos[a[i]] == -1) {
      StartPos[a[i]] = 0;
    }
  }

  vector<ll> ans(m + 1);
  for (int p, v, i = 1; i <= m; i++) {
    cin >> p >> v, --p;
    int pre = a[p], now = a[p] = v;
    if (pre == now) {
      ans[i] = ans[i - 1] + n;
    } else {
      cnt[pre] += i - 1 - StartPos[pre] + 1;
      StartPos[pre] = -1;

      StartPos[now] = i;

      debug(cnt);
      ans[i] = ans[i - 1] + n - (i - cnt[pre]) + (i - cnt[now]);
    }
  }
  debug(ans);
  cout << accumulate(all(ans), 0LL) << "\n";
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}