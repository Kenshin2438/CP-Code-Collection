#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

template<typename T, size_t E>
struct Basis {
  vector<T> B;

  Basis() : B(E) {};
  void insert(T v) {
    for (int i = E - 1; i >= 0; i--) {
      if ((v >> i & 1) == 0) continue;
      if (B[i]) v ^= B[i];
      else return B[i] = v, void();
    }
  }
};

template<typename T, size_t E>
Basis<T, E> merge(const Basis<T, E> &a, const Basis<T, E> &b) {
  auto res = a;
  for (const T &x : b.B) res.insert(x);
  return res;
}

template <typename T, T (*ut)(), T (*f)(T, T)>
struct SegTree {
 private:
  int n, _log;
  vector<T> val;
  void _update(int t) { val[t] = f(val[t << 1 | 0], val[t << 1 | 1]); }

 public:
  SegTree() = default;
  SegTree(const vector<T> &v) {
    n = 1, _log = 0;
    while (n < (int)v.size()) n <<= 1, _log++;
    val.resize(n << 1, ut());
    for (int i = 0; i < (int)v.size(); i++) val[i + n] = v[i];
    for (int i = n - 1; i > 0; i--) _update(i);
  }
  ~SegTree() = default;

  void set(int p, const T &dif) {
    val[p += n] = dif;
    for (int i = 1; i <= _log; i++) _update(p >> i);
  }
  T get(int p) { return val[p + n]; }
  T query(int l, int r) {
    if (l == r) return ut();
    T L = ut(), R = ut();
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) L = f(L, val[l++]);
      if (r & 1) R = f(val[--r], R);
    }
    return f(L, R);
  }
};

namespace SegTreeUtil {  // Utilization
template <typename T>
T Merge(T a, T b) {
  return merge(a, b);
}
template <typename T>
T Init() {
  return T();
}
template <typename T>
struct Tree : SegTree<T, Init<T>, Merge<T>> {
  using base = SegTree<T, Init<T>, Merge<T>>;
  Tree() = default;
  Tree(const vector<T> &v) : base(v) {}
  ~Tree() = default;
};
}  // namespace SegTreeUtil
using SegTreeUtil::Tree;

template <typename T> struct FenwickTree {
  vector<T> s;
  FenwickTree(int n) : s(n) {}
  void update(int pos, T dif) {
    for (; pos < sz(s); pos |= pos + 1) s[pos] ^= dif;
  }
  T query(int pos) {
    T res = 0;
    for (; pos > 0; pos &= pos - 1) res ^= s[pos - 1];
    return res;
  }
};

void solve() {
  int n, q; cin >> n >> q;
  vector<int> a(n);
  for (int &x : a) cin >> x;
  adjacent_difference(all(a), begin(a), std::bit_xor<>());

  FenwickTree<int> ft(n);
  for (int i = 0; i < n; i++) {
    ft.update(i, a[i]);
  }

  vector<Basis<int, 30>> v(n);
  for (int i = 0; i < n; i++) v[i].insert(a[i]);
  Tree<Basis<int, 30>> seg(v);

  for (int op, l, r, x; q--; ) {
    cin >> op >> l >> r >> x, --l;
    if (op == 1) {
      if (l < n) {
        ft.update(l, x);
        Basis<int, 30> B;
        B.insert(a[l] ^= x);
        seg.set(l, B);
      }
      if (r < n) {
        ft.update(r, x);
        Basis<int, 30> B;
        B.insert(a[r] ^= x);
        seg.set(r, B);
      }
    } else {
      auto v = ft.query(l + 1);
      if (l + 1 == r) {
        cout << max(x, x ^ v) << '\n'; continue;
      }
      auto L = seg.query(l + 1, r);
      L.insert(v);
      for (int i = 30 - 1; i >= 0; i--) {
        int b = x >> i & 1;
        if (b == 0 && L.B[i] != 0) x ^= L.B[i];
      }
      cout << x << '\n';
    }
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
