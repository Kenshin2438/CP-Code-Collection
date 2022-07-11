#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  ll a = 1, b = 2, ans = 2;
  while (b <= 4'000'000LL) {
    ll c = a + b;
    if (c % 2 == 0) ans += c;
    a = b, b = c;
  }
  cout << ans << '\n';
  return 0;
}