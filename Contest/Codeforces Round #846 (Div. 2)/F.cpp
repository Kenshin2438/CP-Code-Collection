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

static constexpr int N = 3e5;
bitset<N + 10> ntp;
vector<int> mu(N + 10);

void init() {
  mu[1] = 1;
  vector<int> p;
  for (int i = 2; i < N; i++) {
    if (ntp.test(i) == false) {
      mu[i] = -1;
      p.emplace_back(i);
    } 
    for (const int &pr : p) {
      if (pr * 1LL * i >= N) break;;
      ntp.set(pr * 1LL * i, true);
      if (i % pr == 0) break;
      mu[pr * 1LL * i] = -mu[i];
    }
  }
}

void solve() {
  init();

  int n; cin >> n;
  vector<int> cnt(N), s(N);
  for (int i = 0; i < n; i++) {
    int x; cin >> x; cnt[x] += 1;
  }
  partial_sum(all(cnt), begin(s));

  ll ans = 0;
  for (int d = 1; d <= N; d++) {
    ll S = 0, pre = 0, pS = 0;
    for (int a = 1; a <= N / d; a++) {
      if (cnt[a * d] == 0) continue;
      S += s[a * d - 1] * pre - pS;
      pS += s[a * d], pre += 1;
    }
    ans += S * mu[d];
  }
  cout << ans << '\n';
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}