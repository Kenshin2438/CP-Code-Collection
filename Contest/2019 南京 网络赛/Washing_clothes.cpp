#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)

#define T long long // ValueTypename
struct Line {
  mutable T k, b, x;
  bool operator < (const Line &rhs) const { return k < rhs.k; }
  bool operator < (T rhs) const { return x < rhs; }
};
struct CHT : multiset<Line, less<>> {
  static const T inf = numeric_limits<T>::max();
  // (for doubles, use inf = 1/.0, div(a,b) = a/b)
  // T div(T a, T b) { return a / b; }
  T div(T a, T b) { return a / b - (T)((a ^ b) < 0 && a % b); }
  bool isect(iterator A, iterator B) { // judge intersect
    if (B == end()) return A->x = inf, false;
    if (A->k == B->k) A->x = A->b > B->b ? inf : -inf;
    else A->x = div(B->b - A->b, A->k - B->k);
    return A->x >= B->x;
  }
  void add(T k, T b) {
    iterator C = insert({k, b, 0}), A, B = A = C++;
    while (isect(B, C)) C = erase(C);
    if (A != begin() && isect(--A, B)) isect(A, B = erase(B));
    while ((B = A) != begin() && (--A)->x >= B->x) isect(A, erase(B));
  }
  T get(T x) const { // get max kx+b
    assert(!empty()); // debug
    Line l = *lower_bound(x);
    return l.k * x + l.b;
  }
};
#undef T

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  
  int n, y;
  while (cin >> n >> y) {
    vector<int> t(n + 1);
    for (int i = 1; i <= n; i++) cin >> t[i];
    t[0] = -y;
    sort(all(t));
    
    vector<ll> ans(y + 1);
    CHT S; S.add(0, 0);
    for (int p = n, x = y; x >= 1; x--) {
      while (p >= 1) {
        ll now = max(S.get(x), (ll) t[p] + y);
        ll pre = max((ll) t[p - 1] + y, (n - p + 1) * 1LL * x + t[p]);
        if (pre <= now) {
          S.add((n - p + 1), t[p]);
          p--;
        } else break; 
      }
      ans[x] = max(S.get(x), (ll) t[p] + y);
    }
    for (int x = 1; x <= y; x++) {
      cout << ans[x] << " \n"[x == y];
    }
  }

  return 0;
}