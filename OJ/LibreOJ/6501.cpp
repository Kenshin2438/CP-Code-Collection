#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

const int mod = 998244353;
const int N = 1e5 + 10;

int pw[N], fac[N], inv[N];
void init() {
  fac[0] = fac[1] = inv[0] = inv[1] = 1;
  for (int i = 2; i < N; i++) {
    fac[i] = fac[i - 1] * 1LL * i % mod;
    inv[i] = inv[mod % i] * 1LL * (mod - mod / i) % mod;
  }
  pw[0] = 1;
  for (int i = 1; i < N; i++) {
    pw[i] = (pw[i - 1] << 1) % mod;
    inv[i] = inv[i] * 1LL * inv[i - 1] % mod;
  }
} 

int C(int n, int m) {
  if (n < m) return 0;
  return fac[n] * 1LL * inv[m] % mod * inv[n - m] % mod;
}

void solve() {
  int n, m; cin >> n >> m;
  cout << 1LL * pw[n - m] * C(n, m) % mod << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  init();
  int T; cin >> T;
  while (T--) solve();
  return 0;
}