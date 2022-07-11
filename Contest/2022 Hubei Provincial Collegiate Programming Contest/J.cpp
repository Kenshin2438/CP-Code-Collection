#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

#define PII pair<int, int>
#define vec vector
#define str string
#define fi first
#define se second
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define sz(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

using ull = unsigned long long;

void SingleTest(__attribute__((unused)) int TestCase) {
  str s; cin >> s;
  int n = sz(s), pre = 0;

  {
    int l = 0, r = n - 1;
    while (l <= r && s[l] == s[r]) ++l, --r;
    if (l >= r) return cout << "1 1\n", void();
    pre = l, n = r - l + 1; 
    s = s.substr(pre, n);
    debug(pre, s);
  }

  s = "#" + s; // 1-indexed;
  const ull BASE = 131ULL;
  vec<ull> H(n + 2), rH(n + 2), B(n + 1, 1ULL);
  for (int i = 1; i <= n; i++) B[i] = B[i - 1] * BASE;
  for (int i = 1; i <= n; i++) {
     H[i] =  H[i - 1] * BASE + s[i];
  }
  for (int i = n; i >= 1; i--) {
    rH[i] = rH[i + 1] * BASE + s[i];
  }
  auto Hash = [&](int l, int r) -> ull {
    return  H[r] -  H[l - 1] * B[r - l + 1];
  };
  auto rHash = [&](int l, int r) -> ull {
    return rH[l] - rH[r + 1] * B[r - l + 1];
  };
  auto check = [&](int l, int r) -> bool {
    ull PreHash = Hash(1, l - 1) * B[n - l + 1] + rHash(l, r) * B[n - r] + Hash(r + 1, n);
    ull SufHash = rHash(1, l - 1) + Hash(l, r) * B[l - 1] + rHash(r + 1, n) * B[r];
    return PreHash == SufHash;
  };
  for (int i = 1; i <= n; i++) {
    if (check(1, i)) {
      return cout << pre + 1 << ' ' << pre + i << '\n', void();
    }
    if (check(i, n)) {
      return cout << pre + i << ' ' << pre + n << '\n', void();
    }
  }
  cout << "-1 -1" << '\n';
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  // cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}