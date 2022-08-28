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

void solve() {
  int n, q; cin >> n >> q;
  const int B = n / sqrt(q) + 1;

  vector<int> pos(n + 1), a(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    pos[i] = (i - 1) / B + 1;
  }

  auto val = a;
  sort(all(val)); val.erase(unique(all(val)), end(val));
  for (int i = 1; i <= n; i++) {
    a[i] = lower_bound(all(val), a[i]) - begin(val);
  }

  vector<array<int, 3>> Q(q);
  for (int i = 0; i < q; i++) {
    cin >> Q[i][0] >> Q[i][1], Q[i][2] = i;
  }
  sort(all(Q), [&](const auto &A, const auto &B) {
    return pos[A[0]] == pos[B[0]] ? A[1] < B[1] : A[0] < B[0];
  });

  vector<ll> ans(q);

  const function<ll(int, int)> brute_force = [&](int l, int r) {
    vector<int> cnt(n);
    ll res = -1;
    for (int i = l; i <= r; i++) {
      res = max(res, val[ a[i] ] * 1LL * (cnt[ a[i] ] += 1));
    }
    return res;
  };

  for (int b = 1; b <= pos[n]; b++) {
    vector<int> cnt(n);
    int Rlim = min(n, b * B);
    int L = Rlim + 1, R = Rlim;
    ll ANS = 0;

    for (static int id = 0; id < q; id++) {
      if (pos[Q[id][0]] != b) break;
      if (pos[Q[id][1]] == b) {
        ans[Q[id][2]] = brute_force(Q[id][0], Q[id][1]);
        continue;
      }

      while (R < Q[id][1]) {
        R += 1;
        ANS = max(ANS, val[ a[R] ] * 1LL * (cnt[ a[R] ] += 1));
      }
      auto cur_ANS = ANS;
      while (L > Q[id][0]) {
        L -= 1;
        ANS = max(ANS, val[ a[L] ] * 1LL * (cnt[ a[L] ] += 1));
      }
      ans[Q[id][2]] = ANS;

      while (L <= Rlim) cnt[ a[L++] ] -= 1;
      ANS = move(cur_ANS);
    }
  }

  for (const ll &x : ans) cout << x << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
