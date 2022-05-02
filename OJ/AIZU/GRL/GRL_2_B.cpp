#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

#define PII pair<int, int>
#define vec vector
#define str string
#define fi first
#define se second
#define all(a) a.begin(), a.end()
#define SZ(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

struct DSU {
  vec<int> p;
  DSU(int _) : p(_ + 1) { iota(all(p), 0); }
  int f(int _) { return _ == p[_] ? _ : p[_] = f(p[_]); }
  bool same(int u, int v) { return f(u) == f(v); }
  bool unite(int u, int v) {
    u = f(u), v = f(v);
    if (u == v) return false;
    return p[u] = v, true;
  }
};

const int inf = 0x3f3f3f3f;
struct edge {
  int u, v, w;
  edge(int _u, int _v, int _w = inf) :
    u(_u), v(_v), w(_w) {}
};

struct node {
  edge e; ll val;
  node *l, *r;
  node(edge _) : e(_), val(0) { l = r = nullptr; }
  void prop() {
    e.w += val;
    if (l != nullptr) l->val += val;
    if (r != nullptr) r->val += val;
    val = 0;
  }
  edge top() { return prop(), e; }
};
node *merge(node *a, node *b) {
  if (!a || !b) return a ?: b;
  a->prop(), b->prop();
  if (a->e.w > b->e.w) swap(a, b);
  a->r = merge(b, a->r);
  swap(a->l, a->r);
  return a;
}
void pop(node * &a) {
  a->prop(), a = merge(a->l, a->r);
}

int n, m, rt;
vec<edge> Edges;

int dmst() {
  DSU dsu(n);
  vec<node *> heap(n);
  for (const edge & e : Edges) {
    heap[e.v] = merge(heap[e.v], new node(e));
  }
  vec<int> seen(n, -1), path(n);
  int res = 0; seen[rt] = rt;
  for (int i = 0; i < n; i++) {
    int u = i, idx = 0;
    while (seen[u] < 0) {
      path[idx++] = u, seen[u] = i;
      if (!heap[u]) return -1;
      edge e = heap[u]->top();
      heap[u]->val -= e.w, pop(heap[u]);
      res += e.w, u = dsu.f(e.u);
      if (seen[u] != i) continue;
      node * cyc = nullptr;
      do {
        cyc = merge(cyc, heap[path[--idx]]);
      } while (dsu.unite(u, path[idx]));
      u = dsu.f(u), heap[u] = cyc, seen[u] = -1;
    }
  }
  return res;
}

void SingleTest(int TestCase) {
  cin >> n >> m >> rt;
  for (int u, v, w; m--; ) {
    cin >> u >> v >> w; // 0-indexed
    Edges.emplace_back(u, v, w);
  }
  cout << dmst() << '\n';
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  // cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
