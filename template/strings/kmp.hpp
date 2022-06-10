#include "../main.hpp"

vector<int> KMP(const string &s, const string &pat) {
  string t = pat + '\0' + s;
#define sz(x) static_cast<int>((x).size())
  vector<int> p(sz(t), 0);
  for (int i = 1; i < sz(t); i++) {
    int g = p[i - 1];
    while (g && t[i] != t[g]) g = p[g - 1];
    p[i] = g + (t[i] == t[g]);
  }
  vector<int> match;
  for (int i = sz(t) - sz(pat); i < sz(t); i++) {
    if (p[i] == sz(pat)) {
      match.push_back(i - 2 * sz(pat));
    }
  }
#undef sz
  return match;
}