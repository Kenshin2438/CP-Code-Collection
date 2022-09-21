template <typename T> struct Combination {
  int n; vector<T> facs, ifacs, invs;

  inline void extend() {
    int m = n << 1;
    facs.resize(m), ifacs.resize(m), invs.resize(m);
    for (int i = n; i < m; i++) facs[i] = facs[i - 1] * i;
    ifacs[m - 1] = T(1) / facs[m - 1];
    invs[m - 1] = facs[m - 2] * ifacs[m - 1];
    for (int i = m - 2; i >= n; i--) {
      ifacs[i]= ifacs[i + 1] * (i + 1);
      invs[i] = ifacs[i] * facs[i - 1];
    }
    n = m;
  }

  Combination(int MAX = 0)
      : n(1), facs(1, T(1)), ifacs(1, T(1)), invs(1, T(1)) {
    while (n <= MAX) extend();
  }

  T fac(int i) {
    assert(i >= 0);
    while (n <= i) extend();
    return facs[i];
  }
  T ifac(int i) {
    assert(i >= 0);
    while (n <= i) extend();
    return ifacs[i];
  }
  T inv(int i) {
    assert(i >= 0);
    while (n <= i) extend();
    return invs[i];
  }

  T C(int n, int r) const {
    if (n < 0 || n < r || r < 0) return T(0);
    return fac(n) * ifac(r) * ifac(n - r);
  }
  T P(int n, int r) const {
    if (n < 0 || n < r || r < 0) return T(0);
    return fac(n) * ifac(n - r);
  }
  T S2(int n, int k) const { 
    T res(0); // O(k log n)
    for (int i = 0; i <= k; i++) {
      T t = T(k - i).pow(n) * C(k, i);
      (i & 1) ? res -= t : res += t;
    }
    return res * ifac(k);
  }
  T B(int n, int k) { // sum_{i=0}^{k} S2(n, i)
    static vector<T> sum = { 1 };
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