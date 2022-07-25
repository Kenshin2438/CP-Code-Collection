#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

#define sz(x) static_cast<int>((x).size())

template <typename T>
struct ST {
  vector<vector<T>> st;
  T f(const T &a, const T &b) {
    return max<T>(a, b);
  }

  ST() = default;
  ST(const vector<T> &v) : st(1, v) {
    for (int pw = 1, k = 1; (pw << 1) <= sz(v); pw <<= 1, k++) {
      st.emplace_back(sz(v) - (pw << 1) + 1);
      for (int i = 0; i < sz(st[k]); i++) {
        st[k][i] = f(st[k - 1][i], st[k - 1][i + pw]);
      }
    }
  }
  ~ST() = default;

  T query(int l, int r) {  // query [l, r)
    int dep = 31 - __builtin_clz(r - l);
    return f(st[dep][l], st[dep][r - (1 << dep)]);
  }
};

void solve() {
  int n, m; cin >> n >> m;
  vector<int> a(m);
  for (int &x : a) cin >> x;

  ST<int> RMQ(a);
  int q; cin >> q;
  while (q--) {
    int sx, sy; cin >> sx >> sy;
    int tx, ty; cin >> tx >> ty;
    int k; cin >> k;
    if (abs(tx - sx) % k || abs(ty - sy) % k) {
      cout << "NO" << '\n';
    } else {
      if (sy > ty) swap(sy, ty), swap(sx, tx);
      int X = (n - sx) / k * k + sx;
      if (RMQ.query(sy - 1, ty) < X) cout << "YES\n";
      else cout << "NO\n";
    }
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
