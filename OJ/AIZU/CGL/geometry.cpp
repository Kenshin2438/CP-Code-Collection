#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <ctime>
#include <functional>
#include <iomanip>
#include <ios>
#include <iostream>
#include <memory>
#include <optional>
#include <queue>
#include <sstream>
#include <stack>
#include <string>
#include <tuple>
#include <type_traits>
#include <variant>
#include <vector>

using namespace std;

#ifdef KENSHIN
  #define DBG_MACRO_NO_WARNING
  #include <dbg.h>
#else
  #define dbg(...) (__VA_ARGS__)
#endif

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

namespace geometry {
using ld = long double;

constexpr ld EPS = 1e-8L;
constexpr ld PI  = 3.14159265358979323846L;

int sgn(ld val) { return val < -EPS ? -1 : val > EPS ? +1 : 0; }
bool equals(ld a, ld b) { return sgn(a - b) == 0; }

struct Point {
  ld x, y;
  Point(ld _x = ld(0), ld _y = ld(0)) : x(_x), y(_y) {}

  Point operator-() const { return Point(-x, -y); }
  Point& operator+=(const Point& p) {
    x += p.x, y += p.y;
    return *this;
  }
  Point& operator-=(const Point& p) {
    x -= p.x, y -= p.y;
    return *this;
  }
  Point& operator*=(const ld& k) {
    x *= k, y *= k;
    return *this;
  }
  Point& operator/=(const ld& k) {
    x /= k, y /= k;
    return *this;
  }

  Point operator+(const Point& p) const { return Point(*this) += p; }
  Point operator-(const Point& p) const { return Point(*this) -= p; }
  Point operator*(const ld& k) const { return Point(*this) *= k; }
  Point operator/(const ld& k) const { return Point(*this) /= k; }

  Point operator*(const Point& p) const {
    return Point(x * p.x - y * p.y, x * p.y + y * p.x);
  }

  bool operator==(const Point& p) const {
    return equals(x, p.x) && equals(y, p.y);
  }

  friend istream& operator>>(istream& is, Point& _p) {
    return is >> _p.x >> _p.y;
  }
  friend ostream& operator<<(ostream& os, const Point& p) {
    return os << p.x << " " << p.y;
  }

  ld norm() const { return x * x + y * y; }
  ld abs() const { return hypot(x, y); }
  ld arg() const { return atan2(y, x); }

  Point conj() const { return Point(x, -y); }
  Point unit() const { return Point(*this) /= abs(); }
  Point normal() const { return Point(-y, x); }
};
using Vector = Point;

Vector polar(const ld& r, const ld& theta) {
  return Vector(cos(theta), sin(theta)) * r;
}
ld norm(const Vector& a) { return a.norm(); }
ld abs(const Vector& a) { return a.abs(); }
ld arg(const Vector& a) { return a.arg(); }

ld dot(const Vector& a, const Vector& b) { return a.x * b.x + a.y * b.y; }
ld cross(const Vector& a, const Vector& b) { return a.x * b.y - a.y * b.x; }
ld distance(const Vector& a, const Vector& b) { return abs(b - a); }

struct Line {
  Point s, t;
  Line() = default;
  Line(const Point& _s, const Point& _t) : s(_s), t(_t) {}

  friend std::istream& operator>>(std::istream& is, Line& l) {
    return is >> l.s >> l.t;
  }
  friend std::ostream& operator<<(std::ostream& os, const Line& l) {
    return os << l.s << " to " << l.t;
  }

