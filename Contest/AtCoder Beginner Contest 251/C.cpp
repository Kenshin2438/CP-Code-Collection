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

void SingleTest(int TestCase) {
  int n; cin >> n;
  set<str> S; // str score index
  vec<PII> p;
  for (int i = 1; i <= n; i++) {
    str s; cin >> s;
    int c; cin >> c;
    if (S.count(s)) continue;
    S.insert(s);
    p.push_back({c, i});
  }
  sort(all(p), [&](PII A, PII B) {
    return A.fi == B.fi ? (A.se < B.se) : (A.fi > B.fi);
  });
  cout << p[0].se << '\n';
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
