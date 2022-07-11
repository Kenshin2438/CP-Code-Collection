#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

#define PII pair<int, int>
#define vec vector
#define str string
#define fi first
#define se second
#define all(a) (a).begin(), (a).end()
#define SZ(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

void SingleTest(__attribute__((unused)) int TestCase) {
  int n; cin >> n;
  ll x; cin >> x;

  str s = to_string(x);
  if (*max_element(all(s)) <= '1') {
    return cout << -1 << '\n', void();
  }

  const int LIM = 2000;

  int ans = 1;
  for (vec<ll> a = {x}; true; ans ++) {
    vec<ll> b;
    for (const ll &ax : a) {
      vec<bool> app(10, false);
      ll tmp = ax;
      while (tmp) app[tmp % 10] = true, tmp /= 10;
      for (int i = 2; i < 10; i++) {
        if (app[i] == false) continue;
        b.push_back(i * ax);
      }
    }
    sort(all(b), greater<ll>());
    b.resize(min(SZ(b), LIM));
    a = b;

    if (to_string(b[0]).length() >= n) break;
  }
  cout << ans << '\n';
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  // cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
