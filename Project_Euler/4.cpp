#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int ans = 0;
  for (int i = 999; i >= 100; i--) {
    for (int j = i; j >= 100; j--) {
      string s = to_string(i * j);
      int l = 0, r = s.length() - 1;
      while (l <= r) {
        if (s[l] == s[r]) l++, r--;
        else break;
      }
      if (l >= r) ans = max(ans, i * j);
    }
  }
  cout << ans << '\n';
  return 0;
}