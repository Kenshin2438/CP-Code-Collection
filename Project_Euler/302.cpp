#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  long long n = 1e18, S = 1e6;

  vector<int> p, lpf(S, 0);
  for (int i = 2; i < S; i++) {
    if (lpf[i] == 0) {
      lpf[i] = i;
      p.emplace_back(i);
    }
    for (const int &pr : p) {
      if (pr * 1LL * i >= S) break;
      lpf[pr * 1LL * i] = pr;
      if (i % pr == 0) break;
    }
  }
  vector<vector<int>> fac(S);
  for (const int &pr : p) {
    int x = pr - 1;
    while (x != 1) {
      x /= lpf[x];
      if (not fac[pr - 1].empty() && ) {

      }
      fac[pr - 1].emplace_back(lpf[x]);
    }
  }
  vector<vector<int>> gcd(65, vector<int>(65, 0));
  for (int i = 0; i <= 64; i++) {
    gcd[i][i] = i; 
    for (int j = i + 1; j <= 64; j++) {
      gcd[i][j] = gcd[j][i] = __gcd(i, j);
    }
  }

  ll ans = 0LL;
  const auto check = [&](long long x) -> bool {
    int e = 0;
  };
  const function<void ()> f = 
      [&](int idx, ll x) {
    
  };
  cout << ans << '\n';
  return 0;
}