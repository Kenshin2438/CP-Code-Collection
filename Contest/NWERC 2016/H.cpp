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
  str a, b; cin >> a >> b;
  auto getRank = [](const str& s) -> ll {
    int n = s.length();
    ll res = s[0] - '0';
    for (int i = 1; i < n; i++) {
      res <<= 1;
      res |= int(s[i] - '0') ^ (res >> 1 & 1);
    }
    return res;
  };
  ll A = getRank(a), B = getRank(b);
  tie(A, B) = minmax(A, B);
  cout << max(0LL, B - A - 1) << '\n';
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
