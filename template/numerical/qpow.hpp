#include "../main.hpp"
#include "../numerical/mint.hpp"

ll inv(ll a, ll b) {
  
}

ll qpow(ll x, ll n, ll mod) {
  if (x == 0) return 0;
  if (n == 0) return 1;
  if (n < 0) return qpow(inv(x, mod), -n, mod);
  ll res = 1LL;
  for (x %= mod; n > 0; n >>= 1, x = x * x % mod) {
    if (n & 1LL) res = res * x % mod;
  }
  return (res + mod) % mod;
}
