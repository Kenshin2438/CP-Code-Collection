#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

void solve() {
  int n, k; cin >> n >> k;
  string s; cin >> s;

  vector<int> p;
  for (int i = 0; i < n; i++) {
    if (s[i] == '1') p.push_back(i);
  }

  if (p.empty()) {
    vector<int> len;
    for (int pre = 0, i = 0; i < n; i++) {
      if (s[i] == '0') {
        len.push_back(i - pre), pre = i + 1;
      } else {
        if (i == n - 1) len.push_back(i - pre + 1);
      }
    }
    if (len.empty()) return cout << "No\n", void();
    else {
      int M = *max_element(all(len));
      int C = count(all(len), M);
      if (M == k && C == 1) cout << "Yes\n";
      else cout << "No\n";
    }
  } else {
    int l = p.front(), r = p.back();
    bool ok = true;
    for (int i = l; i <= r; i++) {
      if (s[i] == '0') ok = false;
    }
    if (ok == false) return cout << "No\n", void();
    int cl = 0, cr = 0;
    while (l - cl - 1 >= 0 && s[l - cl - 1] == '?') cl++;
    while (r + cr + 1 <  n && s[r + cr + 1] == '?') cr++;
    int L = r - l + 1, R = L + cl + cr;
    if (k >= L && k <= R) {
      if (k == L || k == R || (cl == 0 || cr == 0)) cout << "Yes\n";
      else cout << "No\n";
    } else {
      cout << "No\n";
    }
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  cin >> T;
  while (T--) solve();

  return 0;
}
