#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

void solve() {
  int n; cin >> n;
  vector<int> h(n);
  for (int &x : h) cin >> x;

  ll ans = 0;
  if (n & 1) {
    for (int i = 1; i < n; i += 2) {
      if (h[i] > max(h[i - 1], h[i + 1])) continue;
      ans += max(h[i - 1], h[i + 1]) + 1 - h[i];
    }
  } else {
    vector<ll> a, b;
    for (int i = 1; i + 1 < n; i += 2) {
      a.push_back(max(0, max(h[i - 1], h[i + 1]) + 1 - h[i]));
    }
    for (int i = 2; i + 1 < n; i += 2) {
      b.push_back(max(0, max(h[i - 1], h[i + 1]) + 1 - h[i]));
    }
    // debug(a);
    // debug(b);
    vector<ll> pre(a.size()), suf(b.size());
    for (int i = 0; i < a.size(); i++) {
      if (i == 0) pre[i] = a[i];
      else pre[i] = pre[i - 1] + a[i];
    }
    for (int i = a.size() - 1; i >= 0; i--) {
      if (i == a.size() - 1) suf[i] = b[i];
      else suf[i] = suf[i + 1] + b[i];
    }
    // debug(pre);
    // debug(suf);
    ans = min(pre.back(), suf.front());
    for (int i = 0; i + 1 < a.size(); i++) {
      ans = min(ans, pre[i] + suf[i + 1]);
    }
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T; cin >> T;
  while (T--) solve(); 
 
  return 0;
}