#define PROBLEM "http://oj.daimayuan.top/course/10/problem/456"

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
typedef long long ll;

void SingleTest(int TestCase) {
  int n; cin >> n;
  map<int, int> mp; mp[0] = 0;
  vec<int> s(n + 1, 0);

  int l = -1, r = -1;
  for (int i = 1; i <= n; i++) {
    int x; cin >> x; x %= n;
    s[i] = (s[i - 1] + x) % n;
    if (mp.count(s[i])) {
      l = mp[s[i]] + 1, r = i;
    } else mp[s[i]] = i;
  }
  if (!~l && !~r) return cout << -1, void();
  cout << (r - l + 1) << '\n';
  for (int i = l; i <= r; i++) cout << i << " \n"[i == r];
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
