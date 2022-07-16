#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

const int N = 1e6 + 10;

int phi[N];

void init() {
  vector<int> p;

  phi[1] = 1;
  for (int i = 2; i < N; i++) {
    if (phi[i] == 0) {
      phi[i] = i - 1;
      p.emplace_back(i);
    }
    for (const int &pr : p) {
      if (pr * 1LL * i >= N) break;
      if (i % pr == 0) {
        phi[pr * i] = phi[i] * pr;
        break;
      } else {
        phi[pr * i] = phi[i] * (pr - 1);
      }
    }
  }
}

ll euler_qpow(ll x, ll n, ll mod) {
  ll res = 1, tag = 0;
  if (x >= mod) x %= mod, tag = 1;
  for (; n > 0LL; n >>= 1) {
    if (n & 1LL) {
      if ((res *= x) > mod) res %= mod, tag = 1;
    } 
    if ((x *= x) > mod) x %= mod, tag = 1;
  } 
  return res + mod * tag;
}

ll power(ll a, ll b, ll p) {
  if (b == 0) return 1LL;
  if (b == 1 || p == 1) {
    return (a > p) ? (a % p + p) : (a);
  }
  return euler_qpow(a, power(a, b - 1, phi[p]), p);
}

void solve() {
  int a, b, m; cin >> a >> b >> m;
  cout << power(a, b, m) % m << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  
  init();
  int T; cin >> T;
  while (T--) solve();

  return 0;
}