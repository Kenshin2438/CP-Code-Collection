#include "../main.hpp"

template <typename T, T (*f)(T, T)>
struct ST {
  vector<vector<T>> st;

  ST() = default;
  ST(const vector<T> &v) : st(1, v) {
#define sz(x) static_cast<int>((x).size())
    for (int pw = 1, k = 1; (pw << 1) <= sz(v); pw <<= 1, k++) {
      st.emplace_back(sz(v) - (pw << 1) + 1);
      for (int i = 0; i < sz(st[k]); i++) {
        st[k][i] = f(st[k - 1][i], st[k - 1][i + pw]);
      }
    }
#undef sz
  }
  ~ST() = default;

  T query(int l, int r) {  // query [l, r)
    int dep = 31 - __builtin_clz(r - l);
    return f(st[dep][l], st[dep][r - (1 << dep)]);
  }
};

template <typename T>
T Min(T a, T b) {
  return min<T>(a, b);
}
