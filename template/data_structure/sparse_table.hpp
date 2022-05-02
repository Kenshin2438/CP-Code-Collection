#include "../main.hpp"

template <typename T, T (*f)(T, T)> struct ST {
  vec<vec<T>> st;

  ST() {}
  ST(const vec<T> &v) : st(1, v) {
    for (int pw = 1, k = 1; (pw << 1) <= SZ(v); pw <<= 1, k++) {
      st.emplace_back(SZ(v) - (pw << 1) + 1);
      for (int i = 0; i < SZ(st[k]); i++) {
        st[k][i] = f(st[k - 1][i], st[k - 1][i + pw]);
      }
    }
  }
  T query(int l, int r) {  // query [l, r)
    int dep = 31 - __builtin_clz(r - l);
    return f(st[dep][l], st[dep][r - (1 << dep)]);
  }
};

template <typename T> T Min(T a, T b) { return min<T>(a, b); }
