#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)

template<typename T> 
struct Basis {
  vector<T> B;
  int sz;
  bool free = false;

  Basis(int n) : B(n) {};
  void insert(T v) {
    for (int i = B.size() - 1; i >= 0; i--) {
      if ((v >> i & 1) == 0) continue;
      if (B[i]) v ^= B[i];
      else {
        for (int j = i - 1; j >= 0; j--) 
          if (v >> j & 1) v ^= B[j];
        for (int j = i + 1; j < (int) B.size(); j++) 
          if (B[j] >> i & 1) B[j] ^= v;
        B[i] = v, sz += 1;
        return;
      }
    }
    free = true;
  }
  T kth(long long k) { // start from 1-index
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
  T max() {
    T res = 0;
    for (int i = 0; i < (int) B.size(); i++) {
      res ^= B[i];
    }
    return res;
  }
};

void solve() {
  int n; cin >> n;
  Basis<ll> B(61);
  for (int i = 1; i <= n; i++) {
    ll x; cin >> x;
    B.insert(x);
  }
  cout << B.max() << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T = 1;
  cin >> T;
  while (T--) solve();
  return 0;
}