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

const int N = 1e6 + 10;
bitset<N> ntp;
vector<int> p;

unordered_set<ll> S;
void init() {
  for (int i = 2; i < N; i++) {
    if (ntp.test(i) == false) p.emplace_back(i);
    for (const int &pr : p) {
      if (pr * 1LL * i >= N) break;
      ntp.set(pr * i);
      if (i % pr == 0) break;
    }
  }
  for (const int &pr : p) S.insert(pr * 1LL * pr);
}

void solve() {
  ll n; cin >> n;
  cout << (S.count(n) ? "YES" : "NO") << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  init();

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
