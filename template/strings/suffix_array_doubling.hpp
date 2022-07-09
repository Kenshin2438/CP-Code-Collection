#include "../main.hpp"

// O(n log(n))
struct SuffixArray_doubling {
  vector<int> sa, lcp;
  SuffixArray_doubling(const string &s, int lim = 256) {
    int n = (int) s.length() + 1; // 注意为 s.length() + 1
    vector<int> x(all(s) + 1), y(n), ws(max(n, lim));
    sa.resize(n), iota(all(sa), 0);
    for (int d = 0, p = 0; p < n; d = max(1, d << 1), lim = p) {
      p = d, iota(all(y), n - d);
      for (int i = 0; i < n; i++) if (sa[i] >= d) y[p++] = sa[i] - d;
      fill(all(ws), 0);
      for (int i = 0; i < n; i++) ws[x[i]]++;
      for (int i = 1; i < lim; i++) ws[i] += ws[i - 1];
      for (int i = n - 1; i >= 0; i--) sa[--ws[x[y[i]]]] = y[i];
      swap(x, y), p = 1, x[sa[0]] = 0;
      for (int i = 1; i < n; i++) {
        int a = sa[i - 1], b = sa[i];
        x[b] = (y[a] == y[b] && y[a + d] == y[b + d]) ? p - 1 : p++;
      }
    }
    vector<int> rk(n); // sa[0] = s.length()
    for (int i = 1; i < n; i++) rk[sa[i]] = i;
    lcp.resize(n); // longest common prefixes
    // lcp[i] = LCP(sa[i], sa[i - 1])
    for (int i = 0, d = 0, p = 0; i < (int) s.length(); i++) {
      p -= p > 0, d = sa[rk[i] - 1];
      while (s[i + p] == s[d + p]) p++;
      lcp[rk[i]] = p;
    }
    sa.erase(begin(sa)), lcp.erase(begin(lcp));
  }
};