#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

void solve() {
  int n; cin >> n;
  string s1, s2; cin >> s1 >> s2;

  int m = 0;
  for (int i = 0; i < n; i++) {
    m += s1[i] == s2[i];
  }
  cout << m << ' ';

  int M = m, a = 0, b = 0;
  // even
  for (int i = 1, tmp = 0; i < n; i++) {
    tmp = m;
    for (int len = 1; ; len++) {
      int l = i - len, r = i + len - 1;
      if (l < 0 || r >= n) break;
      tmp -= (s1[r] == s2[r]) + (s1[l] == s2[l]);
      tmp += (s1[r] == s2[l]) + (s1[l] == s2[r]);
      if (tmp > M) M = tmp, a = l, b = r;
      else if (tmp == M && (b - a) > (r - l)) a = l, b = r;
    }
  }
  // odd
  for (int i = 0, tmp = 0; i < n; i++) {
    tmp = m;
    for (int len = 1; ; len++) {
      int l = i - len, r = i + len;
      if (l < 0 || r >= n) break;
      tmp -= (s1[r] == s2[r]) + (s1[l] == s2[l]);
      tmp += (s1[r] == s2[l]) + (s1[l] == s2[r]);
      if (tmp > M) M = tmp, a = l, b = r;
      else if (tmp == M && (b - a) > (r - l)) a = l, b = r;
    }
  }
  cout << M << ' ' << (a + 1) << ' ' << (b + 1) << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
