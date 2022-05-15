#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  int a, b; cin >> a >> b;
  ll ans = 1;
  for (int i = 1, _ = a + b; i <= _; i++) {
    ans = ans * i;
  }
  cout << ans << '\n';
  return 0;
}
