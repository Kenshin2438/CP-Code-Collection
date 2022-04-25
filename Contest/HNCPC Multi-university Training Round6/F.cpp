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
  str s; cin >> s;
  set<PII> point;
  set<pair<PII, PII>> line;
  int x = 0, y = 0;
  point.insert(PII{x, y});
  for (char op : s) {
    int sx = x, sy = y;
    int tx = x, ty = y;
    if (op == 'U') ty++;
    if (op == 'D') ty--;
    if (op == 'R') tx++;
    if (op == 'L') tx--;
    point.insert(PII{x = tx, y = ty});

    if (sx > tx) {
      swap(sx, tx), swap(sy, ty);
    } else if (sx == tx) {
      if (sy > ty) {
        swap(sx, tx), swap(sy, ty);
      } else if(sy == ty) {
        assert(false);
      }
    }
    line.insert(make_pair(PII{sx, sy}, PII{tx, ty}));
  }
  int V = SZ(point);
  int E = SZ(line);
  cout << 2 + E - V << '\n';
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
