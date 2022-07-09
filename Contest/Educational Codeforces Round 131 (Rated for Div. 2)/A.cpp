#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

void solve() {
  vector<int> a(4);
  for (int &x : a) cin >> x;

  int cnt = count(all(a), 1);
  if (cnt == 0) {
    cout << 0 << '\n';
  } else if (cnt == 1 || cnt == 2 || cnt == 3) {
    cout << 1 << '\n';
  } else {
    cout << 2 << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T = 1;
  cin >> T;
  while (T--) solve();
  return 0;
}