struct R {
  ll a, p, x, y;

  R(ll _a, ll _p) : a(_a), p(_p) { x = 1LL, y = 0LL; }
  void rand() {
    x = randint(0, p - 1);
    y = randint(0, p - 1);
  }
  R &operator*=(const R &rhs) {
    ll _x = (x * rhs.x + y * rhs.y % p * a) % p;
    ll _y = (x * rhs.y + y * rhs.x) % p;
    x = _x, y = _y;
    return *this;
  }

  void pow(ll n) {
    R res(a, p), b = *this;
    for (; n; n >>= 1, b *= b) {
      if (n & 1LL) res *= b;
    }
    x = res.x, y = res.y;
  }
};

ll Cipolla(ll a, ll p) {
  a = (a % p + p) % p;
  if (a == 0) return 0LL;
  // No Solution
  if (qpow(a, (p - 1) / 2, p) != 1LL) return -1LL;  
  if (p % 4 == 3) return qpow(a, (p + 1) / 4, p);

  R t(a, p);
  while (true) {
    t.rand(), t.pow((p - 1) / 2);
    if (t.x == 0 && t.y != 0) {
      return qpow(t.y, p - 2, p);
    }
  }

  assert(false);
  return -1;
}