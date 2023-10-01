#include <bits/stdc++.h>

#if defined(KENSHIN)
  #define DBG_MACRO_NO_WARNING
  #include "dbg/dbg.h"
#else
  #define dbg(...) (__VA_ARGS__)
#endif

using i64 = int64_t;

namespace geometry {
using ld = long double;

constexpr ld EPS = 1e-8L;

auto sgn(ld val) -> int { return val < -EPS ? -1 : val > EPS ? +1 : 0; }
auto equals(ld a, ld b) -> bool { return sgn(a - b) == 0; }

struct Point {
  ld x, y;

  Point() = default;
  explicit Point(const ld& _x, const ld& _y) : x(_x), y(_y) {}

  auto operator-() const -> Point { return Point(-x, -y); }
  auto operator+=(const Point& p) -> Point& {
    x += p.x, y += p.y;
    return *this;
  }
  auto operator-=(const Point& p) -> Point& {
    x -= p.x, y -= p.y;
    return *this;
  }
  auto operator*=(const ld& k) -> Point& {
    x *= k, y *= k;
    return *this;
  }
  auto operator/=(const ld& k) -> Point& {
    x /= k, y /= k;
    return *this;
  }

  auto operator+(const Point& p) const -> Point { return Point(*this) += p; }
  auto operator-(const Point& p) const -> Point { return Point(*this) -= p; }
  auto operator*(const ld& k) const -> Point { return Point(*this) *= k; }
  auto operator/(const ld& k) const -> Point { return Point(*this) /= k; }

  auto operator*(const Point& p) const -> Point {
    return Point(x * p.x - y * p.y, x * p.y + y * p.x);
  }

  auto operator==(const Point& p) const -> bool {
    return equals(x, p.x) && equals(y, p.y);
  }

  friend auto operator>>(std::istream& is, Point& _p) -> std::istream& {
    return is >> _p.x >> _p.y;
  }
  friend auto operator<<(std::ostream& os, const Point& p) -> std::ostream& {
    return os << p.x << " " << p.y;
  }

  [[nodiscard]] auto norm() const -> ld { return x * x + y * y; }
  [[nodiscard]] auto abs() const -> ld { return std::hypot(x, y); }
  [[nodiscard]] auto arg() const -> ld { return std::atan2(y, x); }

  [[nodiscard]] auto conj() const -> Point { return Point(x, -y); }
  [[nodiscard]] auto unit() const -> Point { return Point(*this) /= abs(); }
  [[nodiscard]] auto normal() const -> Point { return Point(-y, x); }
};
using Vector = Point;

auto polar(const ld& r, const ld& theta) -> Vector {
  return Vector(std::cos(theta), std::sin(theta)) * r;
}
auto norm(const Vector& a) -> ld { return a.norm(); }
auto abs(const Vector& a) -> ld { return a.abs(); }
auto arg(const Vector& a) -> ld { return a.arg(); }

auto dot(const Vector& a, const Vector& b) -> ld {
  return a.x * b.x + a.y * b.y;
}
auto cross(const Vector& a, const Vector& b) -> ld {
  return a.x * b.y - a.y * b.x;
}
auto distance(const Vector& a, const Vector& b) -> ld { return abs(b - a); }

struct Line {
  Point s, t;

  Line() = default;
  explicit Line(const Point& _s, const Point& _t) : s(_s), t(_t) {}

  friend auto operator>>(std::istream& is, Line& l) -> std::istream& {
    return is >> l.s >> l.t;
  }
  friend auto operator<<(std::ostream& os, const Line& l) -> std::ostream& {
    return os << l.s << " to " << l.t;
  }

  [[nodiscard]] auto direction() const -> Vector { return t - s; }
};

struct Segment : Line {
  using Line::Line;

  Segment() = default;
  explicit Segment(const Point& _s, const Point& _t) : Line(_s, _t) {}
  explicit Segment(const Line& _l) : Line(_l) {}

