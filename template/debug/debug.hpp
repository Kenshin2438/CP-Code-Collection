/**
 * Based on submission('https://codeforces.com/contest/1787/submission/191105890') 
 * ANSI Escape Sequences: https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797 
 */

#pragma once

#include <iostream>
#include <type_traits>
#include <string>

namespace dbg {
// arithmetic
template <class T, std::enable_if_t<std::is_arithmetic_v<T>, int> = 0>
void __print(const T &x) { std::cerr << std::boolalpha << x; }

// string
void __print(const std::string &x) { std::cerr << '\"' << x << '\"'; }

// bitset
template <std::size_t N> void __print(const bitset<N> &Bs) 
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
template <typename T, typename = std::void_t<>>
struct is_iterable : public std::false_type {};
 
template <typename T>
struct is_iterable<T, std::void_t<decltype(std::declval<T>().begin(),
                                           std::declval<T>().end())>>
    : public std::true_type {};

template <typename T>
using is_iterable_t = typename is_iterable<T>::type;
 
template <typename T>
inline constexpr bool is_iterable_v = is_iterable<T>::value;

template <class T, std::enable_if_t<dbg::is_iterable_v<T>, int> = 0>
void __print(const T &v) {
  int f = 0;
  std::cerr << '{';
  for (const auto &i : v) std::cerr << (f++ ? ", " : ""), __print(i);
  std::cerr << "}";
}

// Debug Mode
void debug_out() { std::cerr << "\e[0m" << std::endl; }
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  std::cerr << " ", __print(H), debug_out(T...);
}
#define debug(...)                                                             \
  std::cerr << "\e[91m" << __func__ << ":" << __LINE__ << " [" << #__VA_ARGS__ \
            << "] =",                                                          \
      debug_out(__VA_ARGS__)
// 输出 __func__ << ":" << __LINE__ 提debug的位置信息（函数，行号）
};
using namespace dbg;