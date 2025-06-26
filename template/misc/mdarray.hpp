#pragma once

#include <array>
#include <cstddef>

namespace kenshin::util {
  namespace internal {
    template <typename T, size_t N, size_t... Ns> struct mdarray {
      using type = typename std::array<typename mdarray<T, Ns...>::type, N>;
    };

    template <typename T, size_t N> struct mdarray<T, N> {
      using type = typename std::array<T, N>;
    };
  }  // namespace internal

  template <typename T, size_t N, size_t... Ns>
  using mdarray_t = internal::mdarray<T, N, Ns...>::type;
};  // namespace kenshin::util

using namespace kenshin::util;