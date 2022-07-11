#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  ll a, b, x;
  cin >> a >> b >> x;

  for (ll pa = 0; pa * a <= x; pa++) {
    ll y = x - pa * a;
    if (y % b == 0) {
      cout << pa << ' ' << y / b << '\n';

      return 0;
    }
  }
  cout << -1;
  return 0;
}