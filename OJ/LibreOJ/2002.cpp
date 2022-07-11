#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

const int mod = 20170408;

struct Matrix {
  vector<vector<ll>> mat;

  Matrix(int n, bool one = true) { 
    mat.resize(n, vector<ll>(n, 0));
    for (int i = 0; i < n; i++) mat[i][i] = one;
  }
  Matrix operator*(const Matrix &o) const {
    int n = mat.size();
    Matrix res(n, false);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        for (int k = 0 ; k < n; k++) {
          res.mat[i][j] += mat[i][k] * o.mat[k][j] % mod;
          res.mat[i][j] %= mod;
        }
      }
    }
    return res;
  }
  Matrix pow(int n) {
    if (n == 0) return Matrix(mat.size());
    if (n == 1) return *this;
    auto s = pow(n >> 1);
    return s * s * pow(n & 1);
  } 
};

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, m, p; cin >> n >> m >> p;
  vector<int> A(p, 0), B(p, 0);

  vector<int> lpf(m + 1, 0), prime;
  for (int i = lpf[1] = 1; i <= m; i++) {
    A[i % p] += 1; 
    if (lpf[i] == 0) {
      prime.emplace_back(i);
      lpf[i] = i;
    } else B[i % p] += 1;
    for (const int &pr : prime) {
      if (pr * 1LL * i > m) break;
      lpf[pr * 1LL * i] = pr;
      if (i % pr == 0) break;
    }
  }

  ll ans = 0;
  {
    Matrix M(p, false);
    for (int j = 0; j < p; j++) {
      for (int i = 0; i < p; i++) {
        M.mat[i][j] = A[(j - i + p) % p];
      }
    }
    auto S = M.pow(n);
    ans += S.mat[0][0];
  }
  {
    Matrix M(p, false);
    for (int j = 0; j < p; j++) {
      for (int i = 0; i < p; i++) {
        M.mat[i][j] = B[(j - i + p) % p];
      }
    }
    auto S = M.pow(n);
    ans -= S.mat[0][0];
  }
  cout << (ans + mod) % mod << '\n';
  return 0;
}