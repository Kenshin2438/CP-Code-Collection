#define PROBLEM "http://oj.daimayuan.top/course/10/problem/466"

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
  int n, k; cin >> n >> k;
  ll s = 0;
  map<ll, int> pos;
  vec<deque<int>> a;
  int cnt = 0;
  a.pb(deque<int>{0}), pos[0] = 0;

  ll ans = 0;
  for (int i = 1; i <= n; i++) {
    ll x; cin >> x; s = (s + x) % k;
    ll tmp = (k + (s - i) % k) % k;
    if (pos.find(tmp) == pos.end()) {
      pos[tmp] = ++cnt;
      a.pb(deque<int>{i});
    } else {
      int p = pos[tmp];
      while (!a[p].empty() && i - a[p].front() >= k) a[p].pop_front();
      ans += (ll) a[p].size();
      a[p].pb(i);
    }
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
