#include <bits/stdc++.h>
using namespace std;

#define vec vector
#define str string

#define all(x) (x).begin(), (x).end()

typedef long long ll;

const int N = (int) 500;

int num[N][2];

int n, m, k;

int main() {
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);
  cin >> n >> k >> m;
  for (int i = 1; i <= n; i++) {
    int a, b; cin >> a >> b;
    if (a < 175) continue;
    num[a][b >= m] ++;
  }
  if (k == 0) return cout << 0 << '\n', 0;
  int ans = 0;
  vec<int> s;
  for (int i = 175; i <= 290; i++) {
    ans += num[i][1];
    if (num[i][0]) ans++, num[i][0]--;
    if (num[i][0]) {
      s.emplace_back(num[i][0]);
    }
  }
  k--;
  for (int x : s) {
    ans += min(k, x);
  }
  cout << ans << '\n';
  return 0;
}
