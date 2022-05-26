#define PROBLEM "http://oj.daimayuan.top/course/11/problem/463"

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

const int N = (int) 1e5 + 10;

ll a[N];

void SingleTest(int TestCase) {
  int n; cin >> n;
  ll k; cin >> k;
  map<ll, int> cnt;
  for (int i = 1; i <= n; i++) {
    cin >> a[i], cnt[a[i]]++;
  }
  ll sum = accumulate(a + 1, a + 1 + n, 0LL);
  if (sum > k) return cout << -1, void();
  
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
