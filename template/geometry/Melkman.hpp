struct Point_2D {
  int x, y;
  Point_2D(int _x = 0, int _y = 0) : x(_x), y(_y) {}
};

int cross(Point_2D p0, Point_2D p1, Point_2D p2) {
  return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

deque<Point_2D> v;
void Melkman(Point_2D p) {
  if (v.size() < 2) {
    v.push_back(p);
  } else if (v.size() == 2) {
    int det = cross(v[0], v[1], p);
    if (det != 0) {
      if (det < 0) swap(v[0], v[1]);
      v.push_back(p);
      v.push_front(p);
    } else {
      v.pop_back();
      v.push_back(p);
    }
  } else {
    if (cross(v[v.size() - 2], v[v.size() - 1], p) > 0 && cross(v[1], v[0], p) < 0) return ;
    while (cross(v[v.size() - 2], v[v.size() - 1], p) <= 0) v.pop_back();
    v.push_back(p);
    while (cross(v[1], v[0], p) >= 0) v.pop_front();
    v.push_front(p);
  }
}