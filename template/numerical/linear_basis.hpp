// 实数线性基
// https://hydro.ac/d/bzoj/p/4004

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
// http://acm.hdu.edu.cn/showproblem.php?pid=3949
// https://hydro.ac/d/bzoj/p/2844
// https://loj.ac/p/114
// https://www.luogu.com.cn/problem/P3857
// https://www.luogu.com.cn/problem/P4570

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

// bitset<> 异或线性基
// https://codeforces.com/gym/102920/problem/J
// https://loj.ac/p/6243 (light chasing)

template <size_t N> struct Basis {
  vector<bitset<N>> B, path;
  int sz = 0;

  Basis(int n) : B(n), path(n) {};

  void insert(bitset<N> v, int id) {
    bitset<N> cur; cur.set(id);
    for (int i = B.size() - 1; i >= 0; i--) {
      if (v.test(i) == false) continue;
      if (B[i].test(i)) {
        v ^= B[i], cur ^= path[i];
      } else {
        for (int j = i - 1; j >= 0; j--)
          if (v.test(j)) v ^= B[j], cur ^= path[j];
        for (int j = i + 1; j < (int) B.size(); j++)
          if (B[j].test(i)) B[j] ^= v, path[j] ^= cur;
        B[i] = v, path[i] = cur, sz += 1;
        return;
      }
    }
  }
  int size() { return sz; }
  pair<bool, bitset<N>> solver(bitset<N> x) {
    // find path
    bitset<N> res;
    for (int i = B.size() - 1; i >= 0; i--) {
      if (x.test(i)) {
        if (B[i].test(i)) {
          x ^= B[i];
          res ^= path[i];
        } else {
          return {false, res};
        }
      }
    }
    return {true, res};
  }
};
