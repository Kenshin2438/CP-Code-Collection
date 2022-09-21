#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

const char num[13] = {
  'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'
};
const char col[4] = {
  'S', 'H', 'C', 'D'
};
pair<int, int> pk(const string &s) {
  int n = 0; while (num[n] != s[0]) n += 1;
  int c = 0; while (col[c] != s[1]) c += 1;
  return {n, c}; // {num, col}
}

vector<pair<int, int>> A, B, C;
bool vis[6];

inline int doMin(int step, int alpha, int beta);
inline int doMax(int step, int alpha, int beta);

int eval() {
  auto assess = [&](const vector<pair<int, int>> &p) {
    vector<int> n, c;
    for (const auto &[_n, _c] : p) {
      n.emplace_back(_n);
      c.emplace_back(_c);
    }
    sort(all(n)), sort(all(c));
    if (count(all(c), c[0]) == 5) {
      bool shun = true;
      for (int i = 1; i < 5; i++) {
        if (n[i] - n[i - 1] != 1) shun = false;
      }
      if (n == vector<int>{0, 9, 10, 11, 12}) shun = true;
      if (shun) {
        if (n[0] == 0) return 10;
        else return 9;
      } else {
        return 6;
      }
    } else {
      bool shun = true;
      for (int i = 1; i < 5; i++) {
        if (n[i] - n[i - 1] != 1) shun = false;
      }
      if (n == vector<int>{0, 9, 10, 11, 12}) shun = true;
      if (shun) {
        return 5;
      } else {
        if (count(all(n), n[0]) == 4 || count(all(n), n[4]) == 4) {
          return 8;
        } else if (
          (count(all(n), n[0]) == 2 && count(all(n), n[4]) == 3) ||
          (count(all(n), n[0]) == 3 && count(all(n), n[4]) == 2)
        ) return 7;
        else if (
          count(all(n), n[0]) == 3 || count(all(n), n[4]) == 3 || count(all(n), n[1]) == 3
        ) return 4;
        else if (
          count(all(n), n[1]) == 2 && count(all(n), n[3]) == 2
        ) return 3;
        else if (
          count(all(n), n[1]) == 2 || count(all(n), n[3]) == 2
        ) return 2;
        else return 1;
      }
    }
  };
  int vA = assess(A);
  int vB = assess(B);

  if (vA > vB) return  1;
  if (vA < vB) return -1;

  if (vA == 10) return 0;

  vector<int> na, nb;
  for (const auto &[_n, _c] : A) {
    na.emplace_back(_n);
  }
  for (const auto &[_n, _c] : B) {
    nb.emplace_back(_n);
  }

  {
    vector<int> cnt(13, 0);
    for (const int &x : na) cnt[x] += 1;
    sort(all(na), [&](int a, int b) {
      return cnt[a] == cnt[b] ? a < b : cnt[a] > cnt[b];
    });
  }
  {
    vector<int> cnt(13, 0);
    for (const int &x : nb) cnt[x] += 1;
    sort(all(nb), [&](int a, int b) {
      return cnt[a] == cnt[b] ? a < b : cnt[a] > cnt[b];
    });
  }

  if (vA == 9 || vA == 5) {
    if (na[0] == 0) na[0] = 13, sort(all(na));
    if (nb[0] == 0) nb[0] = 13, sort(all(nb));
  }

  if (na == nb) return 0;
  if (na < nb) return 1;
  return -1;
}

int doMax(int step, int alpha, int beta) { // Alice
  if (step == 6) return eval();
  for (int i = 0; i < 6; i++) if (!vis[i]) {
    vis[i] = true, A.push_back(C[i]);
    int now = doMin(step + 1, alpha, beta);
    vis[i] = false, A.pop_back();

    if (now > alpha) alpha = now;
    if (alpha >= beta) return alpha;
  }
  return alpha;
}
int doMin(int step, int alpha, int beta) { // Bob
  if (step == 6) return eval();
  for (int i = 0; i < 6; i++) if (!vis[i]) {
    vis[i] = true, B.push_back(C[i]);
    int now = doMax(step + 1, alpha, beta);
    vis[i] = false, B.pop_back();

    if (now < beta) beta = now;
    if (alpha >= beta) return beta;
  }
  return beta;
}
int battle(int step, int alpha, int beta) {
  // step & 1 ? Bob : Alice
  return (step & 1 ? doMin(step, alpha, beta) : doMax(step, alpha, beta));
}

void solve() {
  A.clear(), B.clear(), C.clear();
  for (int i = 0; i < 2; i++) {
    string s; cin >> s;
    A.push_back(pk(s));
  }
  for (int i = 0; i < 2; i++) {
    string s; cin >> s;
    B.push_back(pk(s));
  }
  // for (int i = 0; i < 6; i++) {
  //   string s; cin >> s;
  //   C.push_back(pk(s));
  //   vis[i] = false;
  // }
  // debug(A, B, C);
  int ans = battle(0, -1, 1); // Alice first
  if (ans > 0) cout << "Alice\n";
  else if (ans == 0) cout << "Draw\n";
  else cout << "Bob\n";
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
