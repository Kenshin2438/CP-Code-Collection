#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

void solve() {
  static constexpr int N = 2e5 + 10;
  static char s[N];

  cin >> (s + 1);
  int n = strlen(s + 1);
  array<ll, N> Lu{}, Lud{};
  array<ll, N> Ru{}, Rud{};

  for (int i = 1; i <= n; i++) {
    Lu[i] = Lu[i - 1] + (s[i] == 'u');
    Lud[i] = Lud[i - 1] + (s[i] == 'd') * Lu[i - 1];
  }
  for (int i = n; i >= 1; i--) {
    Ru[i] = Ru[i + 1] + (s[i] == 'u');
    Rud[i] = Rud[i + 1] + (s[i] == 'd') * Ru[i + 1];
  }
  
  vector<ll> ans(N);
  for (int i = 1; i <= n; i++) {
    if (s[i] == 'u') {
      ans[i] = Lud[i - 1] + Rud[i + 1];
    } else if (s[i] == 'd') {
      ans[i] = Lu[i - 1] * Ru[i + 1];
    }
  }
  int pos = max_element(all(ans)) - begin(ans);
  s[pos] = 'a';
  cout << s + 1 << '\n';
} 

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}