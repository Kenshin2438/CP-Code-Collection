#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

void solve() {
  int n, x; cin >> n >> x;
  vector<int> a(n * 2);
  for (int &ax : a) cin >> ax;

  bool ans = true;

  sort(all(a));
  for (int i = 0; i < n; i++) {
    if (a[i + n] - a[i] < x) ans = false;
  }
  cout << (ans ? "Yes" : "No") << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T; cin >> T;
  while (T--) solve();

  return 0;
}