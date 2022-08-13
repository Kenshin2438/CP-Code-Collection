#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxn = 5e6;

int pr[maxn], cnt;
bitset<maxn + 5> ok;
ll phi[maxn + 5];
int mu[maxn + 5];

unordered_map<int, pair<ll, ll> > spm;

void func(int n) {
  mu[1] = phi[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (!ok[i]) pr[++cnt] = i, phi[i] = i - 1, mu[i] = -1;
    for (int j = 1; j <= cnt && pr[j] <= n / i; j++) {
      ok[pr[j] * i] = 1;
      if (i % pr[j] == 0) {
        phi[pr[j] * i] = phi[i] * pr[j];
        break;
      } else {
        phi[pr[j] * i] = phi[pr[j]] * phi[i];
        mu[pr[j] * i] = -mu[i];
      }
    }
  }
  for (int i = 1; i <= n; i++) phi[i] += phi[i - 1], mu[i] += mu[i - 1];
}

inline void slove(ll n, ll& ans1, ll& ans2) {
  if (n <= maxn) {
    ans1 = phi[n], ans2 = mu[n];
    return;
  }
  if (spm.count(n)) {
    ans1 = spm[n].first, ans2 = spm[n].second;
    return;
  }
  ans1 = 1LL * n * (n + 1) >> 1LL, ans2 = 1LL;
  for (ll l = 2, r; l <= n; l = r + 1) {
    r = n / (n / l);
    ll a, b;
    slove(n / l, a, b);
    ans1 -= a * (r - l + 1), ans2 -= b * (r - l + 1);
  }
  spm[n] = {ans1, ans2};
}

int main() {
  func(maxn);
  ll n, _, ans1, ans2;
  scanf("%lld", &n);
  slove(n - 1, _, ans1);
  scanf("%lld", &n);
  slove(n, _, ans2);
  printf("%lld\n", ans2 - ans1);
  return 0;
}
