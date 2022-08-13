#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

std::mt19937 rng(__builtin_ia32_rdtsc());
template <typename T>
inline T randint(T l, T r) {
  return std::uniform_int_distribution<T>(l, r)(rng);
}
template <typename E>
inline E randreal(E l, E r) {
  return std::uniform_real_distribution<E>(l, r)(rng);
}

bool isprime(int n) {
  if (n <= 1 || n % 2 == 0) return n == 2;
  for (int x = 3; x * x <= n; x += 2) {
    if (n % x == 0) return false;
  }
  return true;
}

void solve() {
  int T = 1, P;
  do P = randint<int>(2, 5000); while (!isprime(P));
  ll n = randint<ll>(1, 10000);
  ll k = randint<ll>(1, 10000);
  if (n < k) swap(n, k);
  cout << T << " " << P << "\n" << n << " " << k << "\n";
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
