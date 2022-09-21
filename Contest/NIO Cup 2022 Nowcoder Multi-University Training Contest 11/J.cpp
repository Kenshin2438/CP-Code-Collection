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

std::mt19937 rng(__builtin_ia32_rdtsc());
template <typename T>
inline T randint(T l, T r) {
  return std::uniform_int_distribution<T>(l, r)(rng);
}
template <typename E>
inline E randreal(E l, E r) {
  return std::uniform_real_distribution<E>(l, r)(rng);
}

void solve() {
  int n; cin >> n;
  vector<int> a(n);
  for (int &x : a) cin >> x;

  vector<pair<int, int>> p;
  for (int i = 0; i < n; i++) {
    p.emplace_back(a[i], 1 << a[i]);
  }

  while (true) {
    vector<pair<int, int>> q;

    if (sz(q) == 1) return cout << "Yes\n", void();
    if (sz(p) == sz(q)) return cout << "No\n", void();
    p = move(q);
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
