#define PROBLEM "http://oj.daimayuan.top/course/10/problem/503"

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
#define pb push_back
#define all(a) a.begin(), a.end()

using db = long double;
using ll = long long;

void SingleTest(int TestCase) {
  int n; cin >> n;
  vec<PII> tasks(n);
  for (auto &[d, p] : tasks) {
    cin >> d >> p;
    // assert(d >= 1 && d <= 1e9);
    // assert(p >= 1 && p <= 1e9);
  }
  sort(all(tasks));
  priority_queue<int, vec<int>, greater<int>> pq;
  ll ans = 0, sum = 0;
  for (auto [d, p] : tasks) {
    if (d > (int) pq.size()) pq.push(p), sum += p;
    else {
      if (pq.empty()) continue;
      if (p > pq.top()) {
        sum -= pq.top(), pq.pop();
        sum += p, pq.push(p);
      }
    }
    ans = max(ans, sum);
  }
  cout << ans;
}

void init() { }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  // cin >> T;
  for (init(); T--; ) SingleTest(++TestCase);
  return 0;
}
