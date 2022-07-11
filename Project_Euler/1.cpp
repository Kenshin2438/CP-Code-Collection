#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n = 1000;
  ll ans = 0;
  for (int i = 0; i < n; i++) {
    if (i % 3 == 0 || i % 5 == 0) {
      ans += i;
    }
  }
  cout << ans << '\n';
  return 0;
}