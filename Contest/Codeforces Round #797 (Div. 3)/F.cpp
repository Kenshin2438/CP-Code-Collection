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

void SingleTest(__attribute__((unused)) int TestCase) {
  int n; cin >> n;
  str s; cin >> s;

  vec<int> p(n);
  for (int &x : p) cin >> x, --x;

  vec<bool> vis(n, false);
  ll ans = 1LL;
  for (int i = 0; i < n; i++) {
    if (vis[i]) continue;

    str t = "";
    int cur = i;
    do {
      vis[cur] = true;
      t += s[cur], cur = p[cur];
    } while (cur != i);

    // const auto KMP = [](const str &s, const str &pat) {
    //   str t = pat + '\0' + s;
    //   vec<int> p(t.size(), 0);
    //   for (size_t i = 1; i < t.size(); i++) {
    //     int g = p[i - 1];
    //     while (g && t[i] != t[g]) g = p[g - 1];
    //     p[i] = g + (t[i] == t[g]);
    //   }
    //   for (size_t i = t.size() - s.size(); i < t.size(); i++) {
    //     if (p[i] == (int) pat.size()) return int(i - 2 * pat.size());
    //   }
    //   return -1;
    // };

    const auto KMP = [](const str &s) {
      int n = s.length();
      vec<int> p(n, 0);
      for (int i = 1; i < n; i++) {
        int g = p[i - 1];
        while (g && s[i] != s[g]) g = p[g - 1];
        p[i] = g + (s[i] == s[g]);
      }
      if (n % (n - p.back()) == 0) return n - p.back();
      return n;
    };

    // ll num = KMP(t.substr(1) + t) + 1;
    
    ll num = KMP(t);

    debug(t, num);

    ans = ans / __gcd(ans, num) * num;
  }
  cout << ans << '\n';
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
