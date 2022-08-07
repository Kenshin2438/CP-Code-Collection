#include "../main.hpp"

// 前缀函数 p[i] -> 前缀串s[0..i]的最长匹配的真前后缀
// p[i] = max{k : s[0..k]==s[i-k+1..i]}

vector<int> KMP(const string &s, const string &pat) {
  string t = pat + '\0' + s;
#define sz(x) static_cast<int>((x).size())
  vector<int> lps(sz(t), 0);
  for (int i = 1; i < sz(t); i++) {
    int g = lps[i - 1];
    while (g && t[i] != t[g]) g = lps[g - 1];
    lps[i] = g + (t[i] == t[g]);
  }
  vector<int> match;
  for (int i = sz(t) - sz(s); i < sz(t); i++) {
    if (lps[i] == sz(pat)) {
      match.push_back(i - 2 * sz(pat));
    }
  }
#undef sz
  return match;
}
