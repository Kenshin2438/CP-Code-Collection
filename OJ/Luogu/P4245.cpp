#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) int((x).size())

using C = complex<double>;
void FFT(vector<C>& a) {
  int n = sz(a), L = 31 - __builtin_clz(n);
  // static vector<complex<long double>> R(2, 1);
  static vector<C> rt(2, 1);
  static constexpr double PI = 3.14159265358979311599796;  
  for (static int k = 2; k < n; k <<= 1) {
    // R.resize(n);
    rt.resize(n);
    // auto x = polar(1.0L, acos(-1.0L) / k);
    auto x = polar(1.0, PI / k);
    for (int i = k; i < 2 * k; i++) {
      // rt[i] = R[i] = i & 1 ? R[i >> 1] * x : R[i >> 1];
      rt[i] = i & 1 ? rt[i >> 1] * x : rt[i >> 1];
    }
  }
  vector<int> rev(n);
  for (int i = 0; i < n; i++) {
    rev[i] = rev[i >> 1] >> 1 | (i & 1) << (L - 1);
  }
  for (int i = 0; i < n; i++) {
    if (i < rev[i]) swap(a[i], a[rev[i]]);
  }
  for (int k = 1; k < n; k <<= 1) {
    for (int i = 0; i < n; i += k * 2) {
      for (int j = 0; j < k; j++) {
        // C z = rt[j + k] * a[i + j + k];
        auto x = (double*)&rt[j + k], y = (double*)&a[i + j + k];
        C z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]);
        a[i + j + k] = a[i + j] - z, a[i + j] += z;
      }
    }
  }
}

using Poly = vector<int>;
// template <int M>
int M;  // mod;
Poly convMod(const Poly& a, const Poly& b) {
  if (a.empty() || b.empty()) return {};
  Poly res(sz(a) + sz(b) - 1);
  int B = 32 - __builtin_clz(sz(res));
  int n = 1 << B, S = sqrt(M);
  vector<C> L(n), R(n), outs(n), outl(n);
  for (int i = 0; i < sz(a); i++) {
    L[i] = C(a[i] >> 15, a[i] & 32767);
  }
  for (int i = 0; i < sz(b); i++) {
    R[i] = C(b[i] >> 15, b[i] & 32767);
  }
  FFT(L), FFT(R);
  for (int i = 0; i < n; i++) {
    int j = (n - i) & (n - 1);
    outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
    outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
  }
  FFT(outl), FFT(outs);
  for (int i = 0; i < sz(res); i++) {
    ll a0b0 = ll(outl[i].real() + 0.5);
    ll a0b1 = ll(outl[i].imag() + 0.5);
    ll a1b0 = ll(outs[i].real() + 0.5);
    ll a1b1 = ll(outs[i].imag() + 0.5);
    res[i] = ((a0b0 % M << 30) + ((a0b1 + a1b0) % M << 15) + a1b1) % M;
  }
  return res;
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, m;
  cin >> n >> m >> ::M;

  Poly F(n + 1), G(m + 1);
  for (int& x : F) cin >> x, x %= M;
  for (int& x : G) cin >> x, x %= M;
  auto ans = convMod(F, G);
  for (int& x : ans) cout << x << ' ';
  return 0;
}