#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

ll F(int l, int r) {
  if (l > r) return 0LL;
  ll S1 = (l + r) * 1LL * (r - l + 1) / 2;

  ll S2r = r * 1LL * (r + 1) * (2 * r + 1) / 6;
  --l;
  ll S2l = l * 1LL * (l + 1) * (2 * l + 1) / 6;
  return (S1 + S2r - S2l) / 2;
}

ll S(int a, int b, int c) {
  if (a < 1 || b < 1 || c < 2) return 0LL;
  // solve [1, a] + [1, b] <= [1, c]
  a = min(a, c - 1), b = min(b, c - 1);
  if (a > b) swap(a, b); // s.t. a <= b
  ll res = 0LL;
  if (c > a + b) {
    res += a * 1LL * b * (c - (a + b));
    c = a + b;
  }
  // c <= a + b, a <= b < c
  res += b * 1LL * (b - 1) / 2 * (c - b);
  res += (c - b) * 1LL * (1 + c - b) / 2 * b;
  res += F(c - a, b - 1);
  return res;
}

ll calc(int a, int b, int c, int d) { // d is fixed
  if (a < 1 || b < 1 || c < 1 || d < 1) return 0LL;
  ll res = a * 1LL * b * c;
  { // d is the largest edge
    if (d - 1 >= 2) res -= S(a, b, d - 1);
    if (d - c >= 3) res += S(a, b, d - c - 1);
  }
  { // (a or b or c) is the largest number
    if (a - d >= 2) res -= S(b, c, a - d);
    if (b - d >= 2) res -= S(a, c, b - d);
    if (c - d >= 2) res -= S(a, b, c - d);
  }
  return res;
}

int p[4][2];
void solve() {
  for (int i = 0; i < 4; i++) {
    cin >> p[i][0] >> p[i][1];
    --p[i][0];
  }
  ll ans = 0LL;
  for (int d = p[3][0] + 1; d <= p[3][1]; d++) {
    ans += calc(p[0][1], p[1][1], p[2][1], d);
    ans -= calc(p[0][0], p[1][1], p[2][1], d);
    ans -= calc(p[0][1], p[1][0], p[2][1], d);
    ans -= calc(p[0][1], p[1][1], p[2][0], d);
    ans += calc(p[0][0], p[1][0], p[2][1], d);
    ans += calc(p[0][0], p[1][1], p[2][0], d);
    ans += calc(p[0][1], p[1][0], p[2][0], d);
    ans -= calc(p[0][0], p[1][0], p[2][0], d);
  }
  cout << ans << '\n';
}

signed main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T; cin >> T;
  while (T--) solve();

  return 0;
}
