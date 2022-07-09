#include "../main.hpp"

template <int mod>
struct m32 {
  int v = 0;
  mutable int iv = 0;

  template <typename T>
  int norm(T v) {
    return (v %= mod) < 0 ? (mod + v) : v;
  }

  m32() = default;
  template <typename T> m32(T _ = 0) { v = norm(_); }
  ~m32() = default;

  m32 operator-() const { return v ? m32(mod - v) : m32(0); }
  m32 &operator=(const int &m) { return v = norm(m), *this; }
  m32 &operator+=(const m32 &m) {
    v = (v += m.v) >= mod ? v - mod : v;
    return *this;
  }
  m32 &operator-=(const m32 &m) {
    v = (v -= m.v) < 0 ? v + mod : v;
    return *this;
  }
  m32 &operator*=(const m32 &m) {
    v = norm(v * 1LL * m.v);
    return *this;
  }
  m32 &operator/=(const m32 &m) {
    v = norm(v * 1LL * m.inv());
    return *this;
  }
  m32 operator+(const m32 &m) const { return m32(*this) += m; }
  m32 operator-(const m32 &m) const { return m32(*this) -= m; }
  m32 operator*(const m32 &m) const { return m32(*this) *= m; }
  m32 operator/(const m32 &m) const { return m32(*this) /= m; }
  bool operator==(const m32 &m) const { return m.v == v; }
  bool operator!=(const m32 &m) const { return m.v != v; }
  m32 pow(long long n) const {
    if (n < 0) return inv().pow(-n);
    if (n == 1) return *this;
    if (n == 0) return m32(1);
    if (v == 0) return m32(0);
    m32 res = pow(n >> 1);
    return res * res * pow(n % 2);
  }
  m32 inv() const {
    assert(v != 0);
    m32 res(iv);  // check current inv
    if (res * v == 1) return res;
    return m32(iv = pow(mod - 2).v);
  }
  pair<m32, m32> sqrt() const {
#ifdef CIPOLLA
    return cipolla(v);
#else
    return {1, 1};
#endif
  }
  friend ostream &operator<<(ostream &os, const m32<mod> &m) {
    return os << m.v;
  }
  friend istream &operator>>(istream &is, m32<mod> &m) {
    is >> m.v;
    m.v = norm(m.v);
    return is;
  }
  friend string to_string(const m32 &m) { return to_string(m.v); }
};

const int mod = 998244353;
using mint = m32<mod>;