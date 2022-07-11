#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  ll m, fm; cin >> m >> fm;
  vector<ll> a;
  while (fm) {
    a.push_back(fm % m);
    fm /= m;
  }
  cout << a.size() << '\n';
  for (ll &x : a) cout << x << ' ';
  return 0;
} 