#pragma once

#include <bitset>
#include <deque>
#include <iostream>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

template <class T> string to_string(const T &v);

string to_string(const string &s) { 
  string res = "";
  res.append("\"").append(s).append("\"");
  return res;
}
string to_string(const char *s) { return to_string((string)s); }
string to_string(char s[]) { return to_string(string(s)); }
string to_string(const char &c) {
  string res = "";
  res.append("'").append(1, c).append("'");
  return res;
}
string to_string(bool b) { return (b ? "true" : "false"); }
string to_string(const vector<bool> &v) {
  string res = "{";
  for (int i = 0; i < static_cast<int>(v.size()); i++) {
    if (i != 0) res += ", ";
    res += to_string(v[i]);
  }
  return res += "}", res;
}
template <size_t N>
string to_string(const bitset<N> &v) {
  string res = "";
  for (size_t i = 0; i < N; i++) res += static_cast<char>('0' + v[i]);
  return res;
}
template <typename A, typename B>
string to_string(const pair<A, B> &p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}
template <typename A, typename B>
string to_string(const tuple<A, B> &p) {
  return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", ";
}
template <typename A, typename B, typename C>
string to_string(const tuple<A, B, C> &p) {
  return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " +
         to_string(get<2>(p)) + ")";
}
template <typename A, typename B, typename C, typename D>
string to_string(const tuple<A, B, C, D> &p) {
  return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " +
         to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
}
template <typename A>
string to_string(const A &v) {
  bool first = true;
  string res = "{";
  for (const auto &x : v) {
    if (!first) res += ", ";
    first = false;
    res += to_string(x);
  }
  return res += "}", res;
}
void debug_out() { cerr << endl; }
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H), debug_out(T...);
}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
