const int N = (int) 5e5 + 10;
int n, root, cmpk;

struct node {
  int pos[2];
  int son[2];
  int min[2];
  int max[2];
  int id;
  bool operator < (const node &rhs) const {
    return pos[cmpk] < rhs.pos[cmpk];
  }
} KDT[N];

void update(int nd) {
  for (int k = 0; k < 2; k++) {
    KDT[nd].min[k] = KDT[nd].max[k] = KDT[nd].pos[k];
    for (int i = 0; i < 2; i++) if (KDT[nd].son[i]) {
      int s = KDT[nd].son[i];
      KDT[nd].min[k] = min(KDT[nd].min[k], KDT[s].min[k]);
      KDT[nd].max[k] = max(KDT[nd].max[k], KDT[s].max[k]);
    }
  }
}

int build(int l, int r, int k) {
  int m = (l + r) >> 1; cmpk = k;
  nth_element(KDT + l, KDT + m, KDT + r + 1);
  KDT[m].son[0] = KDT[m].son[1] = 0;
  if (l != m) KDT[m].son[0] = build(l, m - 1, k ^ 1);
  if (r != m) KDT[m].son[1] = build(m + 1, r, k ^ 1);
  return update(m), m;
}

void KDT_build() {
  for (int i = 1; i <= n; i++) {
    cin >> KDT[i].pos[0] >> KDT[i].pos[1];
    KDT[i].id = i;
  }
  root = build(1, n, 0);
}

vector<int> ans;
int st[2], ed[2];

bool judge(const node &nd) {
  return nd.pos[0] >= st[0]
      && nd.pos[0] <= ed[0]
      && nd.pos[1] >= st[1]
      && nd.pos[1] <= ed[1];
}

bool check(const node &nd) {
  return nd.min[0] <= ed[0]
      && nd.max[0] >= st[0]
      && nd.min[1] <= ed[1]
      && nd.max[1] >= st[1];
}

void query(int nd) {
  if (judge(KDT[nd])) ans.push_back(KDT[nd].id);
  for (int i = 0; i < 2; i++) if (KDT[nd].son[i]) {
    int s = KDT[nd].son[i];
    if (check(KDT[s])) query(s);
  }
}

void SingleTest(int TestCase) {
  cin >> n; KDT_build();
  int q; cin >> q;
  while (q--) { // 找到矩形区域内的所有点
    cin >> st[0] >> ed[0];
    cin >> st[1] >> ed[1];
    ans.clear(), query(root), sort(all(ans));
    for (int id : ans) cout << id - 1 << '\n';
  }
}