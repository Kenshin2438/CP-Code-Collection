#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

template <typename T> struct Point {
  using P = Point;
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
template <typename T> struct ConvexHull {
  using P = Point<T>;
  vector<P> v;

  ConvexHull(vector<P> ps) {
    if (sz(ps) < 3) this->v = move(ps);
    else {
      sort(all(ps));
      vector<P> h(sz(ps) + 1);
      int s = 0, t = 0;
      for (int it = 2; it--; s = --t, reverse(all(ps)))
        for (const P &p : ps) {
          while (t >= s + 2 && h[t-2].cross(h[t-1], p) <= 0) t--;
          h[t++] = p;
        }
      this->v = {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
    }
  }

  T area2() const {
    T area = v.back().cross(v[0]);
    for (int i = 0; i < sz(v) - 1; i++) area += v[i].cross(v[i + 1]);
    return area;
  }
};

void solve() {
  int n, q; cin >> n >> q;
  vector<Point<ll>> ps;
  for (int i = 0; i < n; i++) {
    ll x, y; cin >> x >> y;
    ps.push_back(Point<ll>(x - 1, y));
    ps.push_back(Point<ll>(x + 1, y));
    ps.push_back(Point<ll>(x, y - 1));
    ps.push_back(Point<ll>(x, y + 1));
  }
  ConvexHull<ll> S(ps);
  ll A = S.area2();

  ll B = max(abs(S.v.back().x - S.v[0].x), abs(S.v.back().y - S.v[0].y));
  for (int i = 0; i < sz(S.v) - 1; i++) {
    B += max(abs(S.v[i].x - S.v[i + 1].x), abs(S.v[i].y - S.v[i + 1].y));
  }
  for (ll t; q--;) {
    cin >> t, --t;
    ll ans = A + B * t * 2 + t * t * 4;
    cout << (ans >> 1) << (ans & 1LL ? ".5" : ".0") << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(1);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
