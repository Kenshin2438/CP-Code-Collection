#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  ll k; 
  cin >> k;

  const int N = (int) 5e4;

  vector<ll> base(N + 1);
  for (int i = 1; i <= N; i++) {
    base[i] = base[i - 1] + i;
  }

  vector<int> ans(base.size());
  for (int i = N; i >= 1; i--) {
    ans[i] = k / base[i];
    k %= base[i];
  }
  for (int i = 1; i <= N; i++) {
    cout << "re";
    while (ans[i]--) cout << "d";
  }

  debug(base[N]);
  return 0;
}