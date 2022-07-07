#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  string s; cin >> s;
  int n = s.length();

  vector<int> pos;
  for (int i = 0; i < n; i++) {
    if (s[i] == '1') pos.push_back(i);
  }
  if (pos.size() == 0) {
    return cout << "-1\n", 0;
  } else if (pos.size() == 1) {
    cout << pos[0] + 1 << ' ' << pos[0] + 2 << '\n';
    return 0;
  } else if (pos.size() == 2) {
    cout << pos[0] + 1 << ' ' << pos[1] + 1 << '\n';
    return 0;
  }

  ll poly = 0LL;
  for (int x : pos) poly |= 1LL << x;
  poly >>= pos[0];
  ll ans = 1e18, H = pos.back() - pos.front();

  const auto mul = [&](ll x, ll y) -> ll {
    ll res = 0LL;
    for (; y; y >>= 1) {
      if (y & 1LL) res ^= x;
      x <<= 1; 
      if (x >> H & 1LL) x ^= poly;
    }
    return res;
  };
  { // BSGS solve x^k \equiv 1 ( mod Poly(x) ), find k
    const int S = 2e5;
    unordered_map<ll, int> BS;
    ll val = 1LL;
    for (int i = 0; i < S; i++) {
      BS[val] = i, val = mul(val, 2);
    }
    ll now = val;
    for (int i = 1; i < S; i++) {
      if (BS.count(now)) {
        ans = min(ans, 1LL * i * S - BS[now]);
      }
      now = mul(now, val);
    }
  }
  cout << pos[0] + 1 << ' ' << pos[0] + 1 + ans << '\n';
  return 0;
}