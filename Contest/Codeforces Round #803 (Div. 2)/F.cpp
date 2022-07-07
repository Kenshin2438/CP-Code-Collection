#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

void solve() {
  int n; cin >> n;
  vector<int> a(n), b(n);
  for (int &x : a) cin >> x, -- x;
  for (int &x : b) cin >> x, -- x;
  
  if (a[0] != b[0] || a[n - 1] != b[n - 1]) {
    return cout << "NO\n", void();
  }

  vector<pair<int, int>> ans;
  const auto add = [&](int l, int r) {
    ans.emplace_back(l, r);
    reverse(a.begin() + l, a.begin() + r + 1);
  }; 
  for (int i = 1; i < n - 1; i++) {
    if (a[i] == b[i]) continue;
    // s.t. a[i - 1] == b[i - 1]
    int l = i - 1, r = -1;
    for (int j = i + 1; j < n; j++) {
      if (a[j] == a[i - 1] && a[j - 1] == b[i]) {
        r = j; 
        break;
      } 
    }
    if (r == -1) {
      int t = 0;
      for (int j = i; j < n - 1; j++) {
        for (int k = j + 1; k < n; k++) {
          if (a[j] != a[k]) continue;
          // s.t. a[j] == a[k]
          for (t = max(t, j); t < k; t++) {
            if (a[t] == a[i - 1] && a[t + 1] == b[i]) {
              add(j, k);
              r = j + k - t;
              goto B;
            }
          }
        }
      }
      B:;
    }
    if (r != -1) {
      add(l, r);
    } else return cout << "NO\n", void();
  }
  cout << "YES\n" << (int) ans.size() << '\n';
  for (const auto &[l, r] : ans) {
    cout << l + 1 << ' ' << r + 1 << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T; cin >> T;
  while (T--) solve();
  return 0;
}