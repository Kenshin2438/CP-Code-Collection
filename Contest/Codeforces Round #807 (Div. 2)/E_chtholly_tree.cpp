#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

struct ODT {
  map<int, int> mp;

  ODT() = default;
  ODT(int _, int unit) { mp[_ - 1] = unit; }
  ~ODT() = default;

  void split(int x) { mp[x] = prev(mp.upper_bound(x))->second; }
  int get(int x) { return prev(mp.upper_bound(x))->second; }
  void assign(int l, int r, int v) {  // assign [l, r), value v
    split(l), split(r);
    auto it = mp.find(l);
    while (it->first != r) it = mp.erase(it);
    if (get(l - 1) != v) mp[l] = v;
    if (it->second == v) mp.erase(it);
  }

  int answer() {
    while (true) {
      int p = mp.rbegin()->first;
      if (get(p - 1) == 1) return p - 1;
      else mp.erase(p);
    }
    return -1;
  }
  void op(int x) {
    split(x);
    auto it = mp.find(x);
    int v = it->second;
    while (it->second == v) it = mp.erase(it);
    mp[x] = v ^ 1;
    assign(it->first, it->first + 1, v);
  }
};

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, q; cin >> n >> q;
  vector<int> a(n);
  for (int &x : a) cin >> x;

  const int N = 2e5 + 100;
  vector<int> cnt(N, 0);
  for (int x : a) cnt[x] += 1; 
  for (int i = 1; i + 1 < N; i++) {
    cnt[i + 1] += cnt[i] / 2, cnt[i] %= 2;
  }
  ODT S(0, 0);
  for (int i = 1, l = 0, r = 0; i < N; i++) {
    if (cnt[i] == cnt[l]) {
      r = i;
    } else {
      S.assign(l, i, cnt[l]);
      l = r = i;
    }
  }
  while (q--) {
    int p, v; cin >> p >> v;
    --p;
    if (S.get(a[p]) == 0) {
      S.op(a[p]);
    } else {
      S.assign(a[p], a[p] + 1, 0);
    }
    a[p] = v;
    if (S.get(a[p]) == 0) {
      S.assign(a[p], a[p] + 1, 1);
    } else {
      S.op(a[p]);
    }
    cout << S.answer() << '\n';
  }
  return 0;
}