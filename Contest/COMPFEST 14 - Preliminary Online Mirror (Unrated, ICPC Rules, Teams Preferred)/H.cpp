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
  vector<int> a(n);
  for (int &x : a) {
    cin >> x;
    x %= 3, x = x * x % 3;
  }
  int ones = count(all(a), 1);
  int zeros = n - ones;

  int Z = 0;
  if (ones == zeros) {
    Z = 0;
  } else if (ones > zeros) {
    Z = 0;
    for (int i = 0, cnt = (ones - zeros) / 2; i < n && cnt; i++) {
      if (a[i] == 1) cnt -= 1, a[i] = 0;
    }
  } else {
    Z = 2;
    for (int i = 0, cnt = (zeros - ones) / 2; i < n && cnt; i++) {
      if (a[i] == 0) cnt -= 1, a[i] = 1;
    }
  }

  cout << Z << '\n';
  for (int &x : a) cout << x;
  cout << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
