#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

const int mod = 998244353;

void solve() {
  int n, s; cin >> n >> s;
  vector<int> a(n), b(n);
  for (int &x : a) cin >> x;
  for (int &x : b) cin >> x;
  
  // for_all i in range(n), s.t. a[i]-b[i]<=s
  vector<int> pa(n + 1, -1), pb(n + 1, -1);
  for (int i = 0; i < n; i++) {
    pa[ a[i] ] = i;
    if (b[i] != -1) {
      if (a[i] - b[i] > s) return cout << "0\n", void();
      pb[ b[i] ] = i;
    }
  }
  ll ans = 1LL;
  int cnt = 0;
  for (int i = n; i > n - s; i--) {
    cnt += int(pb[i] == -1);
  }
  for (int i = n; i >= 1; i--) {
    if (i - s >= 1) cnt += int(pb[i - s] == -1);
    if (b[ pa[i] ] == -1) {
      ans = ans * cnt % mod;
      -- cnt;
    }
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T = 1;
  cin >> T;
  while (T--) solve();
  return 0;
}