// 实数线性基

template<int mod = 998244353>
struct Basis {
  vector<vector<int>> B;

  Basis(int n) { B.resize(n, vector<int>(n)); }
  int inv(int x) {
    return x == 1 ? 1 : (mod - mod / x) * 1LL * inv(mod % x) % mod;
  }
  bool insert(vector<int> v) {
    for (int i = v.size() - 1; i >= 0; i--) {
      if (v[i] == 0) continue;
      if (B[i][i] == 0) {
        B[i] = v;
        return true;
      }
      int t = v[i] * 1LL * inv(B[i][i]) % mod;
      for (int j = i; j >= 0; j--) {
        v[j] = (v[j] - B[i][j] * 1LL * t % mod + mod) % mod;
      }
    }
    return false;
  }
};

// 异或线性基

template<typename T> struct Basis {
  vector<T> B;
  int sz = 0;
  bool free = false;

  Basis(int n) : B(n) {};
  void insert(T v) {
    for (int i = B.size() - 1; i >= 0; i--) {
      if ((v >> i & 1) == 0) continue;
      if (B[i]) v ^= B[i];
      else {
        for (int j = i - 1; j >= 0; j--)
          if (v >> j & 1) v ^= B[j];
        for (int j = i + 1; j < (int) B.size(); j++)
          if (B[j] >> i & 1) B[j] ^= v;
        B[i] = v, sz += 1;
        return;
      }
    }
    free = true;
  }
  T max() {
    T res = 0;
    for (int i = 0; i < (int) B.size(); i++) res ^= B[i];
    return res;
  }
  T kth(long long k) { // k start from 1-indexed
    if (free) k -= 1; // free -> 0
    if (k >= (1LL << sz)) return -1;
    T res = 0;
    for (int i = 0, t = 0; i < (int) B.size(); i++) {
      if (B[i] == 0) continue;
      if (k >> t & 1) res ^= B[i];
      t += 1;
    }
    return res;
  }
  long long rank(T v) { // rank start from 0-indexed
    long long res = 0;
    for (int i = 0, t = 0; i < (int) B.size(); i++) {
      if (B[i] == 0) continue;
      if (v >> i & 1) res |= 1LL << t;
      t += 1;
    }
    return res;
  }
  int size() { return sz; }
};
