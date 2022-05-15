#include <bits/stdc++.h>
using namespace std;

#define vec vector
#define str string

#define all(x) (x).begin(), (x).end()

typedef long long ll;

const int N = (int) 500 + 10;
const int inf = 0x3f3f3f3f;

int n, dis[N][N];

int main() {
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  // cout << fixed << setprecision(10);
  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      dis[i][j] = inf;
    }
    dis[i][i] = 0;
  }
  vec<int> F, M;
  for (int i = 1; i <= n; i++) {
    char op; cin >> op;
    if (op == 'F') F.push_back(i);
    else M.push_back(i);

    int m; cin >> m;
    while (m--) {
      int to, d; cin >> to >> op >> d;
      // cout << "debug " << to << " " << d << "\n";
      dis[i][to] = min(dis[i][to], d);
    }
  }
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        if (dis[i][k] == inf || dis[k][j] == inf) continue;
        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
      }
    }
  }
  vec<int> Fv(n + 1, 0), Mv = Fv;
  for (int x : F) {
    for (int y : M) {
      Fv[x] = max(Fv[x], dis[y][x]);
    }
  }
  for (int x : M) {
    for (int y : F) {
      Mv[x] = max(Mv[x], dis[y][x]);
    }
  }

  // cout << "debug Fv: ";
  // for (auto x : Fv) cout << x << ' ';
  // cout << "\n";
  //
  // cout << "debug Mv: ";
  // for (auto x : Mv) cout << x << ' ';
  // cout << "\n";

  {
    int val = inf;
    vec<int> ans;
    for (int x : F) {
      if (Fv[x] < val) {
        ans.clear(), ans.push_back(x);
        val = Fv[x];
      } else if (Fv[x] == val) {
        ans.push_back(x);
      }
    }
    sort(all(ans));
    for (int i = 0; i < (int) ans.size(); i++) {
      cout << ans[i] << " \n"[i + 1 == (int) ans.size()];
    }
  }
  {
    int val = inf;
    vec<int> ans;
    for (int x : M) {
      if (Mv[x] < val) {
        ans.clear(), ans.push_back(x);
        val = Mv[x];

      } else if (Mv[x] == val) {
        ans.push_back(x);
      }
    }
    sort(all(ans));
    for (int i = 0; i < (int) ans.size(); i++) {
      cout << ans[i] << " \n"[i + 1 == (int) ans.size()];
    }
  }
  return 0;
}
