#include "../main.hpp"

template <typename T>
pair<T, T> exgcd(T a, T b) {
  bool nega = (a < 0), negb = (b < 0);
  T x = 1, y = 0;
  T r = 0, s = 1, t = 0;
  while (b) {
    r ^= x ^= r ^= x -= (t = a / b) * r;
    s ^= y ^= s ^= y -= t * s;
    b ^= a ^= b ^= a %= b;
  }
  return {nega ? -x : x, negb ? -y : y};
}

// void exgcd(ll a, ll b, ll &g, ll &x, ll &y) {
//   if (b != 0) {
//     exgcd(b, a % b, g, y, x);
//     y -= a / b * x;
//   } else {
//     x = 1, y = 0, g = a;
//   }
// }
