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

int query(int a, int b) {
  cout << "? " << a << ' ' << b << endl;
  int res; cin >> res;
  return res;
}

void answer(int x) { cout << "! " << x << endl; }

void solve() {
  int n; cin >> n;
  vector<int> p(1 << n); iota(all(p), 1);
#define sz(x) static_cast<int>(x.size())
  while (sz(p) > 1) {
    vector<int> q;
    if (sz(p) == 2) {
      q.emplace_back(query(p[0], p[1]) == 1 ? p[0] : p[1]);
    } else {
      for (int i = 0; i < sz(p); i += 4) {
        int a = p[i], b = p[i + 1], c = p[i + 2], d = p[i + 3];

        int r1 = query(a, c);
        if (r1 == 0) q.emplace_back(query(b, d) == 1 ? b : d);
        else if (r1 == 1) q.emplace_back(query(a, d) == 1 ? a : d);
        else q.emplace_back(query(b, c) == 1 ? b : c);
      }
    }
    p = move(q);
  }
#undef sz
  answer(p[0]);
}

int main() {
  // cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
