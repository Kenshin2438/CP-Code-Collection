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

template<typename T> struct Basis {
  vector<T> B;
  int sz = 0;
  bool free = false;

  Basis(int n) : B(n) {};
  bool insert(T v) {
    for (int i = B.size() - 1; i >= 0; i--) {
      if ((v >> i & 1) == 0) continue;
      if (B[i]) v ^= B[i];
      else {
        for (int j = i - 1; j >= 0; j--)
          if (v >> j & 1) v ^= B[j];
        for (int j = i + 1; j < (int) B.size(); j++)
          if (B[j] >> i & 1) B[j] ^= v;
        B[i] = v, sz += 1;
        return true;
      }
    }
    free = true;
    return false;
  }
  T max() {
    T res = 0;
    for (int i = 0; i < (int) B.size(); i++) res ^= B[i];
    return res;
  }
  T kth(long long k) { // k start from 1-indexed
    if (free) k -= 1; // free -> 0
    if (k >= (1LL << sz)) return -1;
    T res = 0;
    for (int i = 0, t = 0; i < (int) B.size(); i++) {
      if (B[i] == 0) continue;
      if (k >> t & 1) res ^= B[i];
      t += 1;
    }
    return res;
  }
  long long rank(T v) { // rank start from 0-indexed
    long long res = 0;
    for (int i = 0, t = 0; i < (int) B.size(); i++) {
      if (B[i] == 0) continue;
      if (v >> i & 1) res |= 1LL << t;
      t += 1;
    }
    return res;
  }
  int size() { return sz; }
};

void solve() {
  Basis<ll> B(63);
  
  int n; cin >> n;
  vector<pair<ll, ll>> val(n);
  for (auto &&[mag, num] : val) {
    cin >> num >> mag;
  }
  sort(all(val), greater<>());
  ll ans = 0;
  for (const auto &[mag, num] : val) {
    if (B.insert(num)) ans += mag;
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
