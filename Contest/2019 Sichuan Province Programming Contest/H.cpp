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
  int n, m; cin >> n >> m;
  vec<int> t(n), c(m);
  for (int &x : t) cin >> x;
  for (int &x : c) cin >> x;

  sort(all(t), greater<int>());
  sort(all(c), greater<int>());

  ll ans = 0, idx = 1;
  for (int x : c) {
    ans += t[idx - 1] + 20LL * (x - 1);
    idx += x;
  }
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
