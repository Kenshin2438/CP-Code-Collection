#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n; cin >> n;
  vector<int> p(n), mp(n);
  for (int &x : p) {
    cin >> x;
    -- x;
  }
  for (int i = 0, x; i < n; i++) {
    cin >> x;
    -- x;
    mp[x] = i; 
  }
  for (int &x : p) x = mp[x];
  ll ans = 0;
  for (int i = 0; i < n; i++) {
    ans += abs(p[i] - i); 
  }
  cout << ans << '\n';
  return 0;
}