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
  static const vector<ull> SPRP = {
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

constexpr int LIM = 1e6;
bitset<LIM> isPrime;
vector<int> eratosthenes() {
  constexpr int S = 1e4, R = LIM / 2;
  vector<int> pr = {2}, sieve(S + 1);
  pr.reserve(int(LIM / log(LIM) * 1.1));
  vector<pair<int, int> > cp;
  for (int i = 3; i <= S; i += 2)
    if (!sieve[i]) {
      cp.push_back({i, i * i / 2});
      for (int j = i * i; j <= S; j += 2 * i) sieve[j] = 1;
    }
  for (int L = 1; L <= R; L += S) {
    array<bool, S> block{};
    for (auto &[p, idx] : cp)
      for (int i = idx; i < S + L; idx = (i += p)) block[i - L] = 1;
    for (int i = 0; i < min(S, R - L); i++)
      if (!block[i]) pr.push_back((L + i) * 2 + 1);
  }
  for (int i : pr) isPrime[i] = 1;
  return pr;
}

vector<int> prime;

void solve() {
  ll x; cin >> x;
  if (x % 2 == 1) {
    if (x == 1) return cout << 2 << '\n', void();
    if (x == 3) return cout << 4 << '\n', void();
    if (x == 5) return cout << -1 << '\n', void();
    if (x == 7) return cout << 8 << '\n', void();
    for (const int &p : prime) {
      if (x - 1 - p <= 0) break;
      if (isPrime[x - 1 - p]) {
        cout << (ll) (x - 1 - p) * p << '\n';
        return;
      }
    }
    cout << -1 << '\n';
  } else {
    if (isPrime.test(x - 1)) {
      cout << (ll) (x - 1) * (x - 1) << '\n';
    } else {
      cout << (x - 3) * 2 << '\n';
    }
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  prime = eratosthenes();

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}