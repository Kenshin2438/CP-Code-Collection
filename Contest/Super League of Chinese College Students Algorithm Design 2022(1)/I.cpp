#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

void solve() {
  int n; cin >> n;
  vector<ll> x(n), y(n);
  for (int i = 0; i < n; i++) {
    cin >> x[i] >> y[i];
  }
  vector<int> p(4); iota(all(p), 0);
  const int inf = 0x3f3f3f3f;
  do {
    bool ans = true;
    vector<array<ll, 3>> line; // A x + B y + C = 0
    for (int i = 0; i < n; i++) {

      bool ok = false;
      for (const array<ll, 3> &l : line) {
        if (l[0] * x[i] + l[1] * y[i] + l[2] == 0) {
          ok = true; break;
        }
      }
      if (ok) continue;

      if (line.size() == 4) { ans = false; break; }
      switch (p[line.size()]) {
      case 0: 
        line.push_back({0, 1, -y[i]}); 
        break;
      case 1:
        line.push_back({1, -1, y[i] - x[i]});
        break;
      case 2: 
        line.push_back({1, 0, -x[i]});
        break;
      case 3: 
        line.push_back({-1, -1, y[i] + x[i]});
        break;
      }
    }
    if (ans == false) continue;

    set<pair<double, double>> S;
    if (line.size() >= 2) {
      for (int i = 0; i < line.size(); i++) {
        for (int j = 0; j < i; j++) {
          auto A = line[j], B = line[i];
          S.insert({
            -1.0 * (A[2] * B[1] - B[2] * A[1]) / (A[0] * B[1] - B[0] * A[1]),
            -1.0 * (A[2] * B[0] - B[2] * A[0]) / (A[1] * B[0] - B[1] * A[0])
          });
        }
      }
    }
    if (S.size() <= 1) return cout << "YES" << '\n', void();
  } while (next_permutation(all(p)));
  cout << "NO" << '\n';
  
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T; cin >> T;
  while (T--) solve();
  
  return 0;
}