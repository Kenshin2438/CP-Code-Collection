using ull = unsigned long long;

#include <bits/extc++.h>
const int SEED = chrono::steady_clock::now().time_since_epoch().count();
struct chash {  // To use most bits rather than just the lowest ones:
  const ull C = ll(4e18 * acos(0)) | 71;  // large odd number
  ll operator()(ll x) const { return __builtin_bswap64((x ^ SEED) * C); }
};
using HashMap = __gnu_pbds::gp_hash_table<ll, int, chash>;

ull splitmix64(ull x) {
  // http://xorshift.di.unimi.it/splitmix64.c
  x += 0x9e3779b97f4a7c15;
  x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
  x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
  return x ^ (x >> 31);
}
