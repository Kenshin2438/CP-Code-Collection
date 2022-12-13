#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

const int N = 2e6 + 10;
int cnt[N];

void solve() {
  int n, k; cin >> n >> k;
  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i], cnt[a[i]] += 1;
  int even = 0, odd = 0;
  for (int i = 0; i < N; i++) {
    if (cnt[i]) continue;
    even += ~i & 1, odd += i & 1;
    if (max(even, odd) > k) {
      cout << (i & 1 ? "Bob" : "Alice") << '\n';
      break;
    }
  }
  for (int i = 0; i < n; i++) cnt[a[i]] -= 1;
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
