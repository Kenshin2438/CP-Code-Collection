#pragma once

// #include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <tuple>
#include <deque>
#include <queue>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
using namespace std;

string to_string(const string &s) { return '"' + s + '"'; }
string to_string(const char *s) { return to_string((string) s); }
string to_string(const char &c) { return "'" + to_string(c) + "'"; }
string to_string(bool b) { return (b ? "true" : "false"); }
string to_string(const vector<bool> &v) {
  string res = "{";
  for (int i = 0; i < static_cast<int>(v.size()); i++) {
    if (i != 0) res += ", ";
    res += to_string(v[i]);
  }
  return res + "}";
}
template <size_t N> string to_string(bitset<N> v) {
  string res = "";
  for (size_t i = 0; i < N; i++) res += static_cast<char>('0' + v[i]);
  return res;
}
template <typename A, typename B>
string to_string(pair<A, B> p) {
  return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}
template <typename A, typename B, typename C>
string to_string(tuple<A, B> p) {
  return "(" + to_string(get<0>(p)) + ", "
             + to_string(get<1>(p)) + ", ";
}
template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p) {
  return "(" + to_string(get<0>(p)) + ", "
             + to_string(get<1>(p)) + ", "
             + to_string(get<2>(p)) + ")";
}
template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) {
  return "(" + to_string(get<0>(p)) + ", "
             + to_string(get<1>(p)) + ", "
             + to_string(get<2>(p)) + ", "
             + to_string(get<3>(p)) + ")";
}
template <typename A> string to_string(A v) {
  bool first = true;
  string res = "{";
  for (const auto &x : v) {
    if (!first) res += ", ";
    first = false;
    res += to_string(x);
  }
  return res + "}";
}
void debug_out() { cerr << endl; }
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H), debug_out(T...);
}
#define debug(...) cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
