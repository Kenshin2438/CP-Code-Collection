#pragma once

#include <bit>
#include <cassert>
#include <cstdint>
#include <vector>

namespace kenshin::DS {
  template <typename T> using Func = T (*)(const T &, const T &);

  template <typename T, T const ut, Func<T> merge>
  class SparseTable {
   private:
    std::vector<std::vector<T>> st;

   public:
    constexpr explicit SparseTable(std::vector<T> &v) : st(1, v) {
      for (int pw {1}, k {1}; 2 * pw <= std::ssize(v); pw *= 2, k += 1) {
        st.emplace_back(std::size(v) - (2 * pw) + 1);
        for (int i {0}; i < std::ssize(st[k]); i++) {
          st[k][i] = merge(st[k - 1][i], st[k - 1][i + pw]);
        }
      }
    }

    [[nodiscard]] constexpr auto query(int l, int r) const -> T {
      assert(l <= r && "SparseTable query interval [l, r) is invalid!");
      if (l == r) return ut;
      const int dep = 31 - std::countl_zero(static_cast<uint32_t>(r - l));
      return merge(st[dep][l], st[dep][r - (1 << dep)]);
    };
  };
};  // namespace kenshin::DS