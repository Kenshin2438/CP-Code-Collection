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
  int gift, cost; cin >> gift >> cost;
  assert(1 <= gift && gift <= (int) 1E9);
  assert(1 <= cost && cost <= (int) 1E9);

  const int DAY = 150 - cost;
  const int WEEK = DAY * 5 - cost * 2;

  if (DAY <= 0) return cout << "-1\n", void(); 

  if (WEEK <= 0 && gift > DAY * 5) {
    return cout << "-1\n", void();
  }

  ll ans = max(0, (gift - DAY * 5) / WEEK) * 7LL;
  int now = WEEK * (ans / 7);

  while (true) {
    for (int i = 0; i < 5; i++) {
      ans ++;
      now += DAY;
      if (now >= gift) return cout << ans << '\n', void();
    }
    for (int i = 0; i < 2; i++) {
      ans ++;
      now -= cost;
    }
  }
  assert(false);
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  cin >> T;
  assert(1 <= T && T <= (int) 1E5);
  while (T--) solve();

  return 0;
}