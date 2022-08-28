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

// D1
// void solve() {
//   int n; cin >> n;
//   vector<int> a(n);
//   for (int &x : a) cin >> x;
//
//   vector<int> dp(n, 1);
//   for (int i = 0; i < n; i++) {
//     for (int j = i - 1; j >= max(0, i - 300); j--) {
//       if ((a[i] ^ j) > (a[j] ^ i)) {
//         dp[i] = max(dp[i], 1 + dp[j]);
//       }
//     }
//   }
//   cout << *max_element(all(dp)) << '\n';
// }

// D2
struct binary_trie {
  struct node {
    int val;
    array<int, 2> dp{};
    array<node *, 2> next{};
  };
  node * root = nullptr;

  explicit binary_trie() {
    root = new node{0, {}, {}};
  }
  int query(int n, int id) {
    int res = 1;
    node * cur = root;
    for (int i = 30; i >= 0; i--) {
      int bit = n >> i & 1;
      if (cur->next[bit ^ 1]) {
        res = max(res, cur->next[bit ^ 1]->dp[id >> i & 1] + 1);
      }
      if (cur->next[bit]) cur = cur->next[bit];
      else break;
    }
    return res;
  }
  void insert(int n, int a, int dp) {
    node * cur = root;
    for (int i = 30; i >= 0; i--) {
      int bit = n >> i & 1;
      if (cur->next[bit] == nullptr) {
        cur->next[bit] = new node{bit, {}, {}};
      }
      cur = cur->next[bit];
      cur->dp[a >> i & 1] = max(cur->dp[a >> i & 1], dp);
    }
  }
};

void solve() {
  int n; cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];

  binary_trie trie;
  vector<int> dp(n, 1);
  for (int i = 0; i < n; i++) {
    dp[i] = trie.query(a[i] ^ i, i);
    trie.insert(a[i] ^ i, a[i], dp[i]);
  }
  cout << *max_element(all(dp)) << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
