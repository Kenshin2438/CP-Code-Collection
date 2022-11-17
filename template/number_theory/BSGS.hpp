// a^x EQUIV n (MOD mod), and gcd(a, mod) = 1
ll BSGS(ll a, ll n, ll mod) {
  a %= mod, n %= mod;
  if (n == 1LL || mod == 1LL) return 0LL;

  unordered_map<ll, ll> bs; // Attention !
  ll S = sqrt(mod) + 1;

  ll base = n;
  for (ll k = 0, val = base; k <= S; k++) {
    bs[val] = k, val = val * a % mod;
  }
  base = qpow(a, S, mod);
  for (ll x = 1, val = base; x <= S; x++) {
    if (bs.count(val)) return x * S - bs[val];
    val = val * base % mod;
  }
  return -1;  // No solution
}

ll inv(ll a, ll mod) {
  auto [res, _] = exgcd(a, mod);
  return (res % mod + mod) % mod;
}

// a^x EQUIV n (MOD mod), and gcd(a, mod) != 1
ll exBSGS(ll a, ll n, ll mod) {
  a %= mod, n %= mod;
  if (n == 1LL || mod == 1LL) return 0LL;

  ll k = 0, val = 1;
  for (ll g = __gcd(a, mod); g != 1LL; g = __gcd(a, mod)) {
    if (n % g != 0LL) return -1;  // No solution
    mod /= g, n /= g;
    val = val * (a / g) % mod, k++;
    if (val == n) return k;
  }
  ll res = BSGS(a, n * inv(val, mod) % mod, mod);
  return ~res ? res + k : res;
}
