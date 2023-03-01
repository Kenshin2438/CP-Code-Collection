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
  int a = 0, b = 0, now = 0, tmp = 1;
  while (n) {
    int num = n % 10; 
    if (num % 2 == 0) {
      a += num / 2 * tmp;
      b += num / 2 * tmp;
    } else {
      if (now) {
        a += num / 2 * tmp;
        b += (num - num / 2) * tmp;
      } else {
        b += num / 2 * tmp;
        a += (num - num / 2) * tmp;
      }        
      now ^= 1;
    }
    n /= 10, tmp *= 10;
  }
  cout << a << " " << b << "\n";
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}