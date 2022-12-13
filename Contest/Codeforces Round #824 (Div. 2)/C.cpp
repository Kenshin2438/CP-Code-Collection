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
  string s; cin >> s;

  vector<int> p(26, -1), q(26, -1);
  vector<vector<bool>> ok(
    26, vector<bool>(26, true)
  );
  for (int i = 0; i < 26; i++) ok[i][i] = false;

  for (int i = 0; i < n; i++) {
    if (p[s[i] - 'a'] != -1) continue;
    for (int j = 0; j < 26; j++) {
      if (ok[s[i] - 'a'][j]) {
        p[s[i] - 'a'] = j;
        q[j] = s[i] - 'a';
        for (int k = 0; k < 26; k++) {
          ok[k][j] = false;
        }
        int k = s[i] - 'a';
        do {
          ok[j][k] = false, k = q[k];
        } while (k != s[i] - 'a' && k != -1);
        break;
      }
    }
  }
  for (int i = 0; i < 26; i++) {
    if (p[i] == -1) {
      for (int k = i; k != -1; k = q[k]) {
        p[i] = k;
      }
      break;
    }
  }
  for (int i = 0; i < n; i++) {
    cout << char('a' + p[s[i] - 'a']);
  }
  cout << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
