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
#define rall(a) (a).rbegin(), (a).rend()
#define sz(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

/**



**/

void SingleTest(__attribute__((unused)) int TestCase) {
  int n; cin >> n;
  if (n == 1) return cout << "1\n1\n"  , void();
  if (n == 2) return cout << "2\n2 2\n", void();

  cout << 2  * (n - 2) << '\n';
  for (int i = 2; i <= n - 1; i++) cout << i << ' ';
  for (int i = n - 1; i >= 2; i--) cout << i << ' ';
  cout << '\n';
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