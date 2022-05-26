#define PROBLEM "http://oj.daimayuan.top/course/11/problem/460"

#include "bits/stdc++.h"
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

void SingleTest(int TestCase) {
  int n, m; cin >> n >> m;
  bitset<(int) 1e5 + 10> ok;
  ok[0] = 1;
  while (n--) {
    int a, b; cin >> a >> b;
    ok = (ok << b) | (ok << a);
  }
  for (int i = 0; i <= m; i++) cout << ok[i];
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
