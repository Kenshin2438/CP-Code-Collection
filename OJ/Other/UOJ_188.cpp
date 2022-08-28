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

const int N = 1e6 + 10;

bitset<N> ntp;
vector<int> p;
void init() {
  for (int i = 2; i < N; i++) {
    if (ntp.test(i) == false) p.push_back(i);
    for (const int &pr : p) {
      if (pr * 1LL * i >= N) break;
      ntp.set(pr * i);
      if (i % pr == 0) break;
    }
  }
}

ll S, M, tot, idx[2][N], block[N], H[N];

ll prime_pi(ll T) {
  return H[T <= S ? idx[0][T] : idx[1][M / T]];
}

ll G(ll n, int id) {
  if (n <= p[id + 1]) return 0;
  ll res = 0;
  for (int i = id + 1; i < sz(p) && p[i] * 1LL * p[i] <= n; i++) {
    for (ll pe = p[i], e = 1; pe <= n; pe *= p[i], e++) {
      res += max(0LL, prime_pi(n / pe) - i - 1) * p[i];
      // res += calc(n / pe, i);
      res += G(n / pe, i) + (e > 1) * p[i];
    }
  }
  return res;
}

ll Min25(ll n) {
  M = n, S = sqrtl(M), tot = 0;
  for (ll l = 1, r; l <= M; l = r + 1) {
    r = M / (M / l);
    block[++tot] = M / l;
    H[tot] = block[tot] - 1;
    block[tot] <= S ? idx[0][block[tot]] = tot : idx[1][M / block[tot]] = tot;
  }
  for (int i = 0; i < sz(p) && p[i] <= S; i++) {
    for (int j = 1; j <= tot && p[i] <= block[j] / p[i]; j++) {
      ll T = block[j] / p[i];
      int pos = T <= S ? idx[0][T] : idx[1][M / T];
      H[j] = H[j] - H[pos] + i;
    }
  }
  return G(n, -1);
}

void solve() {
  ll l, r; cin >> l >> r;
  cout << Min25(r) - Min25(l - 1) << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  init();

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
