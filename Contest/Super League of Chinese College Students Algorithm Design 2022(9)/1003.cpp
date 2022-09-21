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

const int N = 1e5, B = 325;
int pos[N + 10];
void init() {
  for (int i = 1; i <= N; i++) {
    pos[i] = (i - 1) / B + 1;
  }
}

void solve() {
  int n, q; cin >> n >> q;
  vector<int> p(n + 1);
  for (int i = 1; i <= n; i++) cin >> p[i];

  vector<array<int, 3>> Q(q);
  for (int i = 0; i < q; i++) {
    cin >> Q[i][0] >> Q[i][1], Q[i][2] = i;
  }
  sort(all(Q), [&](const auto &A, const auto &B) {
    return pos[A[0]] == pos[B[0]] ? A[1] < B[1] : A[0] < B[0];
  });

  for (int i = 0; i < n; i++) {
    
  }

  vector<int> ans(q);
  for (int i = 0; i < q; i++) {
    cout << ans[i] << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  init();

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
