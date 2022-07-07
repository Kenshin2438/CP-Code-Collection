#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

void solve() {
  int n; cin >> n;
  vector<int> a(n);
  int ans = 0;
  for (int &x : a) cin >> x;
  for (int i = 0; i < n; i++) {
    int ans = 0;
    for (int j = 0; j < n; j++) {
      if (i == j) continue;
      ans ^= a[j];
    }
    if (ans == a[i]) {
      cout << a[i] << '\n';
      return;
    }
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T; cin >> T;
  while (T--) solve();
  return 0;
}