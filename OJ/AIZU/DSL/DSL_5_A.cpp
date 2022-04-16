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
#define all(a) a.begin(), a.end()

using db = double;
using ll = long long;

void SingleTest(int TestCase) {
  int n, t; cin >> n >> t;
  vec<int> num(t + 1, 0);
  for (int l, r; n--; ) {
    cin >> l >> r;
    num[l]++, num[r]--;
  }
  for (int i = 1; i <= t; i++) {
    num[i] += num[i - 1];
  }
  cout << *max_element(all(num)) << '\n';
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
