/**
 * Based on url('https://codeforces.com/contest/1787/submission/191105890')
 * ANSI Escape Sequences: https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
 * TODO: 
*/

#pragma once

// 基本数据类型
void __print(const int &x) { std::cerr << x; }
void __print(const long &x) { std::cerr << x; }
void __print(const long long &x) { std::cerr << x; }
void __print(const unsigned &x) { std::cerr << x; }
void __print(const unsigned long &x) { std::cerr << x; }
void __print(const unsigned long long &x) { std::cerr << x; }
void __print(const float &x) { std::cerr << x; }
void __print(const double &x) { std::cerr << x; }
void __print(const long double &x) { std::cerr << x; }
void __print(const bool &x) { std::cerr << (x ? "true" : "false"); }
void __print(const char &x) { std::cerr << '\'' << x << '\''; }
void __print(const char *x) { std::cerr << '\"' << x << '\"'; }
void __print(char *x) { std::cerr << '\"' << x << '\"'; }
void __print(const std::string &x) { std::cerr << '\"' << x << '\"'; }
// pair, tuple
template <typename A, typename B>
void __print(const std::pair<A, B> &p) {
  std::cerr << "(";
  __print(p.first);
  std::cerr << ", ";
  __print(p.second);
  std::cerr << ")";
}
template <typename A, typename B, typename C>
void __print(const std::tuple<A, B, C> &p) {
  std::cerr << "(";
  __print(std::get<0>(p));
  std::cerr << ", ";
  __print(std::get<1>(p));
  std::cerr << ", ";
  __print(std::get<2>(p));
  std::cerr << ")";
}
// 枚举容器
template <typename T> void __print(const T &x) {
  int f = 0;
  std::cerr << '{';
  for (auto &i : x) std::cerr << (f++ ? ", " : ""), __print(i);
  std::cerr << "}";
}
// Debug Mode
void debug_out() { std::cerr << "\e[92m" << std::endl; }
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  std::cerr << " ", __print(H), debug_out(T...);
}
#define debug(...) std::cerr << "\e[91m" << __func__ << ":" << __LINE__ << " [" << #__VA_ARGS__ << "] =", debug_out(__VA_ARGS__) 
// 输出 __func__ << ":" << __LINE__ 提debug的位置信息（函数，行号）