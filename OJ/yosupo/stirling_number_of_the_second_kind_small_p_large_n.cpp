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

  StirlingNumber(int _P = 2) : P(_P) {
    C.resize(P, vector<int>(P, 0)), S1 = S2 = C;
    for (int i = 0; i < P; i++) {
      C[i][0] = 1, C[i][i] = 1;
      for (int j = 1; j < i; j++) {
        C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
      }
    }
    for (int i = 0; i < P; i++) {
      S2[i][0] = 0, S2[i][i] = 1;
      for (int j = 1; j < i; j++) {
        S2[i][j] = (S2[i - 1][j] * j + S2[i - 1][j - 1]) % P;
      }
    }
    for (int i = 0; i < P; i++) {
      S1[i][0] = 0, S1[i][i] = 1;
      for (int j = 1; j < i; j++) {
        S1[i][j] = (S1[i - 1][j] * (P - i + 1) + S1[i - 1][j - 1]) % P;
      }
    }
  }

  int getC(ll n, ll k) const {
    if (k < 0 || k > n) return 0;
    int res = 1;
    for (; n; n /= P, k /= P) {
      res = res * C[n % P][k % P] % P;
    }
    return res;
  }
  int getS1(ll n, ll k) const {
    if (k < 0 || k > n) return 0;
    if (n == 0) return 1;
    ll n1 = n / P, n0 = n % P;
    if (k < n1) return 0;
    ll i = (k - n1) / (P - 1), j = (k - n1) % (P - 1);
    if (j == 0 && n0 == P - 1) j = P - 1, i -= 1;
    if (i < 0 || i > n1 || j > n0) return 0;
    int res = S1[n0][j] * getC(n1, i) % P;
    if ((n1 ^ i) & 1) res = (P - res) % P;
    return res;
  }
  int getS2(ll n, ll k) const {
    if (k < 0 || k > n) return 0;
    if (n == 0) return 1;
    ll k1 = k / P, k0 = k % P;
    if (n < k1) return 0;
    ll i = (n - k1) / (P - 1), j = (n - k1) % (P - 1);
    if (j == 0) j = P - 1, i -= 1;
    if (j == P - 1 && k0 == 0) return getC(i, k1 - 1);
    else return getC(i, k1) * S2[j][k0] % P;
  }
};

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int q, P; cin >> q >> P;
  StirlingNumber sol(P);
  for (ll n, k; q--;) {
    cin >> n >> k;
    cout << sol.getS2(n, k) << '\n';
  }

  return 0;
}
