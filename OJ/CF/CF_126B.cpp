#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

// z[i] = LCP(s, s.substr(i))

vector<int> Z_algorithm(const string &s) {
  int n = (int) s.length();
  vector<int> z(n); z[0] = n;
  for (int i = 1, l = 0, r = 0; i < n; i++) {
    if (i <= r) z[i] = min(r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i] += 1;
    if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
  }
  return z;
}

void solve() {
  string s; cin >> s;
  auto z = Z_algorithm(s);
  set<int> ok;
  int n = s.length();
  for (int i = 0; i < n; i++) {
    if (z[i] == n - i) ok.insert(n - i);
  }
  vector<int> cnt(n + 2, 0);
  for (int i = 0; i < n; i++) {
    cnt[1]++, cnt[z[i] + 1]--;
  }
  int ans = -1;
  for (int i = 1; i <= n; i++) {
    cnt[i] += cnt[i - 1];
    if (cnt[i] >= 3 && ok.count(i)) ans = i;
  }
  if (ans != -1) {
    cout << s.substr(0, ans) << '\n';
  } else {
    cout << "Just a legend\n";
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
