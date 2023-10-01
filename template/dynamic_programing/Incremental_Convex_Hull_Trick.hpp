template <typename T>
struct CHTLine {
  bool isQuery;
  T k, b;  // line: y = k * x + b

  constexpr explicit CHTLine(const T &_k, const T &_b)
      : isQuery(false), k(_k), b(_b), x(T()) {}
  constexpr explicit CHTLine(const T &_x)
      : isQuery(true), k(T()), b(T()), x(_x) {}

  constexpr auto eval(const T &val) const -> T { return k * val + b; }
};

template <typename T>
using FUN = std::function<bool(const CHTLine<T> &, const CHTLine<T> &)>;

template <typename T, class CMP = std::less<T>>
struct IncrementalConvexHullTrick : public std::multiset<CHTLine<T>, FUN<T>> {
  using MS = std::multiset<CHTLine<T>, FUN<T>>;
  using iter = typename MS::iterator;

  static constexpr T INF = std::numeric_limits<T>::max();
  static constexpr CMP cmp = CMP();
  static constexpr auto equals(const T &a, const T &b) -> bool {
    return !cmp(a, b) and !cmp(b, a);
  }
  static constexpr auto makeFUN() -> FUN<T> {
    return [=](const CHTLine<T> &a, const CHTLine<T> &b) {
      return a.isQuery or b.isQuery ? a.x < b.x : cmp(a.k, b.k);
    };
  }
  constexpr IncrementalConvexHullTrick() : MS(makeFUN()) {}

  [[nodiscard]] constexpr auto div(const T &a, const T &b) const -> T {
    if constexpr (std::is_integral<T>::value) {
      return a / b - static_cast<T>((a < T()) != (b < T()) and cmp(T(), a % b));
    } else if (std::is_floating_point<T>::value) {
      return a / b;
    }
  }
  constexpr auto intersect(iter la, iter lb) -> bool {
    if (lb == MS::end()) {
      la->x = INF;
      return false;
    }
    if (equals(la->k, lb->k)) {
      la->x = cmp(lb->b, la->b) ? INF : -INF;
    } else {
      la->x = div(lb->b - la->b, la->k - lb->k);
    }
    return la->x >= lb->x;
  }
  constexpr auto addLine(const T &k, const T &b) {
    auto z = MS::emplace(k, b), y = z++, x = y;
    while (intersect(y, z)) z = MS::erase(z);
    if (x != MS::begin() && intersect(--x, y)) intersect(x, y = MS::erase(y));
    while ((y = x) != MS::begin() && (--x)->x >= y->x) {
      intersect(x, MS::erase(y));
    }
  }
  [[nodiscard]] constexpr auto eval(const T &x) const -> T {
    return MS::lower_bound(CHTLine<T>(x))->eval(x);
  }
};