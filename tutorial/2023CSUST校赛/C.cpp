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
  int n; cin >> n;
  assert(1 <= n && n <= (int) 5E5);
  int k; cin >> k;
  assert(1 <= k && k <= 10);

  if (n % 4 != 0) return cout << "No\n", void();
  n = n * 3 / 4;

  vector<int> pow3(20);
  for (int i = 1; i <= 18; i++) pow3[i] = i * i * i;

  bool ok = false;
  const function<void(int, int)> dfs = [&](int num, int now) {
    if (ok || now < 0) return;
    if (num == 0) {
      if (now == 0) ok = true;
      return;
    } 

    for (int v = 1; v <= 18 && pow3[v] <= now; v++) {
      dfs(num - 1, now - pow3[v]);
    }
  };
  dfs(k, n);
  cout << (ok ? "Yes" : "No") << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}