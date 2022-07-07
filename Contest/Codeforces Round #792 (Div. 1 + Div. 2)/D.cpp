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
  int n, k; cin >> n >> k;
  vec<int> a(n), p(n);
  for (int &x : a) cin >> x;
  iota(all(p), 0);
  sort(all(p), [&](const int &A, const int &B) {
    return A + a[A] > B + a[B];
  });
  vec<bool> del(n, false);
  for (int i = 0; i < k; i++) del[p[i]] = true;
  ll ans = 0, pre = 0;
  for (int i = 0; i < n; i++) {
    if (del[i]) pre ++;
    else ans += a[i] + pre;
  }
  cout << ans << '\n';
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
