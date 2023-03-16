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

template <typename T> 
std::pair<T, T> exgcd(T a, T b) {
  if (b == 0) return {1, 0};
  const auto &[y, x] = exgcd(b, a % b);
  return {x, y - (a / b) * x}; 
}

void solve() {
  vector<array<ll, 2>> ps(3);
  for (auto &&[a, b] : ps) {
    cin >> a >> b;
    assert(abs(a) >= 0 && abs(a) <= (int) 1e6);
    assert(abs(b) >= 0 && abs(b) <= (int) 1e6);
    assert(abs(a) + abs(b) > 0);
  }
  auto & x = ps[0], y = ps[1], z = ps[2];
  if (x[0] == 0) { 
    swap(x[0], x[1]); 
    swap(y[0], y[1]);
    swap(z[0], z[1]);
  }

  ll L = y[1] * x[0] - y[0] * x[1];
  ll R = z[1] * x[0] - z[0] * x[1];

  if (L == 0) {
    if (R != 0) return cout << "NO\n", void();
    const auto &[a, b] = exgcd(x[0], y[0]);
    const auto &g = __gcd(x[0], y[0]);
    if (z[0] % g != 0) return cout << "NO\n", void();
    cout << "YES\n" << z[0] / g * a << " " << z[0] / g * b << "\n";
  } else {
    if (R % L != 0) return cout << "NO\n", void();
    ll b = R / L;
    if ((z[0] - b * y[0]) % x[0] != 0) return cout << "NO\n", void();
    ll a = (z[0] - y[0] * b) / x[0];
    cout << "YES\n" << a << " " << b << "\n";
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  cin >> T;
  assert(1 <= T && T <= (int) 1e5);
  while (T--) solve();

  return 0;
}