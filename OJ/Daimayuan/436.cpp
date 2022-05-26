#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
  #include "debug.hpp"
#else
  #define debug(...)
#endif

#define PII pair<int, int>
#define vec vector
#define str string
#define fi first
#define se second
#define pb push_back
#define all(a) a.begin(), a.end()

typedef double db;
typedef long long ll;

const int N = (int)5e5 + 10;

int n, a[N];

ll smax[N], smin[N];

void SingleTest(int TestCase) {
  cin >> n;
  debug(n);
  for (int i = 1; i <= n; i++) cin >> a[i];
  stack<int> mx;
  a[0] = 1e9, mx.push(0);
  for (int i = 1; i <= n; i++) {
    while (!mx.empty() && a[mx.top()] <= a[i]) mx.pop();
    int j = mx.top();
    mx.push(i);
    smax[i] = smax[j] + 1LL * (i - j) * a[i];
  }
  stack<int> mi;
  a[0] = -1, mi.push(0);
  for (int i = 1; i <= n; i++) {
    while (!mi.empty() && a[mi.top()] >= a[i]) mi.pop();
    int j = mi.top();
    mi.push(i);
    smin[i] = smin[j] + 1LL * (i - j) * a[i];
  }
  cout << accumulate(smax + 1, smax + 1 + n, 0LL) -
          accumulate(smin + 1, smin + 1 + n, 0LL);
}

void init() {}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  // cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
