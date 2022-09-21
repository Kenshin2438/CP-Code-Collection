template <typename T> pair<T, T> exgcd(T a, T b) {
  bool nega = (a < 0), negb = (b < 0);
  T x = 1, y = 0, r = 0, s = 1;
  while (b) {
    T t = a / b;
    r ^= x ^= r ^= x -= t * r;
    s ^= y ^= s ^= y -= t * s;
    b ^= a ^= b ^= a %= b;
  }
  return {nega ? -x : x, negb ? -y : y};
}

template <typename T> T inv(T a, T mod) {
  auto [res, _] = exgcd<T>(a, mod);
  return (res % mod + mod) % mod;
}

int inv(int x, int mod) { // MOD prime, assert(x != 0)
  return x == 1 ? 1 : inv(mod % x, mod) * 1LL * (mod - mod / x) % mod;
}
