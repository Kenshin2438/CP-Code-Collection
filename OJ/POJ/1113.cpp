#include <iostream>
#include <algorithm>
#include <deque>
#include <vector>
#include <cmath>
using namespace std;

struct Point_2D {
  int x, y;
  Point_2D(int _x = 0, int _y = 0) : x(_x), y(_y) {}
};

int cp(Point_2D p0, Point_2D p1, Point_2D p2) {
  return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

deque<Point_2D> v;
void Melkman(Point_2D p) {
  if (v.size() < 2) {
    v.push_back(p);
  } else if (v.size() == 2) {
    int det = cp(v[0], v[1], p);
    if (det != 0) {
      if (det < 0) swap(v[0], v[1]);
      v.push_back(p);
      v.push_front(p);
    } else {
      v.pop_back();
      v.push_back(p);
    }
  } else {
    if (cp(v[v.size() - 2], v[v.size() - 1], p) > 0 && cp(v[1], v[0], p) < 0) return ;
    while (cp(v[v.size() - 2], v[v.size() - 1], p) <= 0) v.pop_back();
    v.push_back(p);
    while (cp(v[1], v[0], p) >= 0) v.pop_front();
    v.push_front(p);
  }
}

double dis(Point_2D p0, Point_2D p1) {
  double dx = p0.x - p1.x;
  double dy = p0.y - p1.y;
  return sqrt(dx * dx + dy * dy);
}

int main() {
  int n, r; cin >> n >> r;
  for (int i = 0; i < n; i++) {
    int xx, yy; cin >> xx >> yy;
    Melkman(Point_2D(xx, yy));
  } 
  double ans = 6.2831853071795864 * r;
  for (int i = 0; i < (int) v.size() - 1; i++) {
    ans += dis(v[i], v[i + 1]);
  }
  cout << int(ans + 0.5) << '\n';
  return 0;
}