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

int t[3][10][10], e[3][10][10];

void solve() {
  int n, m, h; cin >> n >> m >> h;

  int k; cin >> k;
  for (int i = 1; i <= k; i++) {
    int type, ex, ey, ez;
    cin >> type >> ex >> ey >> ez;
    if (type == 0) {
      t[type][ey][ez] = ex, e[type][ey][ez] = i;
    } else if (type == 1) {
      t[type][ex][ez] = ey, e[type][ex][ez] = i;
    } else {
      t[type][ex][ey] = ez, e[type][ex][ey] = i;
    }
  }

  struct node { int time, pid, st, eid, x, y, z; };
  vector<node> ans;

  int q; cin >> q;
  for (int i = 1; i <= q; i++) {
    int pt, fx, fy, fz, tx, ty, tz;
    cin >> pt >> fx >> fy >> fz >> tx >> ty >> tz;
    if (fx != tx) {
      int pos = t[0][fy][fz];
      int now = fx >= pos ? fx - pos : n + fx - pos;
      while (now < pt) now += n;
      pt = now;
      ans.push_back({pt, i, 1, e[0][fy][fz], fx, fy, fz});
      pt += tx > fx ? tx - fx : n + tx - fx;
      ans.push_back({pt, i, 0, e[0][fy][fz], tx, fy, fz});
      pt += 1;
    }
    if (fy != ty) {
      int pos = t[1][tx][fz];
      int now = fy >= pos ? fy - pos : m + fy - pos;
      while (now < pt) now += m;
      pt = now;
      ans.push_back({pt, i, 1, e[1][tx][fz], tx, fy, fz});
      pt += ty > fy ? ty - fy : m + ty - fy;
      ans.push_back({pt, i, 0, e[1][tx][fz], tx, ty, fz});
      pt += 1;
    }
    if (fz != tz) {
      int pos = t[2][tx][ty];
      int now = fz >= pos ? fz - pos : h + fz - pos;
      while (now < pt) now += h;
      pt = now;
      ans.push_back({pt, i, 1, e[2][tx][ty], tx, ty, fz});
      pt += tz > fz ? tz - fz : h + tz - fz;
      ans.push_back({pt, i, 0, e[2][tx][ty], tx, ty, tz});
      pt += 1;
    }
  }

  sort(all(ans), [&](node a, node b) {
    return a.time == b.time
    ? a.eid == b.eid
      ? a.st == b.st
        ? a.pid < b.pid
        : a.st < b.st
      : a.eid < b.eid
    : a.time < b.time;
  });
  for (const auto &[time, pid, st, eid, x, y, z] : ans) {
    cout << "[" << time << "s]" << " ";
    cout << "Person " << pid << " ";
    cout << (st ? "IN" : "OUT") << " ";
    cout << "Elevator " << eid << " ";
    cout << "at (" << x << ", " << y << ", " << z << ")\n";
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
