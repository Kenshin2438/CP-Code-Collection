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

template<class MapTy>
constexpr bool is_map_v = is_pair<typename MapTy::value_type>::value;

void solve() {
  int n, k; cin >> n >> k;
  string a, b; cin >> a >> b;

  map<char, int> pos;
  for (int i = 0; i < n; i++) {
    if (pos.find(a[i]) == end(pos)) pos[a[i]] = sz(pos);
  }
  debug(pos);
  is_map_v<map<int, int>>;

  const auto f = [&](ll x) { return x * (x + 1) / 2; };
  if (sz(pos) <= k) return cout << f(n) << '\n', void();

  ll ans = 0;
  for (int mask = 0; mask < (1 << sz(pos)); mask++) {
    int diff = __builtin_popcount(mask);
    if (diff > k) continue;
    
    int pre = 0;
    ll tmp = 0;
    for (int i = 0; i < n; i++) {
      if (a[i] == b[i]) continue;
      if (mask >> pos[a[i]] & 1) continue;
      tmp += f(i - pre);
      pre = i + 1;
    }
    tmp += f(n - pre);
    ans = max(ans, tmp);
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}