#include <complex>
#include <vector>
#include <cmath>

using std::vector;
using std::complex;

using C = complex<double>;
void FFT(vector<C> &a) {
  int n = std::size(a), L = 31 - __builtin_clz(n);
  static vector<complex<long double>> R(2, 1);
  static vector<C> rt(2, 1);
  for (static int k = 2; k < n; k <<= 1) {
    R.resize(n), rt.resize(n);
    auto x = polar(1.0L, acos(-1.0L) / k);
    for (int i = k; i < 2 * k; i++) {
      rt[i] = R[i] = i & 1 ? R[i >> 1] * x : R[i >> 1];
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
        C z = rt[j + k] * a[i + j + k];
        a[i + j + k] = a[i + j] - z, a[i + j] += z;
      }
    }
  }
}

using i64 = long long int;
using Poly = vector<i64>;
template <int M>
Poly convMod(const Poly &a, const Poly &b) {
  if (a.empty() || b.empty()) return {};
  Poly res(std::size(a) + std::size(b) - 1);
  int B = 32 - __builtin_clz(std::ssize(res));
  int n = 1 << B, S = sqrt(M);
  vector<C> L(n), R(n), outs(n), outl(n);
  for (int i = 0; i < std::size(a); i++) {
    L[i] = C(int(a[i] / S), int(a[i] % S));
  }
  for (int i = 0; i < std::size(b); i++) {
    R[i] = C(int(b[i] / S), int(b[i] % S));
  }
  FFT(L), FFT(R);
  for (int i = 0; i < n; i++) {
    int j = (n - i) & (n - 1);
    outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
    outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
  }
  FFT(outl), FFT(outs);
  for (int i = 0; i < std::size(res); i++) {
    i64 A = i64(imag(outs[i]) + 0.5) % M;
    i64 B = (i64(imag(outl[i]) + 0.5) + i64(real(outs[i]) + 0.5)) % M * S % M;
    i64 C = i64(real(outl[i]) + 0.5) % M * (S * S % M) % M;
    res[i] = (A + B + C) % M;
  }
  return res;
}
