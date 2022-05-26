#include "../main.hpp"

str LPP(str s) {
  str t = s + '#';
  reverse(all(s));
  t += s;

  int n = t.length();
  vec<int> lps(n, 0);
  for (int i = 1; i < n; i++) {
    int len = lps[i - 1];

    while (len > 0 && t[len] != t[i]) len = lps[len - 1];
    if (t[i] == t[len]) len++;

    lps[i] = len;
  }
  return t.substr(0, lps[n - 1]);
}
