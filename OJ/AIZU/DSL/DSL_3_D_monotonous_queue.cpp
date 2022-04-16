#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

#define PII pair<int, int>
#define vec vector
#define str string
#define fi first
#define se second
#define all(a) a.begin(), a.end()

using db = double;
using ll = long long;

void SingleTest(int TestCase) {
  int n, L; cin >> n >> L;
  vec<int> a(n);
  for (auto &x : a) cin >> x;
  deque<int> Q;
  for (int r = 0; r < n; r++) {
    while (!Q.empty() && a[Q.back()] >= a[r]) Q.pop_back();
    Q.push_back(r);
    while (!Q.empty() && (r - Q.front() + 1) > L) Q.pop_front();
    if (r >= L - 1) cout << a[Q.front()] << " \n"[r + 1 == n];
  }
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  // cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
