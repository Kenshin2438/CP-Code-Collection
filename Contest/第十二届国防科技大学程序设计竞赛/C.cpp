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

/**

$$
\begin{aligned}
\mathrm{E}
&= \sum_{x=1}^{a} x\times \Pr x\\
&= \frac{a!\times b}{(a+b+c)!} \sum_{x=1}^{a}x\frac{(a+b+c-x-1)!}{(a-x)!} \\
&= \frac{a!\times b}{(a+b+c)!} \left(\sum_{x=1}^{a}a\frac{(a+b+c-x-1)!}{(a-x)!}-\sum_{x=1}^{a}(a-x)\frac{(a+b+c-x-1)!}{(a-x)!}\right)\\
&= \frac{a!\times b}{(a+b+c)!} \left(a\sum_{x=0}^{a-1}\frac{(x+b+c-1)!}{x!} - \sum_{x=0}^{a-2}\frac{(x+b+c)!}{x!} \right) \\
&= \frac{a!\times b}{(a+b+c)!} \left(a\frac{(b+c-1+a)!}{(b+c)\times (a-1)!} - \frac{(b+c+a-1)!}{(b+c+1)\times(a-2)!}\right) \\
&= \frac{a!\times b}{(a+b+c)!}\times\frac{(a+b+c-1)!}{(a-1)!} \left(\frac{a}{b+c}-\frac{a-1}{b+c-1}\right)\\
&= \frac{a\times b}{a+b+c} \left(\frac{a}{b+c} - \frac{a-1}{b+c+1}\right) \\
&= \frac{ab}{(b+c)(b+c+1)}
\end{aligned}
$$

**/

template <typename T> pair<T, T> exgcd(T a, T b) {
  bool nega = (a < 0), negb = (b < 0);
  T x = 1, y = 0;
  T r = 0, s = 1, t = 0;
  while (b) {
    r ^= x ^= r ^= x -= (t = a / b) * r;
    s ^= y ^= s ^= y -= t * s;
    b ^= a ^= b ^= a %= b;
  }
  return {nega ? -x : x, negb ? -y : y};
}

template<typename T> T inv(T a, T mod) {
  auto [res, _] = exgcd<T>(a, mod);
  return (res % mod + mod) % mod;
}

void SingleTest(__attribute__((unused)) int TestCase) {
  const int mod = (int) 1e9 + 7;
  ll a, b, c; cin >> a >> b >> c;
  if (b == 0 && c == 0) return cout << a % mod << '\n', void();
  if (b == 0 && c != 0) return cout << 0 << '\n', void();
  ll ans = a * b % mod * inv<ll>(b + c, mod) % mod * inv<ll>(b + c + 1, mod) % mod;
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
