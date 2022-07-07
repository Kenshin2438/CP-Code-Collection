#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

void solve() {
  int n, k; cin >> n >> k;
  vector<int> a(n);
  for (int &x : a) cin >> x;
  if (k == 1) {
    int ans = (n - 2 - 1) / 2 + 1;
    cout << ans << '\n';
    return ;
  }
  int ans = 0;
  for (int i = 1; i < n - 1; i++) {
    ans += (a[i] > a[i - 1] + a[i + 1]);
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T; cin >> T;
  while (T--) solve();
  return 0;
}