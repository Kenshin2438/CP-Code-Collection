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

using ull = unsigned long long;

#include <bits/extc++.h>
const int SEED = chrono::steady_clock::now().time_since_epoch().count();
struct chash {  // To use most bits rather than just the lowest ones:
  const ull C = ll(4e18 * acos(0)) | 71;  // large odd number
  ull operator()(ull x) const { return __builtin_bswap64((x ^ SEED) * C); }
};
using HashMap = __gnu_pbds::gp_hash_table<ull, int, chash>;

ull splitmix64(ull x) {
  // http://xorshift.di.unimi.it/splitmix64.c
  x += 0x9e3779b97f4a7c15;
  x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
  x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
  return x ^ (x >> 31);
}

struct tree_hash {
  int n; // vectex number
  vector<vector<int>> tree;
  vector<ull> H;
  // vector<ull> G;
  // H(u) -> Hash value of subtree(u)
  // G(u) -> Hash value of tree(u-rooted)
  tree_hash(const vector<vector<int>> &_) : tree(_) {
    n = (int) tree.size();
    H.assign(n, 1ULL);
    // G.resize(n);
    build();
  };

  void build() {
    function<void(int, int)> dfs = [&](int u, int fa) {
      for (const int &v : tree[u]) {
        if (v == fa) continue;
        dfs(v, u);
        H[u] += splitmix64(H[v] ^ SEED);
      }
    };
    dfs(0, 0);
    // G[0] = H[0];
    // function<void(int, int)> sol = [&](int u, int fa) {
    //   for (const int &v : tree[u]) {
    //     if (v == fa) continue;
    //     G[v] = H[v] + splitmix64((G[u] - splitmix64(H[v] ^ SEED)) ^ SEED);
    //     sol(v, u);
    //   }
    // };
    // sol(0, 0);
  }
};

void solve() {
  int n; cin >> n;
  vector<vector<int>> tree(n);
  for (int i = 1; i < n; i++) {
    int p; cin >> p;
    tree[p].push_back(i);
    tree[i].push_back(p);
  }

  tree_hash Th(tree);
  const auto &H = Th.H;

  vector<int> ans(n);
  HashMap Ht; int cnt = 0;
  for (int i = 0; i < n; i++) {
    if (Ht.find(H[i]) != end(Ht)) {
      ans[i] = Ht[H[i]];
    } else {
      Ht[H[i]] = ans[i] = cnt++;
    }
  }
  cout << cnt << '\n';
  for (int i = 0; i < n; i++) {
    cout << ans[i] << " \n"[i + 1 == n];
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
