#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

const int N = 2e6 + 10;

int phi[N], mu[N];
ll F[N];

void init() {
  vector<int> p;

  phi[1] = mu[1] = 1;
  for (int i = 2; i < N; i++) {
    if (phi[i] == 0) {
      phi[i] = i - 1;
      mu[i] = -1;
      p.emplace_back(i);
    }
    for (const int &pr : p) {
      if (pr * 1LL * i >= N) break;
      if (i % pr == 0) {
        phi[pr * i] = phi[i] * pr;
        break;
      } else {
        phi[pr * i] = phi[i] * (pr - 1);
        mu[pr * i] = -mu[i];
      }
    }
  }
  for (int d = 1; d < N; d++) {
    for (int T = d; T < N; T += d) {
      F[T] += mu[d] * phi[T / d];
    }
  }
}

void solve() {
  int n; cin >> n;

  vector<ll> cnt(n + 1, 0);
  for (int i = 1; i <= n; i++) ++cnt[phi[i]];
  
  ll ans = 0LL;
  for (int T = 1; T <= n; T++) {
    ll C = 0;
    for (int i = T; i <= n; i += T) C += cnt[i];
    ans += C * C * F[T];
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  
  init();
  int T; cin >> T;
  while (T--) solve();

  return 0;
}