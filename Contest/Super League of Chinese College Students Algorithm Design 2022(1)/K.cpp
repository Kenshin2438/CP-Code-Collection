#include <iostream>
#include <algorithm>
using namespace std;

using ll = long long;

const int mod = 1e9 + 7;

void solve() {
  int n, m; cin >> n >> m;

  cout << (n - m) * 1LL * (mod - mod / 2) % mod << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(false);

  int T; cin >> T;
  while (T--) solve();

  return 0;
}