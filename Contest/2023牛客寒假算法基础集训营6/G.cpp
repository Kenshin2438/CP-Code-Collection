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
  int n, k; cin >> n >> k;
  vector<int> neg, pos;
  int zero = 0;
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    if (x > 0) pos.emplace_back(x);
    else if (x < 0) neg.emplace_back(x);
    else zero += 1;
  }
  sort(all(neg));
  sort(all(pos), greater<>());
  debug(pos, neg);

  vector<int> p, re;
  for (int i = 0; i + 1 < sz(pos); i += 2) {
    p.emplace_back(pos[i] * pos[i + 1]);
  }
  if (sz(pos) & 1) re.emplace_back(pos.back());
  for (int i = 0; i + 1 < sz(neg); i += 2) {
    p.emplace_back(neg[i] * neg[i + 1]);
  }
  if (sz(neg) & 1) re.emplace_back(neg.back());
  while (!re.empty() && zero) {
    zero--;
    re.pop_back();
    p.emplace_back(0);
  }
  if (sz(re) == 2) p.emplace_back(re[0] * re[1]);

  sort(all(p), greater<>());
  int s = 0;
  for (int i = 0; i < min(sz(p), k); i++) {
    s += p[i];
  }
  cout << s << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}