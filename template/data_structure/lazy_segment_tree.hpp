#pragma once

#include <algorithm>
#include <bit>
#include <cassert>
#include <cstddef>
#include <ranges>
#include <vector>

namespace kenshin::DS {
  /**
   * Combiner Functions (maybe non-commutative)
   */
  template <typename A, typename B, typename R>
  using BinaryFunctionPtr = R (*)(const A&, const B&);

  /**
   * Bottom-up Lazy Propagation Segment Tree
   */
  template <typename T, T const ut, typename E, E const ue,
            BinaryFunctionPtr<T, T, T> const mergeTT,
            BinaryFunctionPtr<T, E, T> const mergeTE,
            BinaryFunctionPtr<E, E, E> const mergeEE>
  class LazySegmentTree {
   private:
    static inline constexpr std::size_t ROOT = 1;
    std::vector<T> data;
    std::vector<E> lazy;
    std::size_t INDEX;  // index of the leftmost leaf node

    [[nodiscard]] inline auto reflect(std::size_t node) const -> T {
      return lazy[node] == ue ? data[node] : mergeTE(data[node], lazy[node]);
    }
    inline auto recalc(std::size_t node) -> void {
      while (node >>= 1) {  // node != ROOT
        data[node] = mergeTT(reflect(node << 1 | 0), reflect(node << 1 | 1));
      }
    }
    inline auto eval(std::size_t node) -> void {
      if (lazy[node] == ue) return;
      lazy[node << 1 | 0] = mergeEE(lazy[node << 1 | 0], lazy[node]);
      lazy[node << 1 | 1] = mergeEE(lazy[node << 1 | 1], lazy[node]);
      data[node] = reflect(node);
      lazy[node] = ue;
    }
    inline auto thrust(std::size_t node) -> void {
      std::vector<std::size_t> parents;
      while (node != ROOT) parents.emplace_back(node >>= 1);
      for (auto p : parents | std::views::reverse) eval(p);
    }

    constexpr auto init(const std::size_t& N) -> void {
      INDEX = std::bit_ceil(N);
      data.resize(2 * INDEX, ut);
      lazy.resize(2 * INDEX, ue);
    }

   public:
    template <std::ranges::input_range R>
      requires std::convertible_to<std::ranges::range_value_t<R>, T>
    constexpr explicit LazySegmentTree(R&& range)
      : data(std::ranges::begin(range), std::ranges::end(range)) {
      init(range.size());
      std::ranges::rotate(data, data.begin() + INDEX);
      for (auto node = INDEX - 1; node != 0; node--) {
        data[node] = mergeTT(data[node << 1 | 0], data[node << 1 | 1]);
      }
    }

    auto set(std::size_t pos, const T& val) -> void {
      thrust(pos += INDEX);
      data[pos] = val;
      lazy[pos] = ue;
      recalc(pos);
    }
    [[nodiscard]] auto get(std::size_t pos) const -> T {
      thrust(pos += INDEX);
      return reflect(pos);
    }
    auto query(std::size_t l, std::size_t r) -> T {
      assert((l <= r) && "SegmentTree query interval [l, r) is invalid!");
      if (l == r) return ut;
      l += INDEX, r += INDEX;
      thrust(l), thrust(r - 1);
      T L = ut, R = ut;
      for (auto a = l, b = r; a < b; a >>= 1, b >>= 1) {
        if (a & 1) L = mergeTT(L, reflect(a)), a++;
        if (b & 1) --b, R = mergeTT(reflect(b), R);
      }
      return mergeTT(L, R);
    }
    auto update(std::size_t l, std::size_t r, const E& diff) -> void {
      assert((l <= r) && "SegmentTree update interval [l, r) is invalid!");
      if (l == r) return;
      l += INDEX, r += INDEX;
      thrust(l), thrust(r - 1);
      for (auto a = l, b = r; a < b; a >>= 1, b >>= 1) {
        if (a & 1) lazy[a] = mergeEE(lazy[a], diff), a++;
        if (b & 1) --b, lazy[b] = mergeEE(lazy[b], diff);
      }
      recalc(l), recalc(r - 1);
    }
  };
}  // namespace kenshin::DS
