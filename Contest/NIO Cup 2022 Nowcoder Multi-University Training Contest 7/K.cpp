#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

template <typename T> struct Mo_algo {
  struct Mo {
    int l, r, id;
    Mo(int _l = 0, int _r = 0, int _id = 0) :
      l(_l), r(_r), id(_id) {};
  };
  vector<Mo> Q;
  const int B = 320; // block-size

  Mo_algo(const vector<tuple<int, int, int>> &query) {
    Q.reserve( static_cast<int>(query.size()) );
    for (auto &&[l, r, id] : query) {
      Q.emplace_back(l, r, id);
    }
    sort(all(Q), [&](const Mo &a, const Mo &b) {
      return (a.l / B == b.l / B) ? a.r < b.r : a.l < b.l;
    });
  }
  
  vector<T> ans;
  void solver() {
    int L = 1, R = 0;
    function<void(int)> add = [&](int x) {

    };
    function<void(int)> del = [&](int x) {

    };
    ans.resize(Q);
    for (const auto &[l, r, id] : Q) {
      while (R < r) add(++R);
      while (R > r) del(R--);
      while (L < l) add(++L);
      while (L > l) del(L--);
      ans[id] = ANS;
    }
  }
};

void solve() {

}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
