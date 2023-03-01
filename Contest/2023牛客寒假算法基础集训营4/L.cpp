#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

void solve() {
  ll va, vb, vc;
  cin >> va >> vb >> vc;
  ll S = (va + vb + vc);
  if (S & 1LL) return cout << "NO\n", void();
 
  S /= 2;
  vector<ll> e = {
    S - va, S - vb, S - vc
  };
  sort(all(e));
  if (e[0] <= 0 || (e[0] + e[1] <= e[2])) 
    return cout << "NO\n", void();

  cout << "YES\n";
  cout << S - va << " " << S - vb << " " << S - vc << "\n";
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}