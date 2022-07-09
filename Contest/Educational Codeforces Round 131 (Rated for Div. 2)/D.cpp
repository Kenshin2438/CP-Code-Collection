#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

const int N = 5e5 + 10;

int b[N], l[N], r[N], p[N];

void solve() {
  int n; cin >> n;
  vector<vector<pair<int, int>>> SB(n + 1); 
  for (int i = 1; i <= n; i++) {
    int x; cin >> x; 
    b[i] = x;
    {
      int L = 1, R = n;
      while (L <= R) {
        int m = (L + R) >> 1;
        if (i / m >= x) {
          r[i] = m;
          L = m + 1;
        } else {
          R = m - 1;
        }
      }
    }
    {
      int L = 1, R = n;
      while (L <= R) {
        int m = (L + R) >> 1;
        if (i / m <= x) {
          l[i] = m;
          R = m - 1;
        } else {
          L = m + 1;
        }
      }
    }
    SB[l[i]].emplace_back(r[i], i);
    // debug(l[i], r[i]);
  }

  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; 
  for (int i = 1; i <= n; i++) {
    while (!SB[i].empty()) pq.push(SB[i].back()), SB[i].pop_back();
    p[ pq.top().second ] = i;
    pq.pop();
  }
  for (int i = 1; i <= n; i++) {
    cout << p[i] << " \n"[i == n];
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T = 1;
  cin >> T;
  while (T--) solve();
  return 0;
}