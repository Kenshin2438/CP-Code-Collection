#define PROBLEM "http://oj.daimayuan.top/problem/454"

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
#define pb push_back
#define all(a) a.begin(), a.end()

typedef double db;
typedef long long ll;

void SingleTest(int TestCase) {
  int n, m; cin >> n >> m;
  vec<array<int, 3>> e(m);
  for (auto &[u, v, c] : e) {
    cin >> u >> v >> c, --u, --v;
  }
  vec<int> p(n);
  const function<int (int)> f = [&](int x) {
    return x == p[x] ? x : p[x] = f(p[x]);
  };
  int ans = (1LL << 31) - 1, cnt; 
  for (int b = 30; ~b; b--) {
    iota(all(p), 0), ans ^= 1 << b, cnt = n - 1;
    for (auto [u, v, c] : e) {
      if ((c & ans) == c && (u = f(u)) != (v = f(v))) cnt--, p[u] = v;
    }
    if (cnt) ans ^= 1 << b;
  }
  cout << ans;
}

void init() { }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  // cin >> T;
  for (init(); T--; ) SingleTest(++TestCase);
  return 0;
}
