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

template <uint32_t mod> struct m32 {
  static_assert(mod < (1U << 31), "Modulus error!");

  using u32 = uint32_t;
  using u64 = uint64_t;
  using i64 = int64_t;

  u32 v = 0;
  template <typename T> u32 norm(T v) {
    return static_cast<u32>((v %= mod) < 0 ? mod + v : v);
  }
  m32() = default;
  template <typename T> m32(T _ = 0) : v(norm(_)) {}
  ~m32() = default;

  m32 &operator=(const int &rhs) { return v = norm(rhs), *this; }
  m32 operator-() const {
    return v == 0 ? m32(0) : m32(mod - v);
  }
  m32 &operator+=(const m32 &rhs) {
    v += rhs.v;
    if (v >= mod) v -= mod;
    return *this;
  }
  m32 &operator-=(const m32 &rhs) {
    if (v < rhs.v) v += mod;
    v -= rhs.v;
    return *this;
  }
  m32 &operator*=(const m32 &rhs) {
    v = (u64)v * rhs.v % mod;
    return *this;
  }
  m32 &operator/=(const m32 &rhs) { return *this *= rhs.inv(); }
  m32 operator+(const m32 &rhs) const { return m32(*this) += rhs; }
  m32 operator-(const m32 &rhs) const { return m32(*this) -= rhs; }
  m32 operator*(const m32 &rhs) const { return m32(*this) *= rhs; }
  m32 operator/(const m32 &rhs) const { return m32(*this) /= rhs; }
  bool operator==(const m32 &rhs) const { return rhs.v == v; }
  bool operator!=(const m32 &rhs) const { return rhs.v != v; }
  m32 pow(i64 n) const {
    m32 x(*this), res(1);
    for (; n > 0; n >>= 1, x *= x)
      if (n & 1LL) res *= x;
    return res;
  }
  m32 inv() const {
    assert(v != 0);
    return pow(mod - 2);
  }

  static u32 get_mod() { return mod; }
  friend ostream &operator<<(ostream &os, const m32 &m) {
    return os << m.v;
  }
  friend istream &operator>>(istream &is, m32 &m) {
    long long a; is >> a; m = m32<mod>(a);
    return is;
  }
};

const int mod = 1e9 + 7;
using mint = m32<mod>;

// void solve() {
//   int k; cin >> k;
//   vector<mint> E(6, mint(0)); 
//   // r    0
//   // re   1
//   // red  2
//   // e    3
//   // ed   4
//   // d    5
//   for (int i = 1; i <= k; i++) {
//     vector<mint> nE(6, mint(0)); 
//     { // option 1   red
//       nE[0] += E[0] + 1;
//       nE[1] += E[1] + 1 + E[0];
//       nE[2] += E[2] + 1 + E[1] + E[0];
//       nE[3] += E[3] + 1;
//       nE[4] += E[4] + 1 + E[3];
//       nE[5] += E[5] + 1;
//     }
//     { // option 2   edr
//       nE[0] += E[0] + 1;
//       nE[1] += E[1] + E[0];
//       nE[2] += E[2] + E[1] + E[0]; 
//       nE[3] += E[3] + 1;
//       nE[4] += E[4] + 1 + E[3];
//       nE[5] += E[5] + 1;
//     }
//     { // option 3
//       vector<mint> pre = E;
//       for (int _ = 0; _ < 9; _++) {
//         vector<mint> aft(6, mint(0)); 
//         aft[0] = pre[0] + E[0];
//         aft[1] = pre[1] + E[1] + pre[0] * E[3];
//         aft[2] = pre[2] + E[2] + pre[0] * E[4] + pre[1] * E[5];
//         aft[3] = pre[3] + E[3];
//         aft[4] = pre[4] + E[4] + pre[3] * E[5];
//         aft[5] = pre[5] + E[5];
//         pre = aft;
//       }
//       for (int i = 0; i < 6; i++) nE[i] += pre[i];
//     }
//     for (int i = 0; i < 6; i++) nE[i] /= 3;
//     E = nE;
//   }
//   cout << E[2] << '\n';
// }

string to_string(const mint &m) { return to_string(m.v); }

namespace LinearRecurrence {
using Poly = vector<mint>;
mint linearRec(Poly S, Poly tr, ll k) {
	int n = sz(tr);
	auto combine = [&](Poly a, Poly b) {
		Poly res(n * 2 + 1);
		for (int i = 0; i <= n; i++) 
      for (int j = 0; j <= n; j++)
        res[i + j] += a[i] * b[j];
		for (int i = 2 * n; i > n; --i) 
      for (int j = 0; j < n; j++)
        res[i - 1 - j] += res[i] * tr[j];
		res.resize(n + 1);
		return res;
	};

	Poly pol(n + 1), e(pol);
	pol[0] = e[1] = 1;
	for (++k; k; k /= 2) {
		if (k % 2) pol = combine(pol, e);
		e = combine(e, e);
	}

	mint res = 0;
	for (int i = 0; i < n; i++) res += pol[i + 1] * S[i];
	return res;
}
vector<mint> berlekamp_massey(const vector<mint> &s) {
  int n = sz(s), L = 0, m = 0;
  vector<mint> C(n), B(n), T;
  C[0] = B[0] = 1;
  mint b = 1;
  for (int i = 0; i < n; i++) {
    m += 1;
    mint d = s[i];
    for (int j = 1; j <= L; j++) d += C[j] * s[i - j];
    if (d == 0) continue;
    T = C; mint coef = d / b;
    for (int j = m; j < n; j++) C[j] -= coef * B[j - m];
    if (2 * L > i) continue;
    L = i + 1 - L; B = T; b = d; m = 0;
  }
  C.resize(L + 1); C.erase(C.begin());
  for (auto &&x : C) x = -x;
  return C;
}
mint get(vector<mint> a, ll k) {
  vector<mint> c = berlekamp_massey(a);
  debug(c);
  return linearRec(a, c, k);
}
};

void solve() {
  int k; cin >> k;
  vector<mint> a = {
    333333336,
    777777786,
    925925945,
    530864253,
    917695688,
    330590686,
    562874857,
    449639944,
    237263216,
    663950660,
    750322998,
    651539135
  };
  cout << LinearRecurrence::get(a, k - 1);
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}