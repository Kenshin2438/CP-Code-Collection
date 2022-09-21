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