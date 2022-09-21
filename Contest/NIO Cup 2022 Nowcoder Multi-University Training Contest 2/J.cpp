#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ld = long double;

pair<ld, ld> LeastSquares(const vector<ld>& X, const vector<ld>& Y) {
  int vec_size = X.size();
  ld sum1 = 0, sum2 = 0;
  ld x_avg = std::accumulate(X.begin(), X.end(), 0.0L) / vec_size;
  ld y_avg = std::accumulate(Y.begin(), Y.end(), 0.0L) / vec_size;

  for (int i = 0; i < vec_size; ++i) {
    sum1 += (X.at(i) * Y.at(i) - x_avg * y_avg);
    sum2 += (X.at(i) * X.at(i) - x_avg * x_avg);
  }

  ld k = sum1 / sum2;
  ld b = y_avg - k * x_avg;
  return { k, b };
}

void solve() {
  int n; cin >> n;
  vector<ld> X(n), Y(n);
  for (int i = 0; i < n; i++) {
    cin >> Y[i];
    X[i] = i;
  }
  auto [k, b] = LeastSquares(X, Y);
  ld ans = 0;
  for (int i = 0; i < n; i++) {
    ans += pow(k * X[i] + b - Y[i], 2);
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(10);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
