#include <random>

std::mt19937 rng(__builtin_ia32_rdtsc());
template<typename T> inline T randint(T l, T r) {
  return std::uniform_int_distribution<T>(l, r)(rng);
}
template<typename E> inline E randreal(E l, E r) {
  return std::uniform_real_distribution<E>(l, r)(rng);
}
