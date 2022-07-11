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

void SingleTest(__attribute__((unused)) int TestCase) {
  cout << "Case " << TestCase << ": ";
  db w1, h1, w2, h2; cin >> w1 >> h1 >> w2 >> h2;
  db ans = w1 * h1 + w2 * h2 + min({
    abs(w1 - w2) * (w1 > w2 ? h2 : h1),
    abs(h1 - h2) * (h1 > h2 ? w2 : w1),
    abs(h1 - w2) * (h1 > w2 ? h2 : w1),
    abs(w1 - h2) * (w1 > h2 ? w2 : h1)
  }) / 2;
  cout << ans << '\n';
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
