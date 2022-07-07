#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)

void solve() {
  int n; cin >> n;
  vector<ll> a(n);
  int l = 0, r = 0, z = 0;
  for (ll &x : a) {
    cin >> x;
    l += x < 0LL;
    r += x > 0LL;
    z += x == 0LL;
  }
  if (l >= 3 || r >= 3) {
    return cout << "NO\n", void();
  }
  if (z && (l >= 2 || r >= 2)) {
    return cout << "NO\n", void();
  }
  vector<ll> b;
  int zo = 0;
  for (ll x : a) {
    if (x != 0) b.push_back(x);
    else zo++;
  }
  zo = min(zo, 3);
  
  while (zo--) b.push_back(0);
  sort(all(b));
  set<ll> s;
  for (ll x : b) s.insert(x);
  n = b.size();
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      for (int k = j + 1; k < n; k++) {
        if (s.count(b[i] + b[j] + b[k])) {
          continue;
        } else {
          return cout << "NO\n", void();
        }
      }
    }
  }
  cout << "YES\n";
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T; cin >> T;
  while (T--) solve();
  return 0;
}
