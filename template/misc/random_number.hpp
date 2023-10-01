std::mt19937 rng(static_cast<unsigned int>(__builtin_ia32_rdtsc()));
template <typename T>
auto randint(T l, T r) -> T {
  return std::uniform_int_distribution<T>(l, r)(rng);
}
template <typename E>
auto randreal(E l, E r) -> E {
  return std::uniform_real_distribution<E>(l, r)(rng);
}