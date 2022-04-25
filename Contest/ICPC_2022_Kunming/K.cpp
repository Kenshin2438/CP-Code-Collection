#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void single() {
  ll n, a, b;
  cin >> n >> a >> b;
  cout << (n - 1) * a / b + 1 << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int T = 1; cin >> T;
  while (T--) single();
  return 0;
}
