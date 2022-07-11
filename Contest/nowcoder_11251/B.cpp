#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n;
  cin >> n;

  vector<ll> a(n);
  for (ll &x : a) cin >> x;

  string col; 
  cin >> col;

  ll ans = 0;

  map<pair<int, char>, ll> s;

  s[{1, 'R'}] = 0;
  s[{0, 'R'}] = 0;
  s[{1, 'B'}] = 0;
  s[{0, 'B'}] = 0;

  for (int i = 0; i < n; i++) {
    int r = a[i] % 2;
    char c = col[i];

    r = r ^ 1 ^ 0;
    c = c ^ 'R' ^ 'B';

    ans = max(ans, s[{r, c}] + a[i]);

    s[{a[i] % 2, col[i]}] = max(s[{a[i] % 2, col[i]}], s[{r, c}] + a[i]);
  }

  cout << ans << '\n';
  return 0;
}