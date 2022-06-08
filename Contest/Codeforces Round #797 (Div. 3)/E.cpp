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
#define rall(a) (a).rbegin(), (a).rend()
#define sz(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

void SingleTest(__attribute__((unused)) int TestCase) {
  int n, k; cin >> n >> k;

  ll ans = 0LL;

  vec<ll> a(n);
  for (ll &x : a) {
    cin >> x;
    ans += x / k;
    x %= k;
  }

  sort(rall(a));
  for (int l = 0, r = n - 1; l < r;) {
    while (l < r && a[l] + a[r] < k) r--;
    if (l < r && a[l] + a[r] >= k) {
      ans++, l++, r--;
    }
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