  Vector direction() const { return t - s; }
};

struct Segment : Line {
  using Line::Line;
  Segment(const Line& l) : Line(l) {}
  ld length() const { return direction().abs(); }
};

ld length(const Segment& seg) { return seg.length(); }

Point project(const Point& p, const Line& l) {
  Vector v = l.direction().unit();
  return l.s + v * dot(p - l.s, v);
}
Point reflect(const Point& p, const Line& l) {
  Point mid = project(p, l);
  return mid * 2 - p;
}

enum Position {
  COUNTER_CLOCKWISE = -1,
  CLOCKWISE         = +1,
  ONLINE_BACK       = -2,
  ONLINE_FRONT      = +2,
  ON_SEGMENT        = 0
};
Position ccw(const Point& p, const Segment& seg) {
  Vector vd = seg.direction();
  Vector vp = p - seg.s;
  int sgnA  = sgn(cross(vd, vp));
  if (sgnA == +1) return COUNTER_CLOCKWISE;
  if (sgnA == -1) return CLOCKWISE;
  if (sgn(dot(vd, vp)) == -1) return ONLINE_BACK;
  if (sgn(norm(vd) - norm(vp)) == -1) {
    return ONLINE_FRONT;
  } else {
    return ON_SEGMENT;
  }
}

bool parallel(const Line& la, const Line& lb) {
  return sgn(cross(la.direction(), lb.direction())) == 0;
}
bool orthogonal(const Line& la, const Line& lb) {
  return sgn(dot(la.direction(), lb.direction())) == 0;
}

bool intersect(const Point& p, const Segment& seg) {
  return ccw(p, seg) == ON_SEGMENT;
}
bool intersect(const Point& p, const Line& l) {
  auto status = ccw(p, l);
  return status == ONLINE_BACK or status == ONLINE_FRONT or
         status == ON_SEGMENT;
  // return abs(status) != 1;
}
bool intersect(const Segment& sa, const Segment& sb) {
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
bool intersect(const Segment& seg, const Line& l) {
  Vector vd = l.direction();
  Vector vs = seg.s - l.s;
  Vector vt = seg.t - l.s;
  return sgn(cross(vd, vs)) * sgn(cross(vd, vt)) <= 0;
}
bool intersect(const Line& la, const Line& lb) {
  bool isParallel = parallel(la, lb);
  if (isParallel == false) return true;
  return sgn(cross(la.direction(), la.s - lb.s)) == 0;
}

Point crosspoint(const Line& la, const Line& lb) {
  assert(intersect(la, lb));
  ld A = cross(la.direction(), lb.direction());
  ld B = cross(la.direction(), la.t - lb.s);
  if (sgn(A) == 0 && sgn(B) == 0) return lb.s;
  return lb.s + lb.direction() * B / A;
}

ld distance(const Point& p, const Segment& seg) {
  Point h = project(p, seg);
  if (intersect(h, seg)) return distance(p, h);
  return min(distance(p, seg.s), distance(p, seg.t));
}
ld distance(const Point& p, const Line& l) {
  return distance(p, project(p, l));
}
ld distance(const Segment& sa, const Segment& sb) {
  if (intersect(sa, sb)) return ld(0);
  return min({distance(sa.s, sb), distance(sa.t, sb), distance(sb.s, sa),
              distance(sb.t, sa)});
}
ld distance(const Segment& seg, const Line& l) {
  if (intersect(seg, l)) return ld(0);
  return min(distance(seg.s, l), distance(seg.t, l));
}
ld distance(const Line& la, const Line& lb) {
  if (intersect(la, lb)) return ld(0);
  return distance(la.s, lb);
}

// sort the points in COUNTER_CLOCKWISE order
// that starts from the half line(x <= 0, y = 0)
void polarSort(vector<Point>& PS) {
  const auto part = [](const Point& p) {
    int sgnX = sgn(p.x), sgnY = sgn(p.y);
    if (sgnY < 0) return 0;                 // (-pi, 0)
    if (sgnY == 0 and sgnX >= 0) return 1;  // 0
    if (sgnY > 0) return 2;                 // (0, +pi)
    if (sgnY == 0 and sgnX < 0) return 3;   // pi
    assert(false);
  };
  sort(all(PS), [&](const Point& a, const Point& b) {
    return part(a) == part(b) ? sgn(cross(a, b)) > 0 : part(a) < part(b);
  });
}

struct Polygon : vector<Point> {
  // points are given in the order of COUNTER_CLOCKWISE
  using vector<Point>::vector;
  Polygon() = default;
  Polygon(const vector<Point>& Ps) : vector<Point>(Ps) {}
  ld area() const {
    ld res = 0;
    for (size_t i = 0; i < size(); i++)
      res += cross(at(i), at((i + 1) % size()));
    return res / 2;
  }
  bool isConvex(bool acceptOnSegment = true) const {
    auto n = size();
    if (n <= 2) return true;

    for (size_t i = 0; i < n; i++) {
      auto status = ccw(at((i + 2) % n), Segment(at(i), at((i + 1) % n)));
      if (acceptOnSegment ? status == CLOCKWISE : status != COUNTER_CLOCKWISE)
        return false;
    }
    return true;
  }
  vector<Segment> segments() const {
    vector<Segment> res;
    for (size_t i = 0; i < size(); i++)
      res.emplace_back(at(i), at((i + 1) % size()));
    return res;
  }
};

ld area(const Polygon& poly) { return poly.area(); }
bool isConvex(const Polygon& poly, bool acceptOnSegment = true) {
  return poly.isConvex(acceptOnSegment);
}

enum Contain { OUTSIDE = 0, ON_EDGE = 1, INSIDE = 2 };
// Jordan curve theorem
Contain containment(const Point& p, const Polygon& poly) {
  auto n = poly.size();
  if (n == 0) return OUTSIDE;
  if (n == 1) return p == poly[0] ? ON_EDGE : OUTSIDE;

  bool inside = false;
  for (size_t i = 0; i < n; i++) {
    if (ccw(p, Segment(poly[i], poly[(i + 1) % n])) == ON_SEGMENT)
      return ON_EDGE;
    Point pa = poly[i] - p, pb = poly[(i + 1) % n] - p;
    if (pa.y > pb.y) swap(pa, pb);
    if (sgn(pa.y) <= 0 and sgn(pb.y) > 0 and sgn(cross(pa, pb)) < 0)
      inside = !inside;
  }
  return inside ? INSIDE : OUTSIDE;
}

Polygon convexHull(vector<Point> PS, bool acceptOnSegment = false) {
  if (PS.size() <= 2) return PS;

  sort(all(PS), [&](const Point& a, const Point& b) {
    return (equals(a.y, b.y) ? sgn(a.x - b.x) : sgn(a.y - b.y)) < 0;
  });  // starting from the y-minimum or the leftmost
  PS.erase(unique(all(PS)), end(PS));
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
  reverse(all(PS));
  for (const Point& p : PS) {
    while (convex.size() > k and check(p)) convex.pop_back();
    convex.emplace_back(p);
  }
  convex.pop_back();
  return convex;
}

// Rotating Calipers [forked from: @shiomusubi]
ld convexDiameter(const Polygon& convex) {
  auto N = convex.size();
  if (N <= 1) return ld(0);
  if (N == 2) return distance(convex[0], convex[1]);
  assert(isConvex(convex));

  size_t P = 0, Q = 0;
  for (size_t K = 0; K < N; K++) {
    if (sgn(convex[K].y - convex[P].y) > 0) P = K;
    if (sgn(convex[K].y - convex[Q].y) < 0) Q = K;
  }
  auto sP = P, sQ = Q;

  ld diameter = distance(convex[P], convex[Q]);
  do {  // each Point can't be repeat more than once
    int sgnA = sgn(cross(convex[(P + 1) % N] - convex[P],
                         convex[(Q + 1) % N] - convex[Q]));
    if (sgnA < 0) {
      P = (P + 1) % N;
    } else {
      Q = (Q + 1) % N;
    }
    diameter = max(diameter, distance(convex[P], convex[Q]));
  } while (P != sP || Q != sQ);
  return diameter;
}

Polygon convexCut(const Polygon& convex, const Line& l) {
  assert(isConvex(convex));
  Polygon res;
  for (size_t i = 0; i < convex.size(); i++) {
    const Point& cur = convex[i];
    const Point& nxt = convex[(i + 1) % convex.size()];
    if (ccw(cur, l) != CLOCKWISE) res.emplace_back(cur);
    if (intersect(Segment(cur, nxt), l))
      res.emplace_back(crosspoint(Segment(cur, nxt), l));
  }
  return res;
}

}  // namespace geometry
using namespace geometry;

void solve() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(10);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}