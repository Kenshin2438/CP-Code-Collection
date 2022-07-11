#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

struct Point {
  double x, y;
  Point(double _x = 0, double _y = 0) : x(_x), y(_y){};
  Point operator+(Point &o) const { return Point(x + o.x, y + o.y); }
  Point operator-(Point &o) const { return Point(x - o.x, y - o.y); }
  Point operator*(double k) const { return Point(x * k, y * k); }
  Point operator/(double k) const { return Point(x / k, y / k); }
  double norm() const { return x * x + y * y; }
  double abs() const { return sqrt(norm()); }
};
using Vector = Point;

double dot(Vector a, Vector b) { return a.x * b.x + a.y * b.y; }
double cross(Vector a, Vector b) { return a.x * b.y - a.y * b.x; }
double norm(Vector a) { return a.norm(); }
double abs(Vector a) { return a.abs(); }

struct Segment {
  Point p1, p2;
};
using Line = Segment;

template <typename T>
bool equals(T a, T b) {
  return fabs((a) - (b)) < 1E-10;
}
bool isOrthogonal(Segment s1, Segment s2) {
  return equals(dot(s1.p2 - s1.p1, s2.p2 - s2.p1), 0.0);
}
bool isOrthogonal(Vector a, Vector b) { 
  return equals(dot(a, b), 0.0); 
}
bool isParallel(Vector a, Vector b) { 
  return equals(cross(a, b), 0.0); 
}
bool isParallel(Point a1, Point a2, Point b1, Point b2) {
  return equals(cross(a1 - a2, b1 - b2), 0.0);
}

Point project(Segment s, Point p) {
  Vector base = s.p2 - s.p1;
  double r = dot(p - s.p1, base) / norm(base);
  auto t = base * r;
  return s.p1 + t;
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(10);
  
  int x1, y1, x2, y2;
  cin >> x1 >> y1 >> x2 >> y2;
  auto S = Segment{Point(x1, y1), Point(x2, y2)};
  
  int q; cin >> q;
  while (q--) {
    int x, y; cin >> x >> y;
    auto P = Point(x, y);
    auto ans = project(S, P);
    cout << ans.x << " " << ans.y << '\n';
  }
  return 0;
}
