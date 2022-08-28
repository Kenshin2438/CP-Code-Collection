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

struct binary_trie {
  struct node {
    int bit;
    vector<int> v;
    array<node *, 2> next;

    node(int b) : bit(b) {
      v.clear(), next[0] = next[1] = nullptr;
    };
  };
  node * root = nullptr;

  explicit binary_trie() { root = new node(0); }
  void insert(int n, int id) {
    node * cur = root;
    for (int i = 30; i >= 0; i--) {
      int bit = n >> i & 1;
      if (cur->next[bit] == nullptr) {
        cur->next[bit] = new node(bit);
      }
      cur = cur->next[bit];
      cur->v.emplace_back(id);
    }
  }

  pair<ll, int> solver() const {
    array<array<ll, 2>, 31> cnt {};
    const function<void(node *, int)> dfs = [&](node *cur, int w) {
      if (w == -1 || cur == nullptr) return;
      if (!cur->next[0] || !cur->next[1]) {
        if (cur->next[0]) dfs(cur->next[0], w - 1);
        if (cur->next[1]) dfs(cur->next[1], w - 1);
        return;
      }

      ll inv = 0; int o = 0; 
      for (const int &i : cur->next[0]->v) {
        while (o < sz(cur->next[1]->v) && cur->next[1]->v[o] < i) {
          o++;
        }
        inv += o;
      }
      cnt[w][0] += inv;
      cnt[w][1] += sz(cur->next[1]->v) * 1LL * sz(cur->next[0]->v) - inv;
      if (cur->next[0]) dfs(cur->next[0], w - 1);
      if (cur->next[1]) dfs(cur->next[1], w - 1);
    };
    dfs(root, 30);
    ll inv = 0; int x = 0;
    for (int i = 30; i >= 0; i--) {
      if (cnt[i][0] <= cnt[i][1]) {
        inv += cnt[i][0];
        x |= 0 << i;
      } else {
        inv += cnt[i][1];
        x |= 1 << i;
      }
    }
    return {inv, x};
  }
};

void solve() {
  binary_trie trie;

  int n; cin >> n;
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    trie.insert(x, i);
  }

  auto [cnt, x] = trie.solver();
  cout << cnt << ' ' << x << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
