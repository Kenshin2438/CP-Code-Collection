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

const int N = 1e6 + 10;
vector<int> fac[N];

void init() {
  for (int i = 1; i < N; i++) {
    for (int j = i; j < N; j += i) {
      fac[j].emplace_back(i);
    }
  }
}

void solve() {
  int n; cin >> n;
  string s; cin >> s;

  vector<int> lsm(n + 1); iota(all(lsm), 0);
  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    if (s[i - 1] == '0') {
      for (const int &x : fac[i]) {
        if (lsm[x] == i) {
          ans += x;
          break;
        }
      }
      for (const int &x : fac[i]) {
        if (lsm[x] == i) {
          lsm[x] = i + x;
        }
      }
    }
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  init();

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
