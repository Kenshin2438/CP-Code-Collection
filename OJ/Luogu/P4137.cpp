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

  vector<array<int, 3>> Q(q);
  for (int i = 0; i < q; i++) {
    cin >> Q[i][0] >> Q[i][1], Q[i][2] = i;
  }
  sort(all(Q), [&](const auto &A, const auto &B) {
    return pos[A[0]] == pos[B[0]] ? A[1] > B[1] : A[0] < B[0];
  });

  vector<int> bfcnt(200010);
  const function<int(int, int)> brute_force = [&](int l, int r) {
    for (int i = l; i <= r; i++) bfcnt[ a[i] ]++;
    int res = 0; while (bfcnt[res]) res++;
    for (int i = l; i <= r; i++) bfcnt[ a[i] ]--;
    return res;
  };

  vector<int> ans(q);

  vector<int> cnt(200010);
  int L = 1, R = n, gANS = 0;
  for (int i = L; i <= R; i++) cnt[ a[i] ]++;
  while (cnt[gANS]) gANS++;

  for (int b = 1; b <= pos[n]; b++) {
    int Llim = (b - 1) * B + 1;
    while (R < n) {
      ++R;
      cnt[a[R]]++;
    }
    while (L < Llim) {
      cnt[a[L]]--;
      if (cnt[a[L]] == 0) gANS = min(gANS, a[L]);
      L++;
    }
    int ANS = gANS;

    for (static int id = 0; id < q; id++) {
      if (pos[Q[id][0]] != b) break;
      if (pos[Q[id][1]] == b) {
        ans[Q[id][2]] = brute_force(Q[id][0], Q[id][1]);
        continue;
      }

      while (R > Q[id][1]) {
        cnt[a[R]]--;
        if (cnt[a[R]] == 0) ANS = min(ANS, a[R]);
        R--;
      }
      auto cur_ANS = ANS;
      while (L < Q[id][0]) {
        cnt[a[L]]--;
        if (cnt[a[L]] == 0) ANS = min(ANS, a[L]);
        L++;
      }
      ans[Q[id][2]] = ANS;

      while (L > Llim) {
        --L;
        cnt[a[L]]++;
      }
      ANS = move(cur_ANS);
    }
  }

  for (const auto &x : ans) cout << x << '\n';
}

int main() {
  // freopen("_.in", "r", stdin);
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  // clock_t TS = clock();
  while (T--) solve();
  // clock_t TD = clock();

  // debug(double(TD - TS) / 1000);

  return 0;
}
