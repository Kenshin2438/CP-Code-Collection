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
  int n; cin >> n;
  vector<int> p(n + 2);
  for (int i = 1; i <= n; i++) cin >> p[i];

  vector<int> leqPos(n + 2);
  {
    p[0] = 0;
    stack<int> pos;
    pos.push(0);

    for (int i = 1; i <= n; i++) {
      while (p[pos.top()] > p[i]) pos.pop();
      assert(!pos.empty());
      leqPos[i] = pos.top();
      pos.push(i);
    }
  }
  vector<int> geqPos(n + 2);
  {
    p[0] = n + 1;
    stack<int> pos;
    pos.push(0);

    for (int i = 1; i <= n; i++) {
      while (p[pos.top()] < p[i]) pos.pop();
      assert(!pos.empty());
      geqPos[i] = pos.top();
      pos.push(i);
    }
  }

  vector<int> rleqPos(n + 2);
  {
    p[n + 1] = 0;
    stack<int> pos;
    pos.push(n + 1);

    for (int i = n; i >= 1; i--) {
      while (p[pos.top()] > p[i]) pos.pop();
      assert(!pos.empty());
      rleqPos[i] = pos.top();
      pos.push(i);
    }
  }
  vector<int> rgeqPos(n + 2);
  {
    p[n + 1] = n + 1;
    stack<int> pos;
    pos.push(n + 1);

    for (int i = n; i >= 1; i--) {
      while (p[pos.top()] < p[i]) pos.pop();
      assert(!pos.empty());
      rgeqPos[i] = pos.top();
      pos.push(i);
    }
  }

  debug(leqPos);
  debug(geqPos);
  debug(rleqPos);
  debug(rgeqPos);

  vector<int> rlim(n + 2);
  for (int i = 0; i < n + 2; i++) {
    rlim[i] = min(leqPos[i], geqPos[i]);
  }
  debug(rlim);

  vector<int> cho(n + 2);

  rlim[n + 1] = 0;
  cho[n + 1] = n + 1;

  for (int i = n; i >= 1; i--) {
    int aft = cho[i + 1];
    if (rlim[i] > rlim[aft]) 
      cho[i] = i;
    else 
      cho[i] = aft;
  }

  debug(cho);
  for (int i = 1; i <= n; i++) {
    int r = cho[max(rleqPos[i], rgeqPos[i])];
    if (r == n + 1 || rlim[r] < i) continue;
    return cout << i << " " << r << "\n", void();
  }

  cout << -1 << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}