#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

const int N = 1e5 + 100;

ll a[N], pre[N], n, to[N], K;

bool check(int be, ll atk, int k) {
  debug(be, atk, k);
  if (k <= 0) return false;
  if (be == n + 1) return true;
  if (atk >= a[be]) return check(be + 1, atk + a[be], K);
  int p1 = be, p2 = -1;
  for (; p1 <= n && p1 <= be + k - 1; p1++) {
    if (atk >= a[p1]) {
      p2 = p1;
      while (p2 - 1 >= be) {
        if (to[p2] != 0) p2 = to[p2];

        if (atk + pre[p1] - pre[p2 - 1] >= a[p2 - 1]) p2 -= 1;
        else break;
      }
      if (p2 == be) {
        return check(p1 + 1, atk + pre[p1] - pre[be - 1], be + K - p1);
      } else {
        to[p1] = p2;
      }
    }
  }
  return false;
}

void solve() {
  int A;
  cin >> n >> A >> K;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], pre[i] = pre[i - 1] + a[i];
    to[i] = 0;
  }
  bool ans = check(1, A, K);
  cout << (ans ? "YES" : "NO") << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
