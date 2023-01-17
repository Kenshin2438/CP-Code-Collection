#include <iostream>
#include <vector>
using namespace std;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n, m, k; cin >> n >> m >> k;
  vector<vector<int>> grid(n, vector<int>(m));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> grid[i][j];
  for (int j = 0; j < m; j++) {
    for (int i = 1; i < n; i++) {
      grid[i][j] += grid[i - 1][j];
    } // 各列的前缀和，后续会使用
  }
  long long ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      vector<int> val(m);
      for (int k = 0; k < m; k++) {
        val[k] = grid[j][k] - (i ? grid[i - 1][k] : 0);
      } // 通过上面的前缀和优化
      for (int l = 0, r = 0, S = 0; r < m; r++) {
        S += val[r];
        while (S > k && l <= r) S -= val[l], l += 1;
        ans += max(0, r - l + 1);
      }
    }
  }
  cout << ans << '\n';
  return 0;
}