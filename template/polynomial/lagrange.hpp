ll lagrange(ll N) { // (x, y)
  ll res = 0LL;
  for (int i = 1; i <= k + 2; i++) {
    ll tmp = y[i];
    for (int j = 1; j <= k + 2; j++) {
      if (i == j) continue;
      tmp = (N - x[j]) % mod * inv(x[i] - x[j]) % mod * tmp % mod;
    }
    res = (res + mod + tmp) % mod;
  }
  return res;
}