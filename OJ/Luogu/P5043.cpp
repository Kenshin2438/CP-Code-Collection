#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)

using ull = unsigned long long;

#include <bits/extc++.h>
const int SEED = chrono::steady_clock::now().time_since_epoch().count();
struct chash {  // To use most bits rather than just the lowest ones:
  const ull C = ll(4e18 * acos(0)) | 71;  // large odd number
  ll operator()(ll x) const { return __builtin_bswap64((x ^ SEED) * C); }
};
using HashMap = __gnu_pbds::gp_hash_table<ll, int, chash>;

ull splitmix64(ull x) {
  // http://xorshift.di.unimi.it/splitmix64.c
  x += 0x9e3779b97f4a7c15;
  x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
  x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
  return x ^ (x >> 31);
}

void solve() {
  int m; cin >> m;
  HashMap Mp;
  for (int i = 1; i <= m; i++) {
    int n; cin >> n;
    vector<vector<int>> tree(n);
    int rt = 0;
    for (int i = 0; i < n; i++) {
      int p; cin >> p;
      if (p != 0) {
        tree[p - 1].emplace_back(i);
      } else rt = i;
    }
    vector<ull> H(n, 1);
    function<void(int, int)> dfs = [&](int u, int fa) {
      for (const int &v : tree[u]) {
        if (v == fa) continue;
        dfs(v, u);
        H[u] += splitmix64(H[v] ^ SEED);
      }
    };
    dfs(rt, rt);
    vector<ull> G(n); G[rt] = H[rt];
    function<void(int, int)> sol = [&](int u, int fa) {
      for (const int &v : tree[u]) {
        if (v == fa) continue;
        G[v] = H[v] + splitmix64((G[u] - splitmix64(H[v] ^ SEED)) ^ SEED);
        sol(v, u);
      }
    };
    sol(rt, rt);
    int ans = i;
    for (const ull &H : G) {
      if (Mp.find(H) != end(Mp)) { ans = Mp[H]; break; }
    }
    cout << ans << '\n';
    for (const ull &H : G) Mp[H] = ans;
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
