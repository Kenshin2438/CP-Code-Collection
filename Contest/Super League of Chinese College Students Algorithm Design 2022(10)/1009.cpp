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

inline int doMin(int step, int alpha, int beta);
inline int doMax(int step, int alpha, int beta);

const int N = 1e5;
int n, col[N], cnt;

int doMax(int step, int alpha, int beta) {
  bool ok = false;
  for (int i = 1; i <= n; i++) {
    if (col[i] == 0 && col[i - 1] == 0 && col[i + 1] == 0) {
      ok = true; break;
    }
  }
  if (ok == false) return cnt;

  for (int i = 1; i <= n; i++) {
    if (col[i] == 0 && col[i - 1] == 0 && col[i + 1] == 0) {
      col[i] = 1; cnt += 1;
      int now = doMin(step + 1, alpha, beta);
      col[i] = 0; cnt -= 1;

      if (now > alpha) alpha = now;
      if (alpha >= beta) return alpha;
    }
  }
  return alpha;
}
int doMin(int step, int alpha, int beta) {
  bool ok = false;
  for (int i = 1; i <= n; i++) {
    if (col[i] == 0 && col[i - 1] == 0 && col[i + 1] == 0) {
      ok = true; break;
    }
  }
  if (ok == false) return cnt;

  for (int i = 1; i <= n; i++) {
    if (col[i] == 0 && col[i - 1] == 0 && col[i + 1] == 0) {
      col[i] = 1; cnt += 1;
      int now = doMax(step + 1, alpha, beta);
      col[i] = 0; cnt -= 1;

      if (now < beta) beta = now;
      if (alpha >= beta) return beta;
    }
  }
  return beta;
}
int battle(int step, int alpha, int beta) {
  return (step & 1 ? doMin(step, alpha, beta) : doMax(step, alpha, beta));
}

void solve() {
  for (n = 1; n <= 50; n++) {
    for (int player = 1; player >= 0; player--) {
      memset(col, 0, sizeof col);
      // 1 -> Alice ; 0 -> Bob
      debug(n, player ? "Alice" : "Bob", battle(player, 0, n));
    }
  }
}

int main() {
  // cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();
  // while (1) solve();

  return 0;
}
