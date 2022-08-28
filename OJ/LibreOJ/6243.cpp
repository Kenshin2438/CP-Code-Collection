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

const int N = 1024;
bitset<N> g[N], ans[N], final;

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
  pair<bool, bitset<N>> solver(bitset<N> x) {
    bitset<N> res;
    for (int i = B.size() - 1; i >= 0; i--) {
      if (x.test(i)) {
        if (B[i].test(i)) {
          x ^= B[i];
          res ^= path[i];
        } else {
          return {false, res};
        }
      }
    }
    return {true, res};
  }
};

void solve() {
  int n; cin >> n;
  for (int i = 1; i <= n; i++) {
    string s; cin >> s;
    for (int j = 0; j < n; j++) {
      if (s[j] == '#') g[i].set(j);
    }
  }

  { // Light chasing
    bitset<N> now, nex, pre;
    for (int i = 1; i <= n; i++) {
      nex = (now << 1) ^ now ^ (now >> 1) ^ pre ^ g[i];
      nex.reset(n);

      pre = now, now = nex;
    }
    final = move(now);
  }

  static const auto getVec = [n](int id) {
    bitset<N> now, nex, pre;
    now.set(id);
    for (int i = 1; i <= n; i++) {
      nex = (now << 1) ^ now ^ (now >> 1) ^ pre;
      nex.reset(n);

      pre = now, now = nex;
    }
    return now;
  };

  Basis<N> B(n);
  for (int i = 0; i < n; i++) {
    auto x = getVec(i);
    B.insert(x, i);
  }

  bool ok = false;
  tie(ok, ans[1]) = B.solver(final);
  if (ok == false) return cout << "No solution\n", void();

  for (int i = 1; i < n; i++) {
    ans[i + 1] = (ans[i] << 1) ^ ans[i] ^ (ans[i] >> 1) ^ ans[i - 1] ^ g[i];
    ans[i + 1].reset(n);
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 0; j < n; j++) {
      cout << (ans[i].test(j) ? '#' : '.');
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
