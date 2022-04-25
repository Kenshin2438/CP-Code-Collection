#include <bits/stdc++.h>
using namespace std;

#define vec vector
#define all(x) (x).begin(), (x).end()
using ll = long long;
using db = long double;

const int N = (int) 1e5 + 10;

int n, cnt[N];
vec<int> G[N];
db b[N], a[N], ave;

void sol(int u, int fa) {
  cnt[u] = 1, a[u] = b[u];
  db val = -1e8;
  vec<tuple<db, int>> s;
  for (int v : G[u]) {
    if (v == fa) continue;
    sol(v, u);
    s.push_back({a[v], cnt[v]});
    if (val < (a[v] * cnt[v] + b[u]) / (cnt[v] + 1)) {
      val = (a[v] * cnt[v] + b[u]) / (cnt[v] + 1);
      cnt[u] = cnt[v] + 1, a[u] = val;
    }
    if (val < (b[u] + b[v]) / 2) {
      val = (b[u] + b[v]) / 2;
      cnt[u] = 2, a[u] = val;
    }
  }
  sort(all(s), greater<tuple<db, int>>());
  if (s.size() >= 2) {
    db a1, a2;
    int t1, t2;
    tie(a1, t1) = s[0];
    tie(a2, t2) = s[1];
    ave = max(ave, (a1 * t1 + a2 * t2 + b[u]) / (t1 + t2 + 1));
    vec<db> ss;
    for (int v : G[u]) {
      if (v == fa) continue;
      ss.push_back(b[v]);
    }
    sort(all(ss), greater<db>());
    // for (db vv : ss) cout << "debug : " << vv << " ";
    ave = max(ave, (b[u] + ss[0] + ss[1]) / 3);
  }
  ave = max(ave, val);
  // cout << "debug " << a[u] << " " << cnt[u] << "\n";
}

void single() {
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> b[i];
  for (int i = 1; i < n; i++) {
    int u, v; cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
  db ans = 0;
  {
    ave = -1e8, sol(1, 0);
    ans = max(ans, ave * ave / 4);
  }
  for (int i = 1; i <= n; i++) {
    b[i] = b[i] * -1;
  }
  {
    ave = -1e8, sol(1, 0);
    ans = max(ans, ave * ave / 4);
  }
  cout << ans;
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T = 1; // cin >> T;
  cout << fixed << setprecision(10);
  while (T--) single();
  return 0;
}
