template <typename T>
struct Combination {
  int N{1};
  std::vector<T> facs, ifacs, invs;

  inline void extend() {
    int M = N << 1;
    facs.resize(M), ifacs.resize(M), invs.resize(M);
    for (int i = N; i < M; i++) facs[i] = facs[i - 1] * i;
    ifacs[M - 1] = T(1) / facs[M - 1];
    invs[M - 1]  = facs[M - 2] * ifacs[M - 1];
    for (int i = M - 2; i >= N; i--) {
      ifacs[i] = ifacs[i + 1] * (i + 1);
      invs[i]  = ifacs[i] * facs[i - 1];
    }
    N = M;
  }

  Combination(int MAX = 0) : facs(1, T(1)), ifacs(1, T(1)), invs(1, T(1)) {
    while (N <= MAX) extend();
  }

  auto fac(int i) -> T {
    assert(i >= 0);
    while (N <= i) extend();
    return facs[i];
  }
  auto ifac(int i) -> T {
    assert(i >= 0);
    while (N <= i) extend();
    return ifacs[i];
  }
  auto inv(int i) -> T {
    assert(i >= 0);
    while (N <= i) extend();
    return invs[i];
  }

  auto C(int n, int r) -> T {
    if (n < 0 || n < r || r < 0) return T(0);
    return fac(n) * ifac(r) * ifac(n - r);
  }
  auto P(int n, int r) -> T {
    if (n < 0 || n < r || r < 0) return T(0);
    return fac(n) * ifac(n - r);
  }
  auto S2(int n, int k) -> T {
    T res(0);
    for (int i = 0; i <= k; i++) {
      T t = T(k - i).pow(n) * C(k, i);
      (i & 1) ? res -= t : res += t;
    }
    return res * ifac(k);
  }
  auto B(int n, int k) -> T {  // sum_{i=0}^{k} S2(n, i)
    static std::vector<T> sum = {1};
    for (static int i = 1; i <= k; i++) {
      sum.push_back(sum.back() + (i & 1 ? -ifac(i) : ifac(i)));
    }
    T res(0);
    for (int i = 1; i <= k; i++) {
      res += sum[k - i] * T(i).pow(n) * ifac(i);
    }
    return res;
  }
};
Combination<mint> comb;