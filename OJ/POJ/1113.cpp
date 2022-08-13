#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>
#include <cmath>
using namespace std;

template <typename T> struct Point {
  // using P = Point;
  typedef Point<T> P;
  T x, y;
  explicit Point(T _x = 0, T _y = 0) : x(_x), y(_y) {}
  bool operator<(P p) const { return tie(x, y) < tie(p.x, p.y); }
  bool operator==(P p) const { return tie(x, y) == tie(p.x, p.y); }
  P operator+(P p) const { return P(x + p.x, y + p.y); }
  P operator-(P p) const { return P(x - p.x, y - p.y); }
  P operator*(T d) const { return P(x * d, y * d); }
  P operator/(T d) const { return P(x / d, y / d); }
  T dot(P p) const { return x * p.x + y * p.y; }
  T cross(P p) const { return x * p.y - y * p.x; }
  T cross(P a, P b) const { return (a - *this).cross(b - *this); }
  T dist2() const { return x * x + y * y; }
  double dist() const { return sqrt((double)dist2()); }
  // angle to x-axis in interval [-pi, pi]
  double angle() const { return atan2(y, x); }
  P unit() const { return *this / dist(); }  // makes dist()=1
  P perp() const { return P(-y, x); }        // rotates +90 degrees
  P normal() const { return perp().unit(); }
  // returns point rotated 'a' radians ccw around the origin
  P rotate(double a) const {
    return P(x * cos(a) - y * sin(a), x * sin(a) + y * cos(a));
  }
  friend ostream& operator<<(ostream& os, P p) {
    return os << "(" << p.x << "," << p.y << ")";
  }
};

#define sz(x) static_cast<int>((x).size())
template <typename T> struct Melkman {
  // using P = Point<T>;
  typedef Point<T> P;

  deque<P> v;
  explicit Melkman() {}

  void insert(const P &p) {
    if (sz(v) < 2) v.push_back(p);
    else if (sz(v) == 2) {
      int cp = v[0].cross(v[1], p);
      if (cp == 0) {
        v.pop_back(), v.push_back(p);
      } else {
        if (cp < 0) swap(v[0], v[1]);
        v.push_back(p), v.push_front(p);
      }
    } else {
      if (v[sz(v) - 2].cross(v[sz(v) - 1], p) > 0 && v[1].cross(v[0], p) < 0) {
        return;
      }
      while (v[sz(v) - 2].cross(v[sz(v) - 1], p) <= 0) v.pop_back();
      v.push_back(p);
      while (v[1].cross(v[0], p) >= 0) v.pop_front();
      v.push_front(p);
    }
  }

  T area2() const {
    T area = 0;
    for (int i = 0; i < sz(v); i++) area += v[i].cross(v[(i + 1) % sz(v)]);
    return area;
  }
};

int main() {
  int n, r; cin >> n >> r;
  Melkman<long long> S;
  for (int i = 0; i < n; i++) {
    long long xx, yy; cin >> xx >> yy;
    S.insert(Point<long long>(xx, yy));
  }
  double ans = 6.2831853071795864 * r;
  for (int i = 0; i < (int) S.v.size() - 1; i++) {
    ans += (S.v[i] - S.v[i + 1]).dist();
  }
  cout << int(ans + 0.5) << '\n';
  return 0;
}
