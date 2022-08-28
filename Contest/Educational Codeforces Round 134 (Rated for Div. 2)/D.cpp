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

/**
    vector<int> ca, cb;
    for (int i = l; i <= r; i++) {
      if (a[i] >> p & 1) ca.push_back(a[i]);
      if (!(b[i] >> p & 1)) cb.push_back(b[i]);
    }
    if (sz(ca) == sz(cb)) {
      int lim = sz(ca);
      for (int i = l; i <= r; i++) {
        if (!(a[i] >> p & 1)) ca.push_back(a[i]);
        if (b[i] >> p & 1) cb.push_back(b[i]);
      }

      for (int i = l; i <= r; i++) {
        a[i] = ca[i - l];
        b[i] = cb[i - l];
      }

      sol(l, l + lim - 1, p - 1);
      sol(l + lim, r, p - 1);
    } else {
      sol(l, r, p - 1);
    }
**/

void solve() {
  int n; cin >> n;
  vector<int> a(n), b(n);
  for (int &x : a) cin >> x;
  for (int &x : b) cin >> x;

  vector<pair<int, int>> seg = { {0, n - 1} };

  function<bool(int)> chk = [&](int p) {
    vector<int> SZ;
    bool ok = true;
    for (const auto &[l, r] : seg) {
      vector<int> ca, cb;
      for (int i = l; i <= r; i++) {
        if ((a[i] >> p & 1) == 1) ca.push_back(a[i]);
        if ((b[i] >> p & 1) == 0) cb.push_back(b[i]);
      }
      if (sz(ca) == sz(cb)) {
        SZ.push_back(sz(ca));
        for (int i = l; i <= r; i++) {
          if ((a[i] >> p & 1) == 0) ca.push_back(a[i]);
          if ((b[i] >> p & 1) == 1) cb.push_back(b[i]);
        }
        for (int i = l; i <= r; i++) {
          a[i] = ca[i - l];
          b[i] = cb[i - l];
        }
      } else {
        ok = false; break;
      }
    }
    if (ok) {
      vector<pair<int, int>> nseg;
      for (int i = 0; i < sz(seg); i++) {
        auto [l, r] = seg[i];
        int mid = l + SZ[i] - 1;

        if (mid - l + 1 > 0) {
          nseg.emplace_back(l, mid);
        }
        if (r - mid > 0) {
          nseg.emplace_back(mid + 1, r);
        }
      }
      seg = move(nseg);
    }
    return ok;
  };

  int ans = 0;
  for (int i = 30; i >= 0; i--) {
    if (chk(i)) ans |= 1 << i;
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
