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

using u128 = __uint128_t;
ostream &operator<<(ostream &os, const u128 &v) {
  if (v == 0) return (os << "0");
  u128 num = v; string s;
  for (; num > 0; num /= 10) s.push_back(char(num % 10) + '0');
  return reverse(all(s)), (os << s);
}

void solve() {
  ll n; cin >> n;
  if (n == 1) return cout << 1 << '\n', void();
  if (n == 2) return cout << -1 << '\n', void();
  u128 M = (n + 1) / 2;
  u128 l = M, r = n, ans = M;
  while (l <= r) {
    u128 m = (l + r) / 2;
    bool ok = true;
    {
      u128 a = m, b = m, cnt = 0;
      while (a >= M) { // assert (a >= b);
        cnt = cnt + a / M * b;
        a %= M;
        if (a < b) swap(a, b);
      }
      cnt += min(a, b);
      if (cnt > n) ok = false;
    }
    if (ok) {
      ans = m, l = m + 1;
    } else {
      r = m - 1;
    }
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}