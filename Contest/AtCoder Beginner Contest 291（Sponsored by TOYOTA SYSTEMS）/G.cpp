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

namespace FastFourierTransform {
using real = long double;

struct C {
  real x, y;
  C() : x(0), y(0) {}
  C(real x, real y) : x(x), y(y) {}
  inline C operator+(const C &c) const { return C(x + c.x, y + c.y); }
  inline C operator-(const C &c) const { return C(x - c.x, y - c.y); }
  inline C operator*(const C &c) const {
    return C(x * c.x - y * c.y, x * c.y + y * c.x);
  }
  inline C conj() const { return C(x, -y); }
};

const real PI = acosl(-1);
int base = 1;
vector<C> rts = {{0, 0}, {1, 0}};
vector<int> rev = {0, 1};

void ensure_base(int nbase) {
  if (nbase <= base) return;
  rev.resize(1 << nbase);
  rts.resize(1 << nbase);
  for (int i = 0; i < (1 << nbase); i++) {
    rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
  }
  while (base < nbase) {
    real angle = PI * 2.0 / (1 << (base + 1));
    for (int i = 1 << (base - 1); i < (1 << base); i++) {
      rts[i << 1] = rts[i];
      real angle_i = angle * (2 * i + 1 - (1 << base));
      rts[(i << 1) + 1] = C(cos(angle_i), sin(angle_i));
    }
    ++base;
  }
}

void fft(vector<C> &a, int n) {
  assert((n & (n - 1)) == 0);
  int zeros = __builtin_ctz(n);
  ensure_base(zeros);
  int shift = base - zeros;
  for (int i = 0; i < n; i++) {
    if (i < (rev[i] >> shift)) {
      swap(a[i], a[rev[i] >> shift]);
    }
  }
  for (int k = 1; k < n; k <<= 1) {
    for (int i = 0; i < n; i += 2 * k) {
      for (int j = 0; j < k; j++) {
        C z = a[i + j + k] * rts[j + k];
        a[i + j + k] = a[i + j] - z;
        a[i + j] = a[i + j] + z;
      }
    }
  }
}

vector<int64_t> multiply(const vector<int> &a, const vector<int> &b) {
  int need = (int)a.size() + (int)b.size() - 1;
  int nbase = 1;
  while ((1 << nbase) < need) nbase++;
  ensure_base(nbase);
  int sz = 1 << nbase;
  vector<C> fa(sz);
  for (int i = 0; i < sz; i++) {
    int x = (i < (int)a.size() ? a[i] : 0);
    int y = (i < (int)b.size() ? b[i] : 0);
    fa[i] = C(x, y);
  }
  fft(fa, sz);
  C r(0, -0.25 / (sz >> 1)), s(0, 1), t(0.5, 0);
  for (int i = 0; i <= (sz >> 1); i++) {
    int j = (sz - i) & (sz - 1);
    C z = (fa[j] * fa[j] - (fa[i] * fa[i]).conj()) * r;
    fa[j] = (fa[i] * fa[i] - (fa[j] * fa[j]).conj()) * r;
    fa[i] = z;
  }
  for (int i = 0; i < (sz >> 1); i++) {
    C A0 = (fa[i] + fa[i + (sz >> 1)]) * t;
    C A1 = (fa[i] - fa[i + (sz >> 1)]) * t * rts[(sz >> 1) + i];
    fa[i] = A0 + A1 * s;
  }
  fft(fa, sz >> 1);
  vector<int64_t> ret(need);
  for (int i = 0; i < need; i++) {
    ret[i] = llround(i & 1 ? fa[i >> 1].y : fa[i >> 1].x);
  }
  return ret;
}
};  // namespace FastFourierTransform

void solve() {
  int n; cin >> n;
  vector<vector<int>> a(5, vector<int>(n));
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    for (int j = 0; j < 5; j++) {
      a[j][i] = x >> j & 1;
    }
  }
  vector<vector<int>> b(5, vector<int>(n));
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    for (int j = 0; j < 5; j++) {
      b[j][i] = x >> j & 1;
    }
  }

  vector<int> S(5);
  for (int i = 0; i < 5; i++) {
    S[i] = accumulate(all(a[i]), 0) + accumulate(all(b[i]), 0);
  }

  for (auto &v : a) reverse(all(v));
  vector<vector<int>> B(5, vector<int>(2 * n)), A = a;
  for (int j = 0; j < 5; j++){
    for (int i = 0; i < n; i++) {
      B[j][i] = B[j][i + n] = b[j][i];
    }
  }

  vector<vector<int64_t>> conv(5);
  for (int i = 0; i < 5; i++) {
    conv[i] = FastFourierTransform::multiply(A[i], B[i]);
  }

  ll ans = 0;
  for (int i = n - 1; i < 2 * n - 1; i++) {
    ll tmp = 0;
    for (int j = 0; j < 5; j++) {
      tmp += (1 << j) * (S[j] - conv[j][i]);
    }
    ans = max(ans, tmp);
  }
  cout << ans << "\n";
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}