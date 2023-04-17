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

struct FenwickTree {
  vector<ll> s;
  FenwickTree(int n) : s(n) {}
  void update(int pos, ll dif) {
    for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
  }
  ll query(int pos) { // [0, pos)
    ll res = 0;
    for (; pos > 0; pos &= pos - 1) res += s[pos - 1];
    return res;
  }
};

void solve() {
  int n, k, q; cin >> n >> k >> q;
  vector<int> a(n);
  for (auto &&x : a) cin >> x;

  const auto inversion_counting = [&](const vector<int> &v) -> ll {
    FenwickTree ft(k + 1);
    ll ans = 0;
    for (const auto &x : v) {
      ans += ft.query(k + 1) - ft.query(x + 1);
      ft.update(x, 1);
    }
    return ans;
  };

  vector<vector<int>> pos(k + 1);
  for (int i = 0; i < n; i++) {
    pos[a[i]].emplace_back(i);
  }
  vector<int> Mpl(k + 1);
  iota(all(Mpl), 0);

  unordered_map<ll, ll> backup;
  const auto myHash = [](int x, int y) -> ll {
    return ll(x) << 31 | y;
  };
  const auto calc = [&](int a, int b) {
    if (backup.find(myHash(a, b)) != end(backup)) 
      return backup[myHash(a, b)];
    if (backup.find(myHash(b, a)) != end(backup))
      return 1LL * sz(pos[Mpl[a]]) * sz(pos[Mpl[b]]) - backup[myHash(b, a)]; 

    ll & res = backup[myHash(a, b)] = 0LL;
    if (sz(pos[Mpl[a]]) < sz(pos[Mpl[b]])) {
      for (const int &idx : pos[Mpl[a]]) {
        res += 
      }
    } else {

    }
  };

  ll inv = inversion_counting(a);
  for (int _ = 0; _ < q; _++) {
    int x; cin >> x;
    inv = inv - 
    swap(Mpl[x], Mpl[x + 1]);
    cout << inv << "\n";
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}