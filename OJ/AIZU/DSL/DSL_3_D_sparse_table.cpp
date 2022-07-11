#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

#define PII pair<int, int>
#define vec vector
#define str string
#define fi first
#define se second
#define all(a) a.begin(), a.end()

using db = double;
using ll = long long;

template<typename T, T (*f)(T, T)> struct ST {
#define sz(x) static_cast<int>((x).size())
  vec<vec<T>> st;
  ST(const vec<T> &v) : st(1, v) {
    for (int pw = 1, k = 1; (pw << 1) <= sz(v); pw <<= 1, k++) {
      st.emplace_back(sz(v) - (pw << 1) + 1);
      for (int i = 0; i < sz(st[k]); i++) {
        st[k][i] = f(st[k - 1][i], st[k - 1][i + pw]);
      }
    }
  }
  T query(int l, int r) { // query [l, r)
    int dep = 31 - __builtin_clz(r - l);
    return f(st[dep][l], st[dep][r - (1 << dep)]);
  }
};

template<typename T> T Min(T a, T b) { return min<T>(a, b); }

void SingleTest(int TestCase) {
  int n, L; cin >> n >> L;
  vec<int> a(n);
  for (auto &x : a) cin >> x;
  ST<int, Min<int>> st(a);
  for (int i = 0; i + L <= n; i++) {
    cout << st.query(i, i + L) << " \n"[i + L == n];
  }
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  // cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
