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
  void prop() {
    e.w += val;
    if (l != nullptr) l->val += val;
    if (r != nullptr) r->val += val;
    val = 0;
  }
  edge top() { return prop(), e; }
};
node * merge(node *a, node *b) {
  if (b == nullptr) return a;
  if (a == nullptr) return b;
  a->prop(), b->prop();
  if (a->e.w > b->e.w) swap(a, b);
  swap(a->l, a->r = merge(b, a->r));
  return a;
}
void pop(node * &a) {
  a->prop();
  a = merge(a->l, a->r);
}

int n, m;
vec<edge> Edges;

int dmst(int s) {
  DSU set(n);
  vec<node *> heap(n);
  for (auto &e : Edges) {
    node * cur = new node{e};
    heap[e.v] = merge(heap[e.v], cur);
  }
  vec<int> seen(n, -1), path(n);
  int res = 0; seen[s] = s;
  for (int i = 0; i < n; i++) {
    int u = i, 
  }
  return res;
}

void SingleTest(int TestCase) {
  cin >> n >> m;
  int s; cin >> s;
  for (int u, v, w; m--; ) {
    cin >> u >> v >> w;
    Edges.emplace_back(u, v, w);
  }
  cout << dmst(s) << '\n';
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
