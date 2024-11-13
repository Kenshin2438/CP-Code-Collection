#pragma once

#include <cassert>
#include <vector>

namespace kenshin::DS {
  template <typename T>
  using BinaryOperatorFuncPtr = T (*)(const T &, const T &);

  template <typename T, T const ut, BinaryOperatorFuncPtr<T> merge>
  class SegmentTree {
   private:
    int N = 1, _log = 0;
    std::vector<T> val {};

    constexpr void _update(int t) noexcept {
      val[t] = merge(val[t << 1 | 0], val[t << 1 | 1]);
    }

   public:
    constexpr explicit SegmentTree(const std::vector<T> &v) {
      while (N < std::ssize(v)) N <<= 1, _log++;
      val.resize(N << 1, ut);
      for (int i = 0; const T &x : v) val[N + (i++)] = x;
      for (int i = N - 1; i > 0; i--) _update(i);
    }

    constexpr void set(int p, const T &dif) {
      val[p += N] = dif;
      for (int i = 1; i <= _log; i++) _update(p >> i);
    }
    [[nodiscard]] constexpr auto get(int p) const -> T { return val[p + N]; }
    [[nodiscard]] constexpr auto query(int l, int r) const -> T {
      assert(l < r && "SegmentTree query interval [l, r) is invalid!");
      if (l == r) return ut;
      T L = ut, R = ut;
      for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1) L = merge(L, val[l++]);
        if (r & 1) R = merge(val[--r], R);
      }
      return merge(L, R);
    }
  };
};  // namespace kenshin::DS