#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using PDD = pair<double, double>;
double dis(const PDD &A, const PDD &B) {
  double dx = A.first  -  B.first;
  double dy = A.second - B.second;
  return sqrt(dx * dx + dy * dy);
}

void solve() {
  vector<PDD> M(4), m(4);
  for (auto &p : M) cin >> p.first >> p.second;
  for (auto &p : m) cin >> p.first >> p.second;
  double k = dis(m[0], m[1]) / dis(M[0], M[1]);
  double CD = dis(M[2], M[3]), AD = dis(M[0], M[3]);
  double GH = dis(m[2], m[3]), EH = dis(m[0], m[3]);

  double X1 = (M[2].first - M[3].first) / CD - (m[2].first - m[3].first) / GH * k;
  double Y1 = (M[0].first - M[3].first) / AD - (m[0].first - m[3].first) / EH * k;
  double Z1 = m[3].first - M[3].first;

  double X2 = (M[2].second - M[3].second) / CD - (m[2].second - m[3].second) / GH * k;
  double Y2 = (M[0].second - M[3].second) / AD - (m[0].second - m[3].second) / EH * k;
  double Z2 = m[3].second - M[3].second;

  double x = (Z1 * Y2 - Z2 * Y1) / (X1 * Y2 - X2 * Y1);
  double y = (Z1 * X2 - Z2 * X1) / (Y1 * X2 - Y2 * X1);

  double X = M[3].first + (M[2].first - M[3].first) / CD * x + (M[0].first - M[3].first) / AD * y;
  double Y = M[3].second + (M[2].second - M[3].second) / CD * x + (M[0].second - M[3].second) / AD * y;

  cout << X << ' ' << Y << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(10);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
