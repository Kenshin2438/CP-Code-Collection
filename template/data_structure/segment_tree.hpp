#pragma once

#include <algorithm>
#include <bit>
#include <cassert>
#include <cstddef>
#include <optional>
#include <vector>

namespace kenshin::DS {
  /**
   * Combiner Functions (maybe non-commutative)
   */
  template <typename T>
  using BinaryFunctionPtr = T (*)(const T &, const T &);

  /**
   * Bottom-up Segment Tree
   */
  template <typename T, T const ut, BinaryFunctionPtr<T> const merge>
  class SegmentTree {
   private:
    static inline constexpr std::size_t ROOT = 1;
    std::vector<T> data;
    std::size_t INDEX;  // index of the leftmost leaf node

    inline auto update(std::size_t node) noexcept -> void {
      data[node] = merge(data[node << 1 | 0], data[node << 1 | 1]);
    }

   public:
    constexpr explicit SegmentTree(const std::size_t &N) {
      INDEX = std::bit_ceil(N);
      data.resize(2 * INDEX, ut);
    }

    template <std::ranges::input_range R>
      requires std::convertible_to<std::ranges::range_value_t<R>, T>
    constexpr explicit SegmentTree(R &&range)
      : data(std::ranges::begin(range), std::ranges::end(range)) {
      INDEX = std::bit_ceil(range.size());
      data.resize(2 * INDEX, ut);
      std::ranges::rotate(data, data.begin() + INDEX);
      for (auto node = INDEX - 1; node != 0; node--) update(node);
    }

    auto set(std::size_t pos, const T &val) -> void {
      data[pos += INDEX] = val;
      while (pos != ROOT) update(pos >>= 1);
    }
    [[nodiscard]] auto get(std::size_t pos) const -> T {
      return data[pos + INDEX];
    }
    [[nodiscard]] auto query(std::size_t l, std::size_t r) const -> T {
      assert((l <= r) && "SegmentTree query interval [l, r) is invalid!");
      if (l == r) return ut;
      l += INDEX, r += INDEX;
      T L = ut, R = ut;
      for (auto a = l, b = r; a < b; a >>= 1, b >>= 1) {
        if (a & 1) L = merge(L, data[a++]);
        if (b & 1) R = merge(data[--b], R);
      }
      return merge(L, R);
    }
    [[nodiscard]] auto query_all() const -> T { return data[ROOT]; }

    template <typename UnaryPred>
    [[nodiscard]] auto leftmost_if(const UnaryPred &pred) const
      -> std::optional<std::size_t> {
      if (not pred(data[ROOT])) return std::nullopt;
      auto node = ROOT;
      while (node < INDEX) {
        if (pred(data[node << 1 | 0])) {
          node = node << 1 | 0;
        } else {
          node = node << 1 | 1;
        }
      }
      return node - INDEX;
    }
  };
}  // namespace kenshin::DS
