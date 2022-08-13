#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)

const int mod = 10086;

template<typename T>
struct Basis {
  vector<T> B;
  int sz = 0;
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
  T max() {
    T res = 0;
    for (int i = 0; i < (int) B.size(); i++) {
      res ^= B[i];
    }
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

ll qpow(ll x, ll n, ll mod) {
  ll res = 1LL;
  for (x %= mod; n; n >>= 1, x = x * x % mod) {
    if (n & 1LL) res = res * x % mod;
  }
  return res;
}

void solve() {
  int n; cin >> n;
  Basis<int> B(32);
  for (int i = 1; i <= n; i++) {
    int x; cin >> x;
    B.insert(x);
  }
  int q; cin >> q;
  debug(B.rank(q));
  ll rk = (B.rank(q) % mod * qpow(2, n - B.size(), mod) % mod + 1) % mod;
  cout << rk << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T = 1;
  // cin >> T;
  while (T--) solve();
  return 0;
}
