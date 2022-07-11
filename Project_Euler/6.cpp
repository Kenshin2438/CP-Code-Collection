#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  ll ans = 0;
  for (int i = 1; i <= 100; i++) {
    ans += i * i;
  }
  ans -= 5050 * 5050;
  cout << abs(ans) << '\n';
  return 0;
}