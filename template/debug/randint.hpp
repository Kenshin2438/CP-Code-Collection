#include "../main.hpp"

template<typename T> inline T randint(T l, T r) {
  mt19937 rng(__builtin_ia32_rdtsc());
  return uniform_int_distribution<T>(l, r)(rng);
}
