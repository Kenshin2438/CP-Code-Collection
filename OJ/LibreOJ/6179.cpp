#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

const int mod = 998244353;
const int N = (int) 1e5 + 10;
const int M = 40;

int phi[N], mu[N], inv[N], G[N];
vector<int> S[N], F[M][M];

void init() {
  phi[1] = mu[1] = 1;
  vector<int> p;
  for (int i = 2; i < N; i++) {
    if (phi[i] == 0) {
      p.push_back(i);
      phi[i] = i - 1, mu[i] = mod - 1;
    }
    for (const int &pr : p) {
      if (pr * 1LL * i >= N) break;
      if (i % pr == 0) {
        phi[pr * i] = phi[i] * pr;
        mu[pr * i] = 0;
        break;
      } else {
        phi[pr * i] = phi[i] * (pr - 1);
        mu[pr * i] = mod - mu[i];
      }
    }
  }
  
  inv[0] = inv[1] = 1;
  for (int i = 2; i < N; i++) {
    inv[i] = 1LL * (mod - mod / i) * inv[mod % i] % mod;
  }

  for (int d = 1; d < N; d++) {
    for (int T = d; T < N; T += d) {
      G[T] = (G[T] + inv[ phi[d] ] * 1LL * d % mod * mu[T / d] % mod) % mod;
    }
  }

  for (int T = 1; T < N; T++) {
    S[T].emplace_back(0);
    for (int iT = T; iT < N; iT += T) {
      S[T].emplace_back( (S[T].back() + phi[iT]) % mod );
    }
  }

  for (int i = 1; i < M; i++) {
    for (int j = 1; j < M; j++) {
      F[i][j].emplace_back(0);
      for (int k = 1; k * max(i, j) < N; k++) {
        F[i][j].emplace_back(
          (F[i][j].back() + G[k] * 1LL * S[k][i] % mod * S[k][j] % mod) % mod
        );
      }
    }
  }
}

void solve() {
  int n, m; cin >> n >> m;
  ll ans = 0LL;

  if (n < m) swap(n, m); // n > m
  for (int T = 1; T <= n / M; T++) {
    ans = (ans + G[T] * 1LL * S[T][n / T] % mod * S[T][m / T] % mod) % mod;
  }
  for (int l = n / M + 1, r; l <= m; l = r + 1) {
    int bn = n / l, bm = m / l;
    r = min(n / bn, m / bm);
    ans = (ans + F[bn][bm][r] - F[bn][bm][l - 1] + mod) % mod;
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