#include "../main.hpp"

vec<int> KMP(const str &s, const str &pat) {
  str t = pat + '\0' + s;
  vec<int> p(t.size(), 0);
  for (size_t i = 1; i < t.size(); i++) {
    int g = p[i - 1];
    while (g && t[i] != t[g]) g = p[g - 1];
    p[i] = g + (t[i] == t[g]);
  }
  vec<int> match;
  for (size_t i = t.size() - pat.size(); i < t.size(); i++) {
    if (p[i] == pat.size()) match.push_back(i - 2 * pat.size());
  }
  return match;
}