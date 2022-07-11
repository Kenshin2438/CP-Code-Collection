#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  
  int n; cin >> n;
  vector<array<ll, 3>> c(n);
  
  vector<int> p(n); iota(all(p), 0);
  function<int(int)> f = [&](int x) -> int {
    return x == p[x] ? x : p[x] = f(p[x]);
  };

  ll sx, sy, tx, ty; 
  cin >> sx >> sy >> tx >> ty;  

  for (int i = 0; i < n; i++) {
    cin >> c[i][0] >> c[i][1] >> c[i][2];
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (f(i) == f(j)) continue;

      ll dx = c[i][0] - c[j][0];
      ll dy = c[i][1] - c[j][1];
      ll dis = dx * dx + dy * dy;

      if (
        dis <= (c[i][2] + c[j][2]) * (c[i][2] + c[j][2]) &&
        dis >= (c[i][2] - c[j][2]) * (c[i][2] - c[j][2])
      ) {
        p[f(i)] = f(j);
      }
    }
  }

  vector<int> S, T; 
  for (int i = 0; i < n; i++) {
    ll dx = c[i][0] - sx;
    ll dy = c[i][1] - sy;
    ll dis = dx * dx + dy * dy;
  
    if (dis == c[i][2] * c[i][2]) {
      S.push_back(i);
    }
  }
  for (int i = 0; i < n; i++) {
    ll dx = c[i][0] - tx;
    ll dy = c[i][1] - ty;
    ll dis = dx * dx + dy * dy;
  
    if (dis == c[i][2] * c[i][2]) {
      T.push_back(i);
    }
  }

  for (int ss : S) for (int tt : T) {
    if (f(ss) == f(tt)) {
      return cout << "Yes\n", 0;
    } 
  }
  cout << "No" << '\n';

  return 0;
}