// CF 600D
using db = long double;
using ll = long long;

void SingleTest(int TestCase) {
  db x1, y1, r1;
  cin >> x1 >> y1 >> r1;
  db x2, y2, r2;
  cin >> x2 >> y2 >> r2;

  const db PI = acos(-1);
  auto [r, R] = minmax(r1, r2);
  db D = sqrtl((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
  db ans = 0;

  if (D >= r + R) {
    ans = 0;
  } else if (D <= R - r) {
    ans = PI * r * r;
  } else {
    db a = acos((r * r + D * D - R * R) / (2 * r * D));
    db b = acos((R * R + D * D - r * r) / (2 * R * D));
    ans  = a * r * r + b * R * R;
    ans -= r * sin(a) * r * cos(a);
    ans -= R * sin(b) * R * cos(b);
  }
  cout << ans;
}