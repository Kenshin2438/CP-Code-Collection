// https://codeforces.com/contest/1715/problem/E
// https://loj.ac/p/2035
// https://ac.nowcoder.com/acm/problem/20352

struct Line {
  mutable ll k, b, x;
  bool operator < (const Line &rhs) const { return k < rhs.k; }
  bool operator < (const ll &rhs) const { return x < rhs; }
};
// Incremental Convex Hull Trick
struct CHT : multiset<Line, less<>> {
  static const ll inf = numeric_limits<ll>::max();
  // for doubles, use inf = 1/.0, div(a, b) = a / b
  ll div(ll a, ll b) { return a / b - (ll)((a ^ b) < 0 && a % b); }
  bool isect(iterator A, iterator B) { // judge intersect
    if (B == end()) return A->x = inf, false;
    if (A->k == B->k) A->x = A->b > B->b ? inf : -inf;
    else A->x = div(B->b - A->b, A->k - B->k);
    return A->x >= B->x;
  }
  void add(ll k, ll b) {
    iterator C = insert({k, b, 0}), A, B = A = C++;
    while (isect(B, C)) C = erase(C);
    if (A != begin() && isect(--A, B)) isect(A, B = erase(B));
    while ((B = A) != begin() && (--A)->x >= B->x) isect(A, erase(B));
  }
  ll get(ll x) const { // get max kx+b
    assert(!empty()); // debug
    Line l = *lower_bound(x);
    return l.k * x + l.b;
  }
};
