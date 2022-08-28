const int MAXM = 50050;
const int Z = (MAXM >> 8) + 2;
struct BS {
  __m256i a[MAXM / 256 + 2];
  BS() {}
  void operator^=(const BS &b) {
    for (int i = 0; i < Z; i++) a[i] = _mm256_xor_si256(a[i], b.a[i]);
  }
  void operator|=(const BS &b) {
    for (int i = 0; i < Z; i++) a[i] = _mm256_or_si256(a[i], b.a[i]);
  }
  void reset() {
    __m256i nul = _mm256_setzero_si256();

    for (int i = 0; i < Z; i++) a[i] = nul;
  }
  BS operator&(const BS &b) const {
    BS ret;

    for (int i = 0; i < Z; ++i) ret.a[i] = _mm256_and_si256(a[i], b.a[i]);

    return ret;
  }
  BS operator~() const {
    BS ret;
    __m256i nul = _mm256_setzero_si256();

    for (int i = 0; i < 4; ++i) ((ull *)(&nul))[i] = ~0ull;

    for (int i = 0; i < Z; ++i) ret.a[i] = _mm256_xor_si256(a[i], nul);

    return ret;
  }
  int getnxt(int id) const {
    ull *mcfx = (ull *)&a[id];

    for (int i = 0; i < 4; ++i)
      if (mcfx[i]) return (i << 6) + __builtin_ctzll(mcfx[i]);

    return -1;
  }
  void xr1(int x) { ((ull *)(&a))[x >> 6] ^= 1ull << (x & 63); }
  void or1(int x) { ((ull *)(&a))[x >> 6] |= 1ull << (x & 63); }
  int _Find_next(int pos) {
    __m256i nul = _mm256_setzero_si256();

    for (int i = 0; i < 4; ++i) ((ull *)(&nul))[i] = ~0ull;

    int nxt = -1;

    for (int i = (pos >> 8); i < Z; i++)
      if (!_mm256_testz_si256(a[i], nul)) {
        nxt = (i << 8) + getnxt(i);
        break;
      }

    if (nxt == -1)
      return MAXM + 10;
    else
      return xr1(nxt), nxt;
  }
};
