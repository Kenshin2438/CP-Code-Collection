#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

using ull = unsigned long long;
template<ull base> struct Hash {
  vector<ull> H, pw;

  Hash(const string &s = "") {
    H.emplace_back(0ULL);
    pw.emplace_back(1ULL);
    for (const char &c : s) {
      H.emplace_back(H.back() * base + c);
      pw.emplace_back(pw.back() * base);
    }
  }

  ull query(int l, int r) { // [l, r)
    return H[r] - H[l] * pw[r - l];
  }
};
using H = Hash<(ull) 1e11 + 3>;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  string s, t; cin >> s >> t;
  int n = s.length(), m = t.length();

  H HS(s), HT(t);

  auto check = [&](int len) -> bool {
    vector<ull> v;
    for (int i = 0; i + len - 1 < n; i++) {
      v.emplace_back(HS.query(i, i + len));
    }
    sort(all(v));
    for (int i = 0; i + len - 1 < m; i++) {
      if (binary_search(all(v), HT.query(i, i + len))) {
        return true;
      }
    }
    return false;
  };

  int L = 1, R = min(n, m), ans = 0;
  while (L <= R) {
    int M = (L + R) >> 1;
    if (check(M)) {
      ans = M, L = M + 1;
    } else {
      R = M - 1;
    }
  }
  cout << ans << '\n';

  return 0;
}
