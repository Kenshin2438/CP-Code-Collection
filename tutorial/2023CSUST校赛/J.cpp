#include <bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O3,unroll-loops")

struct BitSet {
  using u64 = unsigned long long;
  vector<u64> a;
  size_t N;

  static u64 maskbit(size_t pos) { return 1uLL << pos; }

  struct ref {
    u64 *p;
    size_t pos;
    ref(BitSet &b, size_t _pos) {
      p = b.a.data() + _pos / 64;
      pos = _pos % 64;
    }
    operator bool() const { return (*p & maskbit(pos)) != 0; }
    bool operator~() const { return (*p & maskbit(pos)) == 0; }
    ref &flip() {
      *p ^= maskbit(pos);
      return *this;
    }
    ref &operator=(bool x) {
      if (x) {
        *p |= maskbit(pos);
      } else {
        *p &= ~maskbit(pos);
      }
      return *this;
    }
    ref &operator=(const ref &r) { return *this = bool(r); }
  };

  BitSet(size_t _N) : a((_N + 63) / 64, 0), N(_N) {}

  ref operator[](size_t pos) { return ref(*this, pos); }
  bool operator[](size_t pos) const {
    return (a[pos / 64] & maskbit(pos % 64)) != 0;
  }
  bool test(size_t pos) const { return (a[pos / 64] & maskbit(pos % 64)) != 0; }
  void set(size_t pos) { a[pos / 64] |= maskbit(pos % 64); }
  void reset(size_t pos) { a[pos / 64] &= ~maskbit(pos % 64); }
  void flip(size_t pos) { a[pos / 64] ^= maskbit(pos % 64); }
  size_t size() const { return N; }

  __attribute__((optimize("O3,unroll-loops"))) BitSet &operator^=(const BitSet &r) {
    assert(a.size() == r.a.size());
    for (size_t i = 0; i < a.size(); i++) a[i] ^= r.a[i];
    return *this;
  }

  __attribute__((optimize("O3,unroll-loops"))) int _Find_next(size_t i) const {
    ++i;
    if (i >= N) return N;
    size_t M = i / 64;
    u64 buf = a[M];
    buf &= ~u64(0) << (i % 64);
    if (buf != 0) return M * 64 + __builtin_ctzll(buf);
    for (; ++M < a.size();) {
      if (a[M] != 0) return M * 64 + __builtin_ctzll(a[M]);
    }
    return N;
  }
  int _Find_first() const { return _Find_next(-1); }

  __attribute__((optimize("O3,unroll-loops"))) int _Find_prev(size_t i) const {
    if (i == 0) return -1;
    if ((*this)[--i] == true) return i;
    size_t M = i / 64;
    u64 buf = a[M];
    buf &= maskbit(i % 64) - 1;
    if (buf != 0) return M * 64 + 63 - __builtin_clzll(buf);
    while (M--) {
      if (a[M] != 0) return M * 64 + 63 - __builtin_clzll(a[M]);
    }
    return -1;
  }
  int _Find_last() const { return _Find_prev(N); }
};

void solve() {
  int n, q; cin >> n >> q;
  assert(1 <= n && n <= (int) 1E5);
  assert(1 <= q && q <= (int) 1E5);
  vector<int> a(n);
  for (int &x : a) {
    cin >> x;
    assert(1 <= x && x <= (int) 1E9);
  }

  auto t = a; sort(begin(t), end(t));
  t.erase(unique(begin(t), end(t)), end(t));
  for (int &x : a) {
    x = distance(begin(t), lower_bound(begin(t), end(t), x));
  }

  using BS = BitSet;
  const int M = (int) t.size();

  const int BLOCK = 325;
  vector<int> pos(n);
  vector<BS> B((n - 1) / BLOCK + 1, BS(M));
  for (int i = 0; i < n; i++) B[pos[i] = i / BLOCK].flip(a[i]);
  for (int i = 1; i < (int) B.size(); i++) B[i] ^= B[i - 1];

  int ans = 0;
  for (int l, r; q--;) {
    cin >> l >> r;
    l = (l ^ ans) - 1;
    r = (r ^ ans) - 1;
    assert(l <= r && l >= 0 && r < n);
  
    int p = -1;
    if (r - l + 1 <= BLOCK) {
      BS bf(M);
      for (int i = l; i <= r; i++) bf.flip(a[i]); 
      p = bf._Find_first();
    } else {
      auto L = B[pos[l]], R = B[pos[r]];
      for (int i =     l; i < n && pos[i] == pos[l]; i++) L.flip(a[i]);
      for (int i = r + 1; i < n && pos[i] == pos[r]; i++) R.flip(a[i]);
      L ^= R;
      p = L._Find_first();
    }
    cout << (ans = p == M ? 0 : t[p]) << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}