#define PROBLEM "http://oj.daimayuan.top/course/10/problem/468"

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

typedef double db;
using ull = unsigned long long;

const ull mod = 998244353;

void SingleTest(int TestCase) {
  int n, k; cin >> n >> k;
  vec<ull> a(n);
  for (ull &x : a) cin >> x;
  ull pre = 0, ans = 0;
  for (int i = 0; i < n; i++) {
    debug(bitset<10>(pre));
    debug(i, bitset<10>(a[i]));
    if ((a[i] & pre) == a[i]) continue;
    int num = __builtin_popcountll(a[i] & ~pre); // a[i] = 1, pre = 0
    int cnt = k - __builtin_popcountll(pre); // pre = 0
    debug(num, cnt);
    ans = (ans + ((1ULL << cnt) - (1ULL << (cnt - num))) % mod * (i + 1) % mod) % mod;
    pre |= a[i];
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
