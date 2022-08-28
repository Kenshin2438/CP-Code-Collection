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

template <size_t N> struct Basis {
  vector<bitset<N>> B, path;
  int sz = 0;

  Basis(int n) : B(n), path(n) {};

  void insert(bitset<N> v, int id) {
    bitset<N> cur; cur.set(id);
    for (int i = B.size() - 1; i >= 0; i--) {
      if (v.test(i) == false) continue;
      if (B[i].test(i)) {
        v ^= B[i], cur ^= path[i];
      } else {
        for (int j = i - 1; j >= 0; j--)
          if (v.test(j)) v ^= B[j], cur ^= path[j];
        for (int j = i + 1; j < (int) B.size(); j++)
          if (B[j].test(i)) B[j] ^= v, path[j] ^= cur;
        B[i] = v, path[i] = cur, sz += 1;
        return;
      }
    }
  }
  int size() { return sz; }
};


void solve() {
  int n; cin >> n;

  Basis<500> B(n);
  for (int i = 0; i < n; i++) {
    bitset<500> v;
    for (int j = 0; j < n; j++) {
      int b; cin >> b; v[j] = b;
    }
    B.insert(v, i);
  }

  if (B.size() != n) return cout << -1 << '\n', void();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (B.path[i].test(j)) cout << (j + 1) << ' ';
    }
    cout << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
