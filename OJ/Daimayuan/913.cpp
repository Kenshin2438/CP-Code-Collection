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

/**
   (y - 1) * d + x \equiv (x - 1) * d + y \pmod{w}
-> (x - y) * (d - 1) \equiv 0 \pmod{w}

w / gcd(d - 1, w) | (y - x)
s.t. x < y and 1 \leq x, y \leq \min(m, d) = LIM

let g = w / gcd(d - 1, w)
answer = \sum_{x=1}^{LIM}\sum_{y=x+1}^{LIM}[g | (y - x)]
       = \sum_{D=1}^{LIM - 1}[D / g]

------------------------
Sample:
5
6 7 4
10 7 12
12 30 7
1 1 1
3247834 10298779 625324

Ans:
6
9
5
0
116461800
------------------------

**/

void SingleTest(int TestCase) {
  ll m, d, w; cin >> m >> d >> w;
  ll LIM = min(m, d), g = w / __gcd(d - 1, w);
  // for (ll D = 1; D < LIM; D ++) ans += D / g;
  ll n = (LIM - 1) / g;
  ll ans = (n - 1) * n / 2 * g + (LIM - g * n) * n;
  cout << ans << '\n';
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
