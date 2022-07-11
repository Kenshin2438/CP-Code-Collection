#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

template <typename T>
struct ODT {
  map<int, T> mp;

  ODT() = default;
  ODT(int _, const T &u) { mp[_ - 1] = u; }
  ~ODT() = default;

  void split(int x) { mp[x] = prev(mp.upper_bound(x))->second; }
  T query(int l, int r) {  // query [l, r)
    split(l), split(r);
    auto it = mp.find(l);
    int res = 0;
    while (it->first != r) {
      res = max(res, it->second);
      it = mp.erase(it);
    }
    return mp[l] = res;
  }
};

constexpr int LIM = 20000;
vector<int> eratosthenes() {
  constexpr int S = 150, R = LIM / 2;
  vector<int> pr = {2}, sieve(S + 1);
  pr.reserve(int(LIM / log(LIM) * 1.1));
  vector<pair<int, int>> cp;
  for (int i = 3; i <= S; i += 2)
    if (!sieve[i]) {
      cp.push_back({i, i * i / 2});
      for (int j = i * i; j <= S; j += 2 * i) sieve[j] = 1;
    }
  for (int L = 1; L <= R; L += S) {
    array<bool, S> block{};
    for (auto &[p, idx] : cp)
      for (int i = idx; i < S + L; idx = (i += p)) block[i - L] = 1;
    for (int i = 0; i < min(S, R - L); i++)
      if (!block[i]) pr.push_back((L + i) * 2 + 1);
  }
  return pr;
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, q;
  cin >> n >> q;

  vector<ll> a(n);
  for (ll &x : a) cin >> x;

  vector<pair<int, int>> ops(q);
  for (auto &&[l, r] : ops) cin >> l >> r;
  vector<ll> ans(q, 1LL);

  auto pr = eratosthenes();
  int m = pr.size();

  const int mod = (int)1e9 + 7;
  for (const int &p : pr) {
    int sz = 0;

    ODT seg(0, 0);
    for (int i = 0; i < n; i++) {
      int pw = 0;
      while (a[i] % p == 0) {
        ++pw, a[i] /= p;
      }
      sz = max(sz, pw);
      seg.mp[i] = pw;
    }

    if (sz == 0) continue;
    vector<ll> pk(sz + 1, 1);
    for (int i = 1; i <= sz; i++) {
      pk[i] = pk[i - 1] * p % mod;
    }

    for (int i = 0; i < q; i++) {
      auto [l, r] = ops[i];
      ans[i] = ans[i] * pk[seg.query(l - 1, r)] % mod;
    }
  }

  for (const ll &x : ans) cout << x << '\n';
  return 0;
}