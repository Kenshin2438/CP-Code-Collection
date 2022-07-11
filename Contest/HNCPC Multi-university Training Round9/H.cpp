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
  int n; cin >> n;
  priority_queue<ll> scare;
  vec<ll> shot;
  for (int i = 1; i <= n; i++) {
    ll a; cin >> a;
    scare.push(-a);
    while (SZ(scare) > SZ(shot)) {
      shot.push_back(-scare.top());
      scare.pop();
    }
  }
  cout << accumulate(all(shot), 0LL) << '\n';
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
