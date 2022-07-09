#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

void solve() {
  int n; cin >> n;
  cout << 2 << '\n';
  vector<int> vis(n + 1, false);
  for (int i = 1; i <= n; i++) {
    if (vis[i] == true) continue;
    for (int j = i; j <= n; j *= 2) {
      if (!vis[j]) cout << j << ' ', vis[j] = true;
      else break;
    }
  }
  cout << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T = 1;
  cin >> T;
  while (T--) solve();
  return 0;
}