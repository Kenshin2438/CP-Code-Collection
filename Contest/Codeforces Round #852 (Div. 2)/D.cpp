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

void solve() {
  int n;
  cin >> n;
  vector<int> p(n), q(n), posP(n), posQ(n);
  for (int i = 0; i < n; i++) {
    cin >> p[i], --p[i];
    posP[p[i]] = i;
  }
  for (int i = 0; i < n; i++) {
    cin >> q[i], --q[i];
    posQ[q[i]] = i;
  }

  const auto U = [&](int l1, int r1, int l2, int r2) {
    if (l1 > r1 || l2 > r2) return 0;
    if (l1 < 0 || r1 >= n) return 0;
    if (l2 < 0 || r2 >= n) return 0;
    return max(0, min(r1, r2) - max(l1, l2) + 1);
  };
  const auto f = [&](ll n) { return n * (n + 1) / 2; };

  int pl = n, pr = -1;
  int ql = n, qr = -1;

  ll ans = 0;
  for (int mex = 0; mex < n; pl = min(pl, posP[mex]), pr = max(pr, posP[mex]),
           ql = min(ql, posQ[mex]), qr = max(qr, posQ[mex]), mex++) {
    if (mex == 0) {
      ans += f(U(0, posP[0] - 1, 0, posQ[0] - 1));
      debug(mex, ans);
      ans += f(U(posP[0] + 1, n - 1, posQ[0] + 1, n - 1));
      debug(mex, ans);
      ans += f(U(posP[0] + 1, n - 1, 0, posQ[0] - 1));
      debug(mex, ans);
      ans += f(U(0, posP[0] - 1, posQ[0] + 1, n - 1));
      debug(mex, ans);
    } else {
      if (posP[mex] >= pl && posP[mex] <= pr) continue;
      if (posQ[mex] >= ql && posQ[mex] <= qr) continue;
      int pP = posP[mex];

      int cho_pl_l, cho_pl_r;
      int cho_pr_l, cho_pr_r;
      if (pP < pl) {
        cho_pl_l = pP + 1, cho_pl_r = pl;
      } else {
        cho_pl_l = 0, cho_pl_r = pl;
      }
      if (pP > pr) {
        cho_pr_l = pr, cho_pr_r = pP - 1;
      } else {
        cho_pr_l = pr, cho_pr_r = n - 1;
      }

      int pQ = posQ[mex];

      int cho_ql_l, cho_ql_r;
      int cho_qr_l, cho_qr_r;
      if (pQ < ql) {
        cho_ql_l = pQ + 1, cho_ql_r = ql;
      } else {
        cho_ql_l = 0, cho_ql_r = ql;
      }
      if (pQ > qr) {
        cho_qr_l = qr, cho_qr_r = pQ - 1;
      } else {
        cho_qr_l = qr, cho_qr_r = n - 1;
      }

      ans += U(cho_pl_l, cho_pl_r, cho_ql_l, cho_ql_r) * 1LL *
             U(cho_pr_l, cho_pr_r, cho_qr_l, cho_qr_r);
    }
  }

  cout << ans + 1 << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}