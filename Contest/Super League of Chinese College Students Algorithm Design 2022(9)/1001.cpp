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
  vector<pair<int, int>> p(n);
  for (int i = 0; i < n; i++) {
    cin >> p[i].first, p[i].second = p[i].first;
  }

  const function<void(int, int)> sol = [&](int l, int r) {
    if (r - l + 1 < 3) return;

    int cnt = 0;
    for (int i = l; i <= r; i++) cnt += p[i].first == 0;
    if (cnt == r - l + 1) return;

    vector<pair<int, int>> q;
    for (int i = l; i <= r; i++) {
      if (p[i].first & 1) q.push_back(p[i]);
    }
    int pos = l + sz(q) - 1;
    for (int i = l; i <= r; i++) {
      if (~p[i].first & 1) q.push_back(p[i]);
    }

    for (int i = l; i <= r; i++) {
      p[i].first = q[i - l].first >> 1;
      p[i].second = q[i - l].second;
    }
    sol(l, pos), sol(pos + 1, r);
  };

  sol(0, n - 1);
  vector<int> ans(n);
  for (int i = 0; i < n; i++) ans[i] = p[i].second;

  unordered_map<int, int> Mp;
  bool ok = true;
  for (int i = 0; i < n; i++) {
    if ((Mp[ ans[i] ] += 1) >= 3) {
      ok = false; break;
    }
  }

  if (ok) {
    cout << "YES\n";
    for (int i = 0; i < n; i++) cout << ans[i] << ' ';
    cout << '\n';
  } else {
    cout << "NO\n";
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
