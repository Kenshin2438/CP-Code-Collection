#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

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

const ll inf = 1e18;
struct edge {
  int to; ll weight;
  edge(int to, ll _ = inf) : to(to), weight(_) {}
};
int n, m, k;
vector<vector<edge>> G;
vector<ll> dis;

void Dijkstra() {
  priority_queue<pair<ll, int>> pq;
  for (int s = 1; s <= n; s++) pq.emplace(-dis[s], s);
  while (!pq.empty()) {
    auto [du, u] = pq.top();
    pq.pop(), du = -du;
    if (dis[u] < du) continue;
    for (auto [v, d] : G[u]) {
      if (dis[v] > d + du) {
        dis[v] = d + du;
        pq.emplace(-dis[v], v);
      }
    }
  }
}

void solve() {
  cin >> n >> m >> k;
  G.resize(n + 1);
  for (int i = 0; i < m; i++) {
    int u, v; ll w;
    cin >> u >> v >> w;
    G[u].emplace_back(v, w);
    G[v].emplace_back(u, w);
  }

  dis.assign(n + 1, inf), dis[1] = 0;
  Dijkstra();
  for (int _ = 0; _ < k; _++) {
    CHT dp;
    for (int i = 1; i <= n; i++) {
      dp.add( 2LL * i, - (dis[i] + i * 1LL * i) );
    }
    for (int i = 1; i <= n; i++) {
      dis[i] = i * 1LL * i - dp.get(i);
    }
    Dijkstra();
  }
  for (int i = 1; i <= n; i++) cout << dis[i] << " \n"[i == n];
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}
