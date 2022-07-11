#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  ll N = 600851475143LL, ans = -1;
  for (ll x = 2; x * x <= N; x++) {
    while (N % x == 0) {
      ans = x;
      N /= x;
    }
  }
  if (N != 1LL) ans = N;
  cout << ans << '\n';
  return 0;
}