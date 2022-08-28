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
  int n; cin >> n;
  const int B = sqrt(n) + 1;

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

  vector<array<int, 3>> Q(n);
  for (int i = 0; i < n; i++) {
    cin >> Q[i][0] >> Q[i][1], Q[i][2] = i;
  }
  sort(all(Q), [&](const auto &A, const auto &B) {
    return pos[A[0]] == pos[B[0]] ? A[1] < B[1] : A[0] < B[0];
  });

  vector<int> ans(n);

  const function<int(int, int)> brute_force = [&](int l, int r) {
    vector<int> cnt(n);
    int res = -1, mx = -1;
    for (int i = l; i <= r; i++) {
      cnt[ a[i] ] += 1;
      if (cnt[ a[i] ] == mx) {
        res = min(res, a[i]);
      } else if (cnt[ a[i] ] > mx) {
        mx = cnt[ a[i] ], res = a[i];
      }
    }
    return res;
  };

  for (int b = 1; b <= pos[n]; b++) {
    vector<int> cnt(n);
    int Rlim = min(n, b * B);
    int L = Rlim + 1, R = Rlim, ANS = 0, MX = 0;

    for (static int id = 0; id < n; id++) {
      if (pos[Q[id][0]] != b) break;
      if (pos[Q[id][1]] == b) {
        ans[Q[id][2]] = brute_force(Q[id][0], Q[id][1]);
        continue;
      }

      while (R < Q[id][1]) {
        R += 1;
        cnt[ a[R] ] += 1;
        if (cnt[ a[R] ] == MX) {
          ANS = min(ANS, a[R]);
        } else if (cnt[ a[R] ] > MX) {
          MX = cnt[ a[R] ], ANS = a[R];
        }
      }
      int cur_ANS = ANS, cur_MX = MX;
      while (L > Q[id][0]) {
        L -= 1;
        cnt[ a[L] ] += 1;
        if (cnt[ a[L] ] == MX) {
          ANS = min(ANS, a[L]);
        } else if (cnt[ a[L] ] > MX) {
          MX = cnt[ a[L] ], ANS = a[L];
        }
      }
      ans[Q[id][2]] = ANS;

      while (L <= Rlim) cnt[ a[L++] ] -= 1;
      ANS = cur_ANS, MX = cur_MX;
    }
  }

  for (const int &x : ans) cout << val[x] << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
