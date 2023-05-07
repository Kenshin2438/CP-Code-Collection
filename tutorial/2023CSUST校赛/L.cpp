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

using ull = unsigned long long;
ull modmul(ull a, ull b, ull M) {
  ll ret = a * b - M * ull(1.L / M * a * b);
  return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull modpow(ull b, ull e, ull mod) {
  ull ans = 1;
  for (; e; b = modmul(b, b, mod), e /= 2)
    if (e & 1) ans = modmul(ans, b, mod);
  return ans;
}
bool miller_rabin(ull n) {
  static const vector<ull> SPRP {
    2, 325, 9375, 28178, 450775, 9780504, 1795265022
  };
  if (n == 1 || n % 6 % 4 != 1) return (n | 1) == 3;
  ll t = __builtin_ctzll(n - 1), k = (n - 1) >> t;
  for (const ull &a : SPRP) {
    ull tmp = modpow(a, k, n);
    if (tmp <= 1 || tmp == n - 1) continue;
    for (int i = 0; i <= t; i++) {
      if (i == t) return false;
      tmp = modmul(tmp, tmp, n);
      if (tmp == n - 1) break;
    }
  }
  return true;
}

void solve() {
  constexpr ll L = 1'000'000'000'000'000'081LL;
  constexpr ll R = 1'000'000'000'000'100'081LL;

  const auto isPrime = [](ll n) -> bool {
    // if (n == 1 || n % 6 % 4 != 1) return (n | 1) == 3;
    // for (ll i = 5; i * i <= n; i += 2) 
    //   if (n % i == 0) return false;
    // return true;
    return miller_rabin(n);
  };

  for (ll i = L; i <= R; i++) {
    if (isPrime(i) == true) return cout << i << '\n', void();
  }

  assert(false);
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
 