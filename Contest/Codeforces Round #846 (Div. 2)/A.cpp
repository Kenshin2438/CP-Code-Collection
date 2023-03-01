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
  vector<int> odd, even;
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    if (x & 1) {
      odd.emplace_back(i + 1);
    } else {
      even.emplace_back(i + 1);
    }
  }
  if (sz(odd) >= 3) {
    cout << "YES\n";
    cout << odd[0] << " ";
    cout << odd[1] << " ";
    cout << odd[2] << "\n";
  } else if (sz(even) >= 2 && sz(odd) >= 1) {
    cout << "YES\n";
    cout << odd[0] << " ";
    cout << even[0] << " ";
    cout << even[1] << "\n";
  } else {
    cout << "NO\n";
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}