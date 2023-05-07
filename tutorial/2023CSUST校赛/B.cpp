#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

constexpr int N = (int) 5E6 + 10;
int phi[N];

void initPhi() {
  vector<int> p;
  phi[1] = 1;
  for (int i = 2; i < N; i++) {
    if (phi[i] == 0) {
      phi[i] = i - 1;
      p.emplace_back(i);
    }
    for (const int &pr : p) {
      if (pr * 1LL * i >= N) break;
      if (i % pr == 0) {
        phi[pr * i] = phi[i] * pr;
        break;
      } else {
        phi[pr * i] = phi[i] * (pr - 1);
      }
    }
  }
}

void solve() {
  initPhi();

  int n, q; cin >> n >> q;
  assert(1 <= n && n <= (int) 1E5);
  assert(1 <= q && q <= (int) 1E5);

  const int BLOCK = n / sqrt(q) + 2;
  const int M = (n - 1) / BLOCK + 1;

  vector<int> a(n), pos(n), L(M, n), R(M, -1);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    assert(1 <= a[i] && a[i] <= (int) 5E6);

    pos[i] = i / BLOCK;
    L[pos[i]] = min(L[pos[i]], i);
    R[pos[i]] = max(R[pos[i]], i);
  }

  constexpr ll inf = (ll) 1E18;
  const auto chk = [&](int na, int nb) {
    return na != phi[nb] && nb != phi[na];
  };

  const auto DP = [&](int s, int t) -> vector<ll> {
    vector<ll> res(4);

    if (t == s) {
      res[0b00] = 0;
      res[0b01] = -inf;
      res[0b10] = -inf;
      res[0b11] = a[t];
      return res;
    }

    if (t - s + 1 == 2) {
      res[0b00] = 0;
      res[0b01] = a[s];
      res[0b10] = a[t];
      res[0b11] = chk(a[t], a[s])  ? (a[t] + a[s]) : -inf;
      return res;
    }

    {
      ll A0 = 0;
      ll A1 = a[s + 1];
      for (int i = s + 2; i <= t; i++) {
        ll nA0 = max(A0, A1);
        ll nA1 = max(A0 + a[i], chk(a[i], a[i - 1]) ? A1 + a[i] : -inf);
        A0 = nA0, A1 = nA1;
      }
      res[0b00] = A0;
      res[0b10] = A1;
    }
    {
      ll A0 = a[s];
      ll A1 = chk(a[s], a[s + 1]) ? (a[s] + a[s + 1]) : -inf;
      for (int i = s + 2; i <= t; i++) {
        ll nA0 = max(A0, A1);
        ll nA1 = max(A0 + a[i], chk(a[i], a[i - 1]) ? A1 + a[i] : -inf);
        A0 = nA0, A1 = nA1;
      }
      res[0b01] = A0;
      res[0b11] = A1;
    }

    return res;
  };

  vector<bool> tag(M, false);
  vector<vector<ll>> dp(M, vector<ll>(4));

  const auto update = [&](int id) {
    if (tag[id]) return;
    tag[id] = all_of(begin(a) + L[id], begin(a) + R[id] + 1, 
                    [&](const int &x) { return x == 1; });
    dp[id] = DP(L[id], R[id]);
  };

  for (int i = 0; i < M; i++) update(i);

  const auto modify = [&](int l, int r) {
    if (pos[l] == pos[r]) {
      if (tag[pos[l]] == false) {
        for (int i = l; i <= r; i++) a[i] = phi[a[i]];
        update(pos[l]);
      }
    } else {
      if (tag[pos[l]] == false) {
        for (int i = l; i <= R[pos[l]]; i++) a[i] = phi[a[i]];
        update(pos[l]);
      }
      if (tag[pos[r]] == false) {
        for (int i = r; i >= L[pos[r]]; i--) a[i] = phi[a[i]];
        update(pos[r]);
      }
      for (int k = pos[l] + 1; k < pos[r]; k++) {
        if (tag[k] == false) {
          for (int i = L[k]; i <= R[k]; i++) a[i] = phi[a[i]];
          update(k);
        }
      }
    }
  };

  const auto query = [&](int l, int r) {
    if (r - l + 1 <= 2 * BLOCK) {
      auto ans = DP(l, r);
      return *max_element(all(ans)); 
    } else {
      auto dpl = DP(l, R[pos[l]]);
      auto dpr = DP(L[pos[r]], r);
      ll A0 = max(dpl[0b00], dpl[0b01]);
      ll A1 = max(dpl[0b10], dpl[0b11]);
      for (int k = pos[l] + 1; k < pos[r]; k++) {
        ll nA0 = max(
          dp[k][0b00] + max(A0, A1), 
          dp[k][0b01] + (chk(a[L[k]], a[R[k - 1]]) ? max(A0, A1) : A0)
        );
        ll nA1 = max(
          dp[k][0b10] + max(A0, A1), 
          dp[k][0b11] + (chk(a[L[k]], a[R[k - 1]]) ? max(A0, A1) : A0)
        );
        A0 = nA0, A1 = nA1;
      }
      {
        ll nA0 = max(
          dpr[0b00] + max(A0, A1), 
          dpr[0b01] + (chk(a[L[pos[r]]], a[R[pos[r] - 1]]) ? max(A0, A1) : A0)
        );
        ll nA1 = max(
          dpr[0b10] + max(A0, A1), 
          dpr[0b11] + (chk(a[L[pos[r]]], a[R[pos[r] - 1]]) ? max(A0, A1) : A0)
        );
        A0 = nA0, A1 = nA1;
      }
      return max(A0, A1);
    }
  };

  for (int _ = 0; _ < q; _++) {
    int op, l, r; cin >> op >> l >> r;
    assert(1 <= l && l <= r && r <= n);
    -- l, -- r;
    if (op == 1) {
      modify(l, r);
    } else if (op == 2) {
      cout << query(l, r) << '\n';
    } else {
      assert(false);
    }
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}