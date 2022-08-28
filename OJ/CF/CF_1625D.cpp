#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) static_cast<int>(size(x))

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
    size_t topbits;
    while (v->hgt != 0) {
      topbits = (_xor_val >> (v->hgt - 2) & 3) ^ 3;
      for (size_t ind = 0; ind < 4; ind++) {
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
  int n, k; cin >> n >> k;
  vector<pair<int, int>> p(n);
  for (int i = 0; i < n; i++) {
    cin >> p[i].first, p[i].second = i + 1;
  }

  if (k == 0) {
    cout << n << '\n';
    for (int i = 1; i <= n; i++) cout << i << ' ';
  } else {
    int hbt = 32 - __builtin_clz(k);
    sort(all(p), [&](const auto &A, const auto &B) {
      return (A.first >> hbt) > (B.first >> hbt);
    });
    vector<int> ans;

    binary_trie<30> tr;
    map<int, int> val;
    int u = 0, v = 0;
    tr.insert(p[0].first), val[p[0].first] = p[0].second;

    for (int l = 0, r = 1; r < n; r++) {
      if ((p[r].first >> hbt) != (p[l].first >> hbt)) {
        if (u && v) ans.emplace_back(u), ans.emplace_back(v);
        else ans.emplace_back(p[l].second);

        u = v = 0, tr = move( binary_trie<30>() ), l = r, val.clear();
        tr.insert(p[r].first), val[p[r].first] = p[r].second;
      } else {
        // assert(false);

        tr.xor_all(p[r].first);
        int tmp = tr.max();
        tr.xor_all(p[r].first);
        if (tmp >= k) u = p[r].second, v = val[tmp ^ p[r].first];
        tr.insert(p[r].first), val[p[r].first] = p[r].second;
      }
    }
    if (u && v) ans.emplace_back(u), ans.emplace_back(v);
    else ans.emplace_back(p[n - 1].second);

    if (sz(ans) < 2) return cout << "-1\n", void();
    cout << sz(ans) << '\n';
    for (const int &x : ans) cout << x << ' ';
  }
  cout << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  debug(2 ^ 16);
  debug(2 ^ 14);
  debug(14 ^ 16);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
