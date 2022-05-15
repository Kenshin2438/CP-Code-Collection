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
  vec<PII> s(n);
  int sum = 0;
  for (int i = 1; i <= n; i++) {
    cin >> s[i - 1].fi;
    s[i - 1].se = i;
    sum += s[i - 1].fi;
  }
  sort(all(s), greater<PII>());
  if (sum - s.front().fi < s.front().fi) {
    cout << "impossible\n";
  } else {
    for (auto [_, rk] : s) cout << rk << ' ';
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
