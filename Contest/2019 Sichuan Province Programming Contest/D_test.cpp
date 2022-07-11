#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10;
#define fi first
#define se second
#define mp make_pair
#define sz(v) ((int)(v).size())
#define debug(a) cout << #a << " = " << a << endl;
typedef long long ll;
typedef pair <int, int> P;
vector < int > edge[N];
const ll MOD = 1e9 + 7;
int n, m;
int a[N], Size[N], dep[N], fa[N], hs[N], tot;
int minn[N], maxn[N], dfn;
void dfs(int u, int f, int d) {
    dep[u] = d; fa[u] = f; Size[u] = 1; dfn++;
    if (minn[a[u]] > n) minn[a[u]] = u;
    maxn[a[u]] = u;
    for (int i = 0; i < sz(edge[u]); i++) {
        int v = edge[u][i];
        if (v == fa[u]) continue;
        dfs(v, u, d + 1);
        if (Size[v] > Size[hs[u]])  hs[u] = v;
        Size[u] += Size[v];
    }
}

int top[N];
void dfs2(int u, int T) {
    top[u] = T;
    if (!hs[u]) return ;
    dfs2(hs[u], T);
    for (int i = 0; i < sz(edge[u]); i++){
        int v = edge[u][i];
        if (hs[u] == v || v == fa[u]) continue;
        dfs2(v, v);
    }
}

inline int Lca(int u, int v) {
    while (top[u] != top[v]) {
        if (dep[top[u]] < dep[top[v]])  swap(u, v);
        u = fa[top[u]];
    }
    return dep[u] > dep[v] ? v : u;
}

struct node {
    int a, b, c;
    inline bool operator < (const node & o) const {
        return a > o.a;
    }
} v[N];

int col[N];
bool vis[N];
void add(int u) {
    col[a[u]] = true; vis[u] = true;
    for (int i = 0; i < sz(edge[u]); i++) {
        int v = edge[u][i];
        if (v == fa[u] || vis[v]) continue;
        add(v);
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T;
    cin >> T;
    for (int Case = 1; Case <= T; Case++) {
        memset(minn, 0x3f, sizeof(minn));
        memset(maxn, 0xff, sizeof(maxn));
        cin >> n; tot = 0;
        for (int i = 1; i <= n; i++)    cin >> a[i];
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            edge[u].push_back(v);
            edge[v].push_back(u);
        }
        dfs(1, 0, 0);
        dfs2(1, 1);
        for (int i = 1; i <= n; i++)
            if (minn[i] <= n && maxn[i] > 0) {
                int l = Lca(minn[i], maxn[i]);
                v[++tot] = {dep[l], l, i};
            }
        sort(v + 1, v + tot + 1);
        int ans = 0;
        for (int i = 1; i <= tot; i++) {
            if (col[v[i].c]) continue;
            add(v[i].b);  ans++;
        }
        for (int i = 1; i <= n; i++)
            vis[i] = false, col[i] = false, hs[i] = 0, edge[i].clear();
        cout << "Case " << Case << ": " << ans << endl;
    }
    return 0;
}
