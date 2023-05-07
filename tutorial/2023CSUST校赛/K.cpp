#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

void solve() {
  string s; cin >> s;

  assert(1 <= sz(s) && sz(s) <= (int) 1E3);
  assert(all_of(all(s), 
        [](char c) { return c >= 'a' && c <= 'z'; }));

  vector<int> cnt(26);
  for (const char &c : s) cnt[c - 'a'] += 1;
  cout << *max_element(all(cnt)) << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  cin >> T;
  assert(1 <= T && T <= (int) 1E3);
  while (T--) solve();

  return 0;
}