#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

struct FenwickTree {
#define SZ(a) static_cast<int>((a).size())
  vector<ll> s;
  FenwickTree(int n) : s(n) {}
  void update(int pos, ll dif) {
    for (; pos < SZ(s); pos |= pos + 1) s[pos] += dif;
  }
  ll query(int pos) {
    ll res = 0;
    for (; pos > 0; pos &= pos - 1) res += s[pos - 1];
    return res;
  }
};

void solve() {
  auto DigitalSum = [](ll n, ll x, ll y) -> int {
    ll d = min({x, y, n - x + 1, n - y + 1});
    ll num = n * n - (n - 2 * d + 2) * (n - 2 * d + 2);
    if (x == d) {
      num += (n - 2 * d + 2) * 2 - 2 + (y - d + 1);
    } else if (y == d) {
      num += (n - 2 * d + 2) * 1 - 1 + (n - d + 1 - x + 1);
    } else if (x == n - d + 1) {
      num += (n - d + 1 - y + 1);
    } else if (y == n - d + 1) {
      num += (n - 2 * d + 2) * 3 - 3 + (x - d + 1);
    }
    // return num;

    int res = 0;
    while (num) res += num % 10, num /= 10;
    return res;
  };

  int n, m, q; cin >> n >> m >> q;
  vector<array<int, 4>> Q;
  for (int i = 0; i < m; i++) {
    int x, y; cin >> x >> y;
    Q.push_back({x, y, 0, DigitalSum(n, x, y)});
  }
  for (int i = 0; i < q; i++) {
    int x1, x2, y1, y2; cin >> x1 >> y1 >> x2 >> y2;
    Q.push_back({x2, y2, 1, i});
    Q.push_back({x1 - 1, y1 - 1, 1, i});
    Q.push_back({x2, y1 - 1, -1, i});
    Q.push_back({x1 - 1, y2, -1, i});
  }
  sort(all(Q), [](auto A, auto B) {
    if (A[0] == B[0]) {
      if (A[1] == B[1]) {
        return abs(A[2]) < abs(B[2]);
      } else return A[1] < B[1];
    } else return A[0] < B[0];
  });
  vector<ll> ans(q);
  FenwickTree ft(n + 1);
  for (auto v : Q) {
    if (v[2] == 0) {
      ft.update(v[1], v[3]);
    } else {
      ans[v[3]] += ft.query(v[1] + 1) * v[2];
    }
  }
  for (ll &x : ans) cout << x << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T; cin >> T;
  while (T--) solve();

  return 0;
}
