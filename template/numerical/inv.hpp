#include "../main.hpp"
#include "../number_theory/exgcd.hpp"

template <typename T>
T inv(T a, T mod) {
  auto [res, _] = exgcd<T>(a, mod);
  return (res % mod + mod) % mod;
}

int inv(int x, int mod) {
  return x == 1 ? 1 : inv(mod % x, mod) * 1LL * (mod - mod / x) % mod;
}
