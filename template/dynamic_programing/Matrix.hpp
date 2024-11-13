template <uint32_t mod>
struct LazyMontgomeryModInt {
  using i32 = int32_t;
  using u32 = uint32_t;
  using i64 = int64_t;
  using u64 = uint64_t;

  static constexpr u32 n2 = -u64(mod) % mod;
  static constexpr u32 r {[]() -> u32 {
    u32 res(mod);
    for (i32 i = 0; i < 4; i++) res *= 2 - mod * res;
    return res;
  }()};
  static_assert(r * mod == 1, "invalid, r * mod != 1");
  static_assert(mod < (1 << 30), "invalid, mod >= 2 ^ 30");

  static constexpr auto get_mod() -> u32 { return mod; }
  static constexpr auto reduce(const u64 &b) -> u32 {
    return u32((b + u64(u32(b) * u32(-r)) * mod) >> 32);
  }

  u32 val = 0U;
  constexpr LazyMontgomeryModInt(const i64 &b)
    : val(reduce(u64(b % mod + mod) * n2)) {}

  [[nodiscard]] constexpr auto get() const -> u32 {
    u32 res = reduce(val);
    return (res >= mod ? res - mod : res);
  }

  using mint = LazyMontgomeryModInt;
  constexpr auto operator+=(const mint &rhs) -> mint & {
    val += rhs.val - 2 * mod;
    if (i32(val) < 0) val += 2 * mod;
    return *this;
  }
  constexpr auto operator-=(const mint &rhs) -> mint & {
    val -= rhs.val;
    if (i32(val) < 0) val += 2 * mod;
    return *this;
  }
  constexpr auto operator*=(const mint &rhs) -> mint & {
    val = reduce(u64(val) * rhs.val);
    return *this;
  }
  constexpr auto operator/=(const mint &rhs) -> mint & {
    *this *= rhs.inverse();
    return *this;
  }
  constexpr auto operator+(const mint &rhs) const -> mint {
    return mint(*this) += rhs;
  }
  constexpr auto operator-(const mint &rhs) const -> mint {
    return mint(*this) -= rhs;
  }
  constexpr auto operator*(const mint &rhs) const -> mint {
    return mint(*this) *= rhs;
  }
  constexpr auto operator/(const mint &rhs) const -> mint {
    return mint(*this) /= rhs;
  }
  constexpr auto operator-() const -> mint { return mint() - mint(*this); }
  constexpr auto operator+() const -> mint { return mint(*this); }
  constexpr auto operator==(const mint &rhs) const -> bool {
    return (val >= mod ? val - mod : val) ==
           (rhs.val >= mod ? rhs.val - mod : rhs.val);
  }
  constexpr auto operator!=(const mint &rhs) const -> bool {
    return (val >= mod ? val - mod : val) !=
           (rhs.val >= mod ? rhs.val - mod : rhs.val);
  }
  [[nodiscard]] constexpr auto pow(u64 n) const -> mint {
    mint res(1), mul(*this);
    while (n > 0) {
      if (n & 1) res *= mul;
      mul *= mul, n >>= 1;
    }
    return res;
  }
  [[nodiscard]] constexpr auto inverse() const -> mint {
    i32 x = get(), y = mod, u = 1, v = 0;
    while (y > 0) {
      i32 t = x / y;
      x -= t * y, u -= t * v;
      std::swap(x, y);
      std::swap(u, v);
    }
    return mint {u};
  }

  friend auto operator<<(std::ostream &os, const mint &b) -> std::ostream & {
    return os << b.get();
  }
  friend auto operator>>(std::istream &is, mint &b) -> std::istream & {
    i64 t;
    is >> t;
    b = mint(t);
    return (is);
  }
};

using mint = LazyMontgomeryModInt<1'000'000'007>;

struct Matrix {
  int n; vector<vector<mint>> M;

  Matrix(int _n, bool id = false) : n(_n) {
    M.resize(n, vector<mint>(n));
    if (id) for (int i = 0; i < n; i++) M[i][i] = 1;
  }

  Matrix &operator*=(const Matrix &m) {
    vector<vector<mint>> ans(n, vector<mint>(n));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
          ans[i][j] += M[i][k] * m.M[k][j];
        }
      }
    }
    this->M = move(ans);
    return *this;
  }
  Matrix pow(int k) const {
    Matrix x(*this), res(n, true);
    for (; k > 0; k >>= 1, x *= x) {
      if (k & 1) res *= x;
    }
    return res;
  }
};
