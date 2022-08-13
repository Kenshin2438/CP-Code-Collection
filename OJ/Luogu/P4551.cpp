#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using u32 = unsigned;
template <u32 BitLength> struct binary_trie {
  struct node {  // 4-ary trie
    u32 val;
    u32 hgt;
    array<node *, 4> child;
  };

  explicit binary_trie() { _root = new node{0, inner_len, {}}; };

  void insert(u32 x) {
    x ^= _xor_val;
    node *v = _root;
    node **parent;
    size_t topbits = x >> (v->hgt - 2) & 3;
    if (!v->child[topbits]) {
      v->child[topbits] = new node{x, 0, {}};
      return;
    }
    parent = &v->child[topbits];
    v = v->child[topbits];
    while (true) {
      if (static_cast<int>(v->hgt) > bsr(x ^ v->val)) {
        if (!v->hgt) return;
        topbits = x >> (v->hgt - 2) & 3;
        if (v->child[topbits]) {
          parent = &v->child[topbits];
          v = v->child[topbits];
        } else {
          v->child[topbits] = new node{x, 0, {}};
          return;
        }
      } else {
        node *split_node = new node{v->val, (bsr(v->val ^ x) | 1) + 1u, {}};
        (split_node->val >>= split_node->hgt) <<= split_node->hgt;
        *parent = split_node;
        split_node->child[v->val >> (split_node->hgt - 2) & 3] = v;
        split_node->child[x >> (split_node->hgt - 2) & 3] = new node{x, 0, {}};
        return;
      }
    }
  }

  u32 max() const {
    node *v = _root;
    std::size_t topbits;
    while (v->hgt != 0) {
      topbits = (_xor_val >> (v->hgt - 2) & 3) ^ 3;
      for (std::size_t ind = 0; ind < 4; ind++) {
        if (v->child[ind ^ topbits]) {
          v = v->child[ind ^ topbits];
          break;
        }
      }
    }
    return v->val ^ _xor_val;
  }

  void xor_all(u32 xor_val) noexcept { _xor_val ^= xor_val; }

 private:
  u32 inner_len = (BitLength + 1u) & ~1u;
  node *_root;
  u32 _xor_val = 0;
  static constexpr int bsr(u32 t) {
    return (t == 0 ? -1 : 63 - __builtin_clzll(t));
  }
};

void solve() {
  int n; cin >> n;
  vector<vector<pair<int, int>>> tree(n);
  for (int i = 1; i < n; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    --u, --v;
    tree[v].emplace_back(u, w);
    tree[u].emplace_back(v, w);
  }
  vector<int> S(n);
  const function<void(int, int)> dfs = [&](int u, int fa) {
    for (const auto &[v, w] : tree[u]) {
      if (v == fa) continue;
      S[v] = S[u] ^ w;
      dfs(v, u);
    }
  };
  dfs(0, 0);

  sort(all(S)), S.erase(unique(all(S)), end(S));

  u32 ans = 0;
  binary_trie<29> bt;
  bt.insert(0);
  for (const int &x : S) {
    bt.xor_all(x), ans = max(ans, bt.max()), bt.xor_all(x);
    bt.insert(x);
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
