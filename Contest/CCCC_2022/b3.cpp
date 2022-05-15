#include <bits/stdc++.h>
using namespace std;

#define vec vector
#define str string

#define all(x) (x).begin(), (x).end()

typedef long long ll;

const int N = (int) 1e5 + 10;

int n, q, rt;
vec<int> G[N];
int dep[N], p[N];

void dfs(int u, int fa) {
  dep[u] = dep[fa] + 1;
  for (int v : G[u]) {
    if (v == fa) continue;
    dfs(v, u);
  }
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);
  cin >> n >> q;
  for (int i = 1; i <= n; i++) {
    int x; cin >> x;
    if (x == -1) rt = i;
    else G[x].push_back(i), p[i] = x;
  }
  vec<int> vis(n + 1, false);
  dfs(rt, -1);
  int ans = 0, Mx = 0;
  vis[rt] = true;
  for (int x; q--; ) {
    cin >> x;
    if (vis[x] == false) {
      int t = x, d = 0;
      while (vis[t] == false) {
        vis[t] = true;
        t = p[t], d++;
      }
      Mx = max(Mx, dep[x]);
      ans = ans + d;
    }
    cout << ans * 2 - Mx + 1 << '\n';
  }
  return 0;
}
