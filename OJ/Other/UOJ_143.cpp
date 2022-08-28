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

void solve() {
  int n; cin >> n;
  vector<pair<int, int>> p(n);
  for (int i = 0; i < n; i++) {
    cin >> p[i].first;
    p[i].second = i + 1;
  }

  const function<void(int, int)> Sort = [&](int l, int r) {
    if (r - l + 1 < 3) return;
    int cnt = 0;
    for (int i = l; i <= r; i++) {
      cnt += p[i].first == 0;
    }
    if (cnt == r - l + 1) return;

    vector<pair<int, int>> q;
    for (int i = l; i <= r; i++) {
      if (p[i].first & 1) q.push_back(p[i]);
    }
    int pos = l + sz(q) - 1;
    for (int i = l; i <= r; i++) {
      if (~p[i].first & 1) q.push_back(p[i]);
    }
    for (int i = l; i <= r; i++) {
      p[i].first = q[i - l].first >> 1;
      p[i].second = q[i - l].second;
    }
    Sort(l, pos), Sort(pos + 1, r);
  };
  Sort(0, n - 1);

  for (const auto &[_, val] : p) cout << val << ' ';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}

/**

{s, k, t} 三个数为等差，等价于：s + t = 2 * k。显然此时{s, t}必须是奇偶性相同的两个数。
按照奇偶性分开后，只会在奇数或者偶数内部产生等差的三元组。

然后又可以得到如下关系:
三个奇数{2s+1, 2k+1, 2t+1}满足：(2s + 1) + (2t + 1) = 2 * (2k + 1)
三个偶数{2s, 2k, 2t}满足：(2s) + (2t) = 2 * (2k)

上面两个式子都等价为 s + t = 2 * k，所以将所有的数整除掉2之后和原问题一样。

**/
