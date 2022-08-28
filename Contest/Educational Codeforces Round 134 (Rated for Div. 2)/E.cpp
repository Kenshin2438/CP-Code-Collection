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
  string s; cin >> s;
  int n = s.length();

  vector<int> lps(sz(s) + 15, 0);
  vector<array<int, 26>> aut(sz(s) + 15);
  aut[0][s[0] - 'a'] = 1;
  for (int i = 1; i < sz(s); i++) {
    for (int c = 0; c < 26; c++) {
      if (i > 0 && 'a' + c != s[i]) {
        aut[i][c] = aut[lps[i - 1]][c];
      } else {
        aut[i][c] = i + ('a' + c == s[i]);
      }
    }
    lps[i] = aut[lps[i - 1]][s[i] - 'a'];
  }

  int q; cin >> q;
  while (q--) {
    string t; cin >> t;
    s += t;
    for (int i = n; i < sz(s); i++) {
      for (int c = 0; c < 26; c++) {
        if (i > 0 && 'a' + c != s[i]) {
          aut[i][c] = aut[lps[i - 1]][c];
        } else {
          aut[i][c] = i + ('a' + c == s[i]);
        }
      }
      lps[i] = aut[lps[i - 1]][s[i] - 'a'];
    }
    for (int i = n; i < sz(s); i++) {
      cout << lps[i] << " \n"[i + 1 == sz(s)];
    }
    while (sz(s) > n) s.pop_back();
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
