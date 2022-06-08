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

void SingleTest(__attribute__((unused)) int TestCase) {
  int n; cin >> n;

  vec<int> s(n), f(n);
  for (int &x : s) cin >> x;
  for (int &x : f) cin >> x;

  vec<int> d(n);

  for (int i = 1; i < n; i++) {
    s[i] = max(s[i], f[i - 1]);
  }

  for (int i = 0; i < n; i++) {
    d[i] = f[i] - s[i];
  }

  for (const int &x : d) cout << x << ' ';
  cout << '\n';
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
