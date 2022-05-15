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
#define all(a) (a).begin(), (a).end()
#define SZ(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

void SingleTest(int TestCase) {
  int n, m; cin >> n >> m;
  vec<int> a(n);
  for (int &x : a) cin >> x;
  set<int> num;
  for (int i = 0; i < n; i++) {
    {
      int tmp = a[i];
      if (tmp <= m && num.find(tmp) == num.end()) {
        num.insert(tmp);
      }
    }
    for (int j = i + 1; j < n; j++) {
      {
        int tmp = a[i] + a[j];
        if (tmp <= m && num.find(tmp) == num.end()) {
          num.insert(tmp);
        }
      }
      for (int k = j + 1; k < n; k++) {
        {
          int tmp = a[i] + a[j] + a[k];
          if (tmp <= m && num.find(tmp) == num.end()) {
            num.insert(tmp);
          }
        }
      }
    }
  }
  cout << SZ(num) << '\n';
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
