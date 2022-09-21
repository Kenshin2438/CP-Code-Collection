using ull = unsigned long long;
template<ull base> struct Hash {
  vector<ull> H, pw;

  Hash(const string &s = "") {
    H.emplace_back(0ULL);
    pw.emplace_back(1ULL);
    for (const char &c : s) {
      H.emplace_back(H.back() * base + c);
      pw.emplace_back(pw.back() * base);
    }
  }

  ull query(int l, int r) { // [l, r)
    return H[r] - H[l] * pw[r - l];
  }
};
using H = Hash<(ull) 1e11 + 3>;
