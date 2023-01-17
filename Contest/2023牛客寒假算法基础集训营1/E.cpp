#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	double dist() const { return sqrt((double)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	double angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(double a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
  friend istream& operator>>(istream& is, P &p) {
    return is >> p.x >> p.y;}
};
typedef Point<double> P;
const double eps = 1e-6;

void solve() {
  vector<P> abc(3); 
  for (auto &&p : abc) cin >> p;
  P AB = abc[0] - abc[1];
  P CB = abc[2] - abc[1];

  vector<P> def(3); 
  for (auto &&p : def) cin >> p;
  P DE = def[0] - def[1];
  P FE = def[2] - def[1];

  if (fabs(AB.dist2() - CB.dist2()) <= eps)  
    return cout << "NO\n", void();

  bool ans = true;
  double ang;
  if (fabs(AB.dist2() - DE.dist2()) <= eps) {
    ang = AB.angle() - DE.angle();
    DE = DE.rotate(ang), FE = FE.rotate(ang);
    if (
      fabs(FE.x - CB.x) <= eps &&
      fabs(FE.y - CB.y) <= eps
    ) ans = false;
  } else {
    ang = AB.angle() - FE.angle();
    FE = FE.rotate(ang), DE = DE.rotate(ang);
    if (
      fabs(DE.x - CB.x) <= eps &&
      fabs(DE.y - CB.y) <= eps
    ) ans = false;
  }
  cout << (ans ? "YES" : "NO") << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}