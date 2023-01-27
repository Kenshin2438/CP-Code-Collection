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

using ull = unsigned long long;
ull modmul(ull a, ull b, ull M) {
  ll ret = a * b - M * ull(1.L / M * a * b);
  return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull modpow(ull b, ull e, ull mod) {
  ull ans = 1;
  for (; e; b = modmul(b, b, mod), e /= 2)
    if (e & 1) ans = modmul(ans, b, mod);
  return ans;
}

void solve() {
  vector<ll> a;
  string _; cin >> _;
  ll num = 0; char c;
  for (const char &c : _) {
    if (c == '?' || c == '=') {
      a.emplace_back(num), num = 0;
    } else {
      num = num * 10 + (c - '0');
    }
  }
  debug(a, num);
  
  int n = sz(a) - 1;
  for (int s = 0; s < modpow(3, n, 531441 + 114514); s++) {
    vector<int> ops(n);
    for (int tmp = s, i = 0; i < n; i++) {
      ops[i] = tmp % 3, tmp /= 3;
    }
    debug(ops);
    ll val = a[0];
    for (int i = 0; i < n; i++) {
      if (ops[i] == 0) {
        val = val + a[i + 1];
      } else if (ops[i] == 1) {
        val = val - a[i + 1];
      } else {
        if (val > 0 && a[i + 1] > 0) {
          val = modpow(val, val, a[i + 1]);
        } else {
          val = -1; break;
        }
      }
    }
    if (val == num) {
      cout << a[0];
      for (int i = 0; i < n; i++) {
        if (ops[i] == 0) cout << "+";
        else if (ops[i] == 1) cout << "-";
        else cout << "#";

        cout << a[i + 1];
      }
      cout << "=" << num << "\n";
      return;
    }
  }
  cout << -1 << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}