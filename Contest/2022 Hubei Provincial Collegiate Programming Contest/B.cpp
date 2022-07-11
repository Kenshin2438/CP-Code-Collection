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
#define rall(a) (a).rbegin(), (a).rend()
#define sz(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

/**
 * a = 1, b = 1;
 * 
 * 3:5
 * 
 **/

void SingleTest(__attribute__((unused)) int TestCase) {
  ll x, y, a, b; cin >> x >> y >> a >> b;
  // assert(a == 1 && b == 1);
  ll ans = 0;
  bool flag = false;

  while (x || y) {
    ll g = gcd(x, y); 
    x /= g, y /= g;
    
    if (x == 0 || y == 0) { ans ++; break; }
    if (x < y) swap(x, y);
    if ((x - y) & 1) { flag = true; break; }
    x = (x - y) / 2, ans ++;
  }

  if (flag) ans = -1;
  cout << ans << '\n';
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}