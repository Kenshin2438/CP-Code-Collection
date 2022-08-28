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

using ull = unsigned long long;

#include <bits/extc++.h>
const int SEED = chrono::steady_clock::now().time_since_epoch().count();
struct chash {  // To use most bits rather than just the lowest ones:
  const ull C = ll(4e18 * acos(0)) | 71;  // large odd number
  ll operator()(ll x) const { return __builtin_bswap64((x ^ SEED) * C); }
};
using HashMap = __gnu_pbds::gp_hash_table<ll, int, chash>;

ull splitmix64(ull x) {
  // http://xorshift.di.unimi.it/splitmix64.c
  x += 0x9e3779b97f4a7c15;
  x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
  x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
  return x ^ (x >> 31);
}

const int N = 1e5 + 10;

bitset<N> ntp;
vector<int> p;
void init() {
  for (int i = 2; i < N; i++) {
    if (ntp.test(i) == false)
      p.push_back(i);
    for (const int &pr : p) {
      if (pr * 1LL * i >= N) break;
      ntp.set(pr * i);
      if (i % pr == 0) break;
    }
  }
}

int S, tot, B[N], idx[2][N], H[N];

int PI(int T) {
  return H[T <= S ? idx[0][T] : idx[1][B[0] / T]];
}

void min25(int n) {
  S = sqrt(n), B[tot = 0] = n;
  for (int l = 1, r; l <= n; l = r + 1) {
    r = n / (B[++tot] = n / l);
    H[tot] = B[tot] - 1;
    B[tot] <= S ? idx[0][B[tot]] = tot : idx[1][B[0] / B[tot]] = tot;
  }
  for (int i = 0; i < sz(p) && p[i] <= S; i++) {
    for (int j = 1; j <= tot && p[i] <= B[j] / p[i]; j++) {
      H[j] = H[j] + i - PI(B[j] / p[i]);
    }
  }
}

int qpow(int x, int n) {
  int res = 1;
  for (; n; n >>= 1, x *= x) if (n & 1) res *= x;
  return res;
}

int M, K;

HashMap SM;
int G(int n, int id) {
  if (n <= p[id + 1]) return 0U;
  if (SM.find(splitmix64(id) * n) != end(SM)) {
    return SM[splitmix64(id) * n];
  }
  int res = 0;
  for (int i = id + 1; p[i] <= n / p[i]; i++) {
    int val = qpow(p[i], K);
    for (ll pe = p[i], e = 1; pe <= n; pe *= p[i], e++) {
      int pi = PI(n / pe);
      if (pi >= i + 1) res += val * (pi - i - 1);
      res += G(n / pe, i) + int(e > 1) * val;
    }
  }
  return SM[splitmix64(id) * n] = res;
}

HashMap F;
int sieve(int n) {
  if (F.find(n) != end(F)) return F[n];
  int res = G(n, -1) + PI(n);
  for (int l = 2, r; l <= n; l = r + 1) {
    r = n / (n / l);
    res -= sieve(n / l) * (r - l + 1);
  }
  return F[n] = res;
}

void solve() {
  cin >> M >> K;
  min25(M);

  const ll mod = (1LL << 32) - 1;

  int ans = 0;
  for (int l = 1, r, bn; l <= M; l = r + 1) {
    r = M / (bn = M / l);
    ans += (sieve(r) - sieve(l - 1)) * bn * bn;
  }
  cout << (ans & mod) << '\n';
}

signed main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  init();

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
