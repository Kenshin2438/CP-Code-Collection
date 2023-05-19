/**
 * Based on:
 * https://codeforces.com/contest/1787/submission/191105890
 *
 * ANSI Escape Sequences:
 * https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
 */

#pragma once

#include <bitset>
#include <iostream>
#include <string>
#include <type_traits>

namespace dbg {
// arithmetic
template <class _Tp, std::enable_if_t<std::is_arithmetic_v<_Tp>, int> = 0>
void __print(const _Tp &x) {
  if constexpr (std::is_same_v<_Tp, bool>) {
    std::cerr << (x ? "true" : "false");
  } else {
    std::cerr << x;
  }
}

// string
void __print(const std::string &x) { std::cerr << '\"' << x << '\"'; }

// bitset
template <size_t N> void __print(const std::bitset<N> &Bs)
{ std::cerr << Bs; }

// pair
template <typename A, typename B>
void __print(const std::pair<A, B> &p) {
  std::cerr << "(";
  __print(p.first);
  std::cerr << ", ";
  __print(p.second);
  std::cerr << ")";
}

// Iterable https://spectre-code.org/sfinae.html
template <typename _Tp, typename = std::void_t<>>
struct is_iterable : public std::false_type {};

template <typename _Tp>
struct is_iterable<_Tp, std::void_t<decltype(std::declval<_Tp>().begin(),
                                             std::declval<_Tp>().end())>>
    : public std::true_type {};

template <typename _Tp>
using is_iterable_t = typename is_iterable<_Tp>::type;

template <typename _Tp>
inline constexpr bool is_iterable_v = is_iterable<_Tp>::value;

template <class _Tp, std::enable_if_t<is_iterable_v<_Tp>, int> = 0>
void __print(const _Tp &v) {
  int f = 0;
  std::cerr << '{';
  for (const auto &i : v) {
    if (f++) std::cerr << ", ";
    __print(i);
  }
  std::cerr << "}";
}

// Debug Mode
void debug_out() { std::cerr << "\e[0m" << std::endl; }
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  std::cerr << " ", __print(H), debug_out(T...);
}
// 输出 __func__ << ":" << __LINE__ 提debug的位置信息（函数，行号）
#define debug(...)                                                             \
  std::cerr << "\e[91m" << __func__ << ":" << __LINE__ << " [" << #__VA_ARGS__ \
            << "] =",                                                          \
      debug_out(__VA_ARGS__)
};  // namespace dbg
using namespace dbg;