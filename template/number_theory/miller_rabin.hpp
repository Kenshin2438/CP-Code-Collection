using ull = unsigned long long;
ull modmul(ull a, ull b, ull M) {
  ll ret = a * b - M * ull(1.L / M * a * b);
  return ret + M * (ret < 0) - M * (ret >= (ll)M);
}
ull modpow(ull b, ull e, ull mod) {
  ull ans = 1;
  for (; e; b = modmul(b, b, mod), e /= 2)
    if (e & 1) ans = modmul(ans, b, mod);
  return ans;
}
bool miller_rabin(ull n) {
  static const vector<ull> SPRP = {
    2, 325, 9375, 28178, 450775, 9780504, 1795265022
  };
  if (n == 1 || n % 6 % 4 != 1) return (n | 1) == 3;
  ll t = __builtin_ctzll(n - 1), k = (n - 1) >> t;
  for (const ull &a : SPRP) {
    ull tmp = modpow(a, k, n);
    if (tmp <= 1 || tmp == n - 1) continue;
    for (int i = 0; i <= t; i++) {
      if (i == t) return false;
      tmp = modmul(tmp, tmp, n);
      if (tmp == n - 1) break;
    }
  }
  return true;
}
