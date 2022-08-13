#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

struct StirlingNumber {
  const int P; // P is a small prime

  vector<vector<int>> C, S1, S2;

  StirlingNumber(int _P = 1) : P(_P) {
    C.assign(P + 1, {}), S1 = S2 = C;
    for (int i = 0; i <= P; i++) {
      C[i].assign(P + 1, 0), S1[i] = S2[i] = C[i];
      C[i][0] = C[i][i] = S1[i][i] = S2[i][i] = 1;
      for (int j = 1; j < i; j++) {
        C[i][j]  = (C[i - 1][j] + C[i - 1][j - 1]) % P;
        S2[i][j] = (S2[i - 1][j] * j + S2[i - 1][j - 1]) % P;
        S1[i][j] = (S1[i - 1][j] * (i - 1) + S1[i - 1][j - 1]) % P;
      }
    }
    // assert(false);
  }

  int getC(ll n, ll k) const {
    int res = 1;
    for (; n; n /= P, k /= P) {
      res = res * C[n % P][k % P] % P;
    }
    return res;
  }
  int getS1(ll n, ll k, bool sgn = false) const {
    if (n == 0 || k == 0) return int(n == k);
    ll n1 = n / P, n0 = n % P;
    ll j = (k - n1 - (n0 ? 1 : 0)) / (P - 1);
    ll i = k - n1 - j * (P - 1);
    int res = S1[n0][i] * getC(n1, j) % P;
    if ((n1 - j) & 1) res = P - res;
    if (sgn && ((n - k) & 1)) res = P - res;
    return res % P;
  }
  int getS2(ll n, ll k) const {
    ll k1 = k / P, k0 = k % P;
    ll j = n / P;
    ll i = n - k1 - j * (P - 1);
    int res = S2[i][k0] * getC(j, k1) % P;
    return res;
  }
};

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int q, P; cin >> q >> P;
  StirlingNumber sol(P);
  for (ll n, k; q--;) {
    cin >> n >> k;
    // cout << sol.getS1(n, k, true) << '\n';
    cout << sol.getS2(n, k) << '\n';
  }

  return 0;
}
