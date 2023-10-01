vector<int> dep(n), siz(n), son(n, -1);
vector<int> dfn(n), seq;
const function<void(int, int)> dfs_son = [&](int u, int fa) {
  dfn[u] = seq.size(); seq.push_back(u); siz[u] = 1;
  for (const int &v : tree[u]) {
    if (v == fa) continue;
    dep[v] = dep[u] + 1;
    dfs_son(v, u);
    siz[u] += siz[v];
    if (son[u] == -1 || siz[son[u]] < siz[v]) son[u] = v;
  }
};
dfs_son(0, 0);

const auto add = [&](int x) { /*...*/ };
const auto del = [&](int x) { /*...*/ };
const auto calc = [&]() { /*...*/ };
const function<void(int, int, bool)> dfs = [&](int u, int fa, bool keep) {
  for (const int &v : tree[u]) {
    if (v == fa || v == son[u]) continue;
    dfs(v, u, false);
  }
  if (~son[u]) dfs(son[u], u, true);
  for (const int &v : tree[u]) {
    if (v == fa || v == son[u]) continue;
    for (int i = dfn[v]; i < dfn[v] + siz[v]; i++) add(seq[i]);
  }
  add(u); ans[u] = calc();
  if (keep == true) return;
  for (int i = dfn[u]; i < dfn[u] + siz[u]; i++) del(seq[i]);
};
dfs(0, 0, false);