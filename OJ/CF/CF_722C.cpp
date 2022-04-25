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

struct DSU {
  vec<ll> p, s;
  DSU(int _) : p(_ + 2), s(_ + 2, -1) { iota(all(p), 0); }
  int f(int _) { return _ == p[_] ? _ : p[_] = f(p[_]); }
  bool same(int u, int v) { return f(u) == f(v); }
  void unite(int u, int v) {
    if (!same(u, v)) {
      s[f(v)] += s[f(u)];
      p[f(u)] = f(v);
    }
  }
};

void SingleTest(int TestCase) {
  int n; cin >> n;
  vec<ll> a(n), p(n);
  for (auto &x : a) cin >> x;
  for (auto &x : p) cin >> x;
  vec<ll> ans(n);
  DSU set(n);
  ll A = 0;
  for (int i = n - 1; i >= 0; i--) {
    ans[i] = A;
    int cur = p[i];
    set.s[cur] = a[cur - 1];
    if (set.s[cur + 1] != -1) set.unite(cur, cur + 1);
    if (set.s[cur - 1] != -1) set.unite(cur, cur - 1);
    A = max(A, set.s[set.f(cur)]);

    debug(set.s, set.p);
  }
  for (int i = 0; i < n; i++) {
    cout << ans[i] << '\n';
  }
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
