#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  ll ans = 1;
  for (ll i = 1; i <= 20; i++) {
    if (ans % i == 0) continue;
    ans = ans / gcd(i, ans) * i;
  }
  cout << ans << '\n';
  return 0;
}