  [[nodiscard]] auto length() const -> ld { return direction().abs(); }
};

auto length(const Segment& seg) -> ld { return seg.length(); }

auto project(const Point& p, const Line& l) -> Point {
  Vector v = l.direction().unit();
  return l.s + v * dot(p - l.s, v);
}
auto reflect(const Point& p, const Line& l) -> Point {
  Point mid = project(p, l);
  return mid * 2 - p;
}

enum Position {
  COUNTER_CLOCKWISE = -1,
  CLOCKWISE = +1,
  ONLINE_BACK = -2,
  ONLINE_FRONT = +2,
  ON_SEGMENT = 0
};
auto ccw(const Point& p, const Segment& seg) -> Position {
  Vector vd = seg.direction();
  Vector vp = p - seg.s;
  int sgnA = sgn(cross(vd, vp));
  if (sgnA == +1) return COUNTER_CLOCKWISE;
  if (sgnA == -1) return CLOCKWISE;
  if (sgn(dot(vd, vp)) == -1) return ONLINE_BACK;
  if (sgn(norm(vd) - norm(vp)) == -1) {
    return ONLINE_FRONT;
  }
  return ON_SEGMENT;
}

auto parallel(const Line& la, const Line& lb) -> bool {
  return sgn(cross(la.direction(), lb.direction())) == 0;
}
auto orthogonal(const Line& la, const Line& lb) -> bool {
  return sgn(dot(la.direction(), lb.direction())) == 0;
}

auto intersect(const Point& p, const Segment& seg) -> bool {
  return ccw(p, seg) == ON_SEGMENT;
}
auto intersect(const Point& p, const Line& l) -> bool {
  auto status = ccw(p, Segment(l));
  return status == ONLINE_BACK or status == ONLINE_FRONT or
         status == ON_SEGMENT;
  // return abs(status) != 1;
}
auto intersect(const Segment& sa, const Segment& sb) -> bool {
  auto statusSa = ccw(sa.s, sb);
  auto statusTa = ccw(sa.t, sb);
  if (statusSa == ON_SEGMENT or statusTa == ON_SEGMENT) return true;

  auto statusSb = ccw(sb.s, sa);
  auto statusTb = ccw(sb.t, sa);
  if (statusSb == ON_SEGMENT or statusTb == ON_SEGMENT) return true;

  return ((statusSa == COUNTER_CLOCKWISE and statusTa == CLOCKWISE) or
          (statusSa == CLOCKWISE and statusTa == COUNTER_CLOCKWISE)) and
         ((statusSb == COUNTER_CLOCKWISE and statusTb == CLOCKWISE) or
          (statusSb == CLOCKWISE and statusTb == COUNTER_CLOCKWISE));
  // return statusSa * statusTa <= 0 and statusSb * statusTb <= 0;
}
auto intersect(const Segment& seg, const Line& l) -> bool {
  Vector vd = l.direction();
  Vector vs = seg.s - l.s;
  Vector vt = seg.t - l.s;
  return sgn(cross(vd, vs)) * sgn(cross(vd, vt)) <= 0;
}
auto intersect(const Line& la, const Line& lb) -> bool {
  bool isParallel = parallel(la, lb);
  if (!isParallel) return true;
  return sgn(cross(la.direction(), la.s - lb.s)) == 0;
}

auto crosspoint(const Line& la, const Line& lb) -> Point {
  assert(intersect(la, lb));
  ld A = cross(la.direction(), lb.direction());
  ld B = cross(la.direction(), la.t - lb.s);
  if (sgn(A) == 0 && sgn(B) == 0) return lb.s;
  return lb.s + lb.direction() * B / A;
}

auto distance(const Point& p, const Segment& seg) -> ld {
  Point h = project(p, seg);
  if (intersect(h, seg)) return distance(p, h);
  return std::min(distance(p, seg.s), distance(p, seg.t));
}
auto distance(const Point& p, const Line& l) -> ld {
  return distance(p, project(p, l));
}
auto distance(const Segment& sa, const Segment& sb) -> ld {
  if (intersect(sa, sb)) return static_cast<ld>(0);
  return std::min({distance(sa.s, sb), distance(sa.t, sb), distance(sb.s, sa),
                   distance(sb.t, sa)});
}
auto distance(const Segment& seg, const Line& l) -> ld {
  if (intersect(seg, l)) return static_cast<ld>(0);
  return std::min(distance(seg.s, l), distance(seg.t, l));
}
auto distance(const Line& la, const Line& lb) -> ld {
  if (intersect(la, lb)) return static_cast<ld>(0);
  return distance(la.s, lb);
}

// sort the points in COUNTER_CLOCKWISE order
// that starts from the half line(x <= 0, y = 0)
void polarSort(std::vector<Point>& PS) {
  const auto part = [](const Point& p) {
    const int sgnX = sgn(p.x);
    const int sgnY = sgn(p.y);
    if (sgnY < 0) return 0;                 // (-pi, 0)
    if (sgnY == 0 and sgnX >= 0) return 1;  // 0
    if (sgnY > 0) return 2;                 // (0, +pi)
    if (sgnY == 0 and sgnX < 0) return 3;   // pi
    assert(false);
  };
  sort(begin(PS), end(PS), [&](const Point& a, const Point& b) {
    return part(a) == part(b) ? sgn(cross(a, b)) > 0 : part(a) < part(b);
  });
}

struct Polygon : std::vector<Point> {
  // points are given in the order of COUNTER_CLOCKWISE
  using std::vector<Point>::vector;

  Polygon() = default;
  explicit Polygon(const std::vector<Point>& PointSet)
      : std::vector<Point>(PointSet) {}

  [[nodiscard]] auto area() const -> ld {
    ld res = 0;
    for (size_t i = 0; i < size(); i++) {
      res += cross(at(i), at((i + 1) % size()));
    }
    return res / 2;
  }
  [[nodiscard]] auto isConvex(bool acceptOnSegment = true) const -> bool {
    auto n = size();
    if (n <= 2) return true;

    for (size_t i = 0; i < n; i++) {
      auto status = ccw(at((i + 2) % n), Segment(at(i), at((i + 1) % n)));
      if (acceptOnSegment ? status == CLOCKWISE : status != COUNTER_CLOCKWISE) {
        return false;
      }
    }
    return true;
  }
  [[nodiscard]] auto segments() const -> vector<Segment> {
    std::vector<Segment> res;
    for (size_t i = 0; i < size(); i++) {
      res.emplace_back(at(i), at((i + 1) % size()));
    }
    return res;
  }
};

auto area(const Polygon& poly) -> ld { return poly.area(); }
auto isConvex(const Polygon& poly, bool acceptOnSegment = true) -> bool {
  return poly.isConvex(acceptOnSegment);
}

enum Contain { OUTSIDE = 0, ON_EDGE = 1, INSIDE = 2 };
// Jordan curve theorem
auto containment(const Point& p, const Polygon& poly) -> Contain {
  auto n = poly.size();
  if (n == 0) return OUTSIDE;
  if (n == 1) return p == poly[0] ? ON_EDGE : OUTSIDE;

  bool inside = false;
  for (size_t i = 0; i < n; i++) {
    if (ccw(p, Segment(poly[i], poly[(i + 1) % n])) == ON_SEGMENT) {
      return ON_EDGE;
    }
    Point pa = poly[i] - p;
    Point pb = poly[(i + 1) % n] - p;
    if (pa.y > pb.y) std::swap(pa, pb);
    if (sgn(pa.y) <= 0 and sgn(pb.y) > 0 and sgn(cross(pa, pb)) < 0) {
      inside = !inside;
    }
  }
  return inside ? INSIDE : OUTSIDE;
}

auto convexHull(Polygon PS, bool acceptOnSegment = false) -> Polygon {
  if (PS.size() <= 2) return PS;

  sort(begin(PS), end(PS), [&](const Point& a, const Point& b) {
    return (equals(a.y, b.y) ? sgn(a.x - b.x) : sgn(a.y - b.y)) < 0;
  });  // starting from the y-minimum or the leftmost
  PS.erase(unique(begin(PS), end(PS)), end(PS));
  Polygon convex;
  const auto check = [&](const Point& p) {
    Segment seg(*prev(end(convex), 2), *prev(end(convex), 1));
    return acceptOnSegment ? ccw(p, seg) == CLOCKWISE
                           : ccw(p, seg) != COUNTER_CLOCKWISE;
  };
  for (const Point& p : PS) {
    while (convex.size() > 1 and check(p)) convex.pop_back();
    convex.emplace_back(p);
  }
  auto k = convex.size();
  PS.pop_back();
  reverse(begin(PS), end(PS));
  for (const Point& p : PS) {
    while (convex.size() > k and check(p)) convex.pop_back();
    convex.emplace_back(p);
  }
  convex.pop_back();
  return convex;
}

// Rotating Calipers [forked from: @shiomusubi]
auto convexDiameter(const Polygon& convex) -> ld {
  auto N = convex.size();
  if (N <= 1) return static_cast<ld>(0);
  if (N == 2) return distance(convex[0], convex[1]);
  assert(isConvex(convex));

  size_t P = 0, Q = 0;
  for (size_t K = 0; K < N; K++) {
    if (sgn(convex[K].y - convex[P].y) > 0) P = K;
    if (sgn(convex[K].y - convex[Q].y) < 0) Q = K;
  }
  const size_t sP = P, sQ = Q;

  ld diameter = distance(convex[P], convex[Q]);
  do {  // each Point can't be repeat more than once
    int sgnA = sgn(cross(convex[(P + 1) % N] - convex[P],
                         convex[(Q + 1) % N] - convex[Q]));
    if (sgnA < 0) {
      P = (P + 1) % N;
    } else {
      Q = (Q + 1) % N;
    }
    diameter = std::max(diameter, distance(convex[P], convex[Q]));
  } while (P != sP || Q != sQ);
  return diameter;
}

auto convexCut(const Polygon& convex, const Line& l) -> Polygon {
  assert(isConvex(convex));
  Polygon res;
  for (size_t i = 0; i < convex.size(); i++) {
    const Point& cur = convex[i];
    const Point& nxt = convex[(i + 1) % convex.size()];
    if (ccw(cur, Segment(l)) != CLOCKWISE) res.emplace_back(cur);
    if (intersect(Segment(cur, nxt), l)) {
      // TODO: cross point is cur/nxt
      res.emplace_back(crosspoint(Segment(cur, nxt), l));
    }
  }
  return res;
}

}  // namespace geometry

auto solve() -> void {}

auto main() -> int {
  std::ios_base::sync_with_stdio(false);
  std::cin.exceptions(std::cin.failbit);
  std::cin.tie(nullptr);

  std::cout << std::fixed << std::setprecision(15);

  int TestCase = 1;
  // std::cin >> TestCase;
  while (TestCase--) solve();

  return 0;
}