template <typename T, typename E, class F, class G, class H>
struct LazySegmentTree {
 private:
  int N, _log;
  std::vector<T> dat;
  std::vector<E> laz;
  const F f;
  const G g;
  const H h;
  const T ti;
  const E ei;
  auto init(int n) -> void {
    N = 1, _log = 0;
    while (N < n) N <<= 1, _log++;
    dat.assign(N << 1, ti);
    laz.assign(N << 1, ei);
  }
  auto build(const std::vector<T> &v) -> void {
    int n = (int)v.size();
    init(n);
    for (int i = 0; i < n; i++) dat[i + N] = v[i];
    for (int i = N - 1; i > 0; i--) {
      dat[i] = f(dat[i << 1 | 0], dat[i << 1 | 1]);
    }
  }

  inline auto reflect(int t) const -> T {
    return laz[t] == ei ? dat[t] : g(dat[t], laz[t]);
  }
  inline auto push(int t) -> void {
    if (laz[t] == ei) return;
    laz[t << 1 | 0] = h(laz[t << 1 | 0], laz[t]);
    laz[t << 1 | 1] = h(laz[t << 1 | 1], laz[t]);
    dat[t] = g(dat[t], laz[t]);
    laz[t] = ei;
  }
  inline auto thrust(int t) -> void {
    for (int i = _log; i > 0; i--) push(t >> i);
  }
  inline auto recalc(int t) -> void {
    while (t >>= 1) dat[t] = f(reflect(t << 1 | 0), reflect(t << 1 | 1));
  }

 public:
  LazySegmentTree(int n, F _f, G _g, H _h, T _ti, E _ei)
      : f(_f), g(_g), h(_h), ti(_ti), ei(_ei) {
    init(n);
  }
  LazySegmentTree(const std::vector<T> &v, F _f, G _g, H _h, T _ti, E _ei)
      : f(_f), g(_g), h(_h), ti(_ti), ei(_ei) {
    build(v);
  }

  auto set(int p, const T &val) -> void {
    thrust(p += N);
    dat[p] = val;
    laz[p] = ei;
    recalc(p);
  }
  auto get(int p) -> T {
    thrust(p += N);
    return reflect(p);
  }
  auto update(int l, int r, const E &dif) -> void {  // [l, r)
    if (l >= r) return;
    l += N, r += N;
    thrust(l), thrust(r - 1);
    for (int a = l, b = r; a < b; a >>= 1, b >>= 1) {
      if (a & 1) laz[a] = h(laz[a], dif), a++;
      if (b & 1) --b, laz[b] = h(laz[b], dif);
    }
    recalc(l), recalc(r - 1);
  }
  auto query(int l, int r) -> T {  // [l, r)
    if (l >= r) return ti;
    l += N, r += N;
    thrust(l), thrust(r - 1);
    T L = ti, R = ti;
    for (int a = l, b = r; a < b; a >>= 1, b >>= 1) {
      if (a & 1) L = f(L, reflect(a++));
      if (b & 1) R = f(reflect(--b), R);
    }
    return f(L, R);
  }
};