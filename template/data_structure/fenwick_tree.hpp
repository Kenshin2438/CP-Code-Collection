struct FenwickTree {
  vector<ll> s;
  FenwickTree(int n) : s(n) {}
  void update(int p, ll dif) {
    for (; p < sz(s); p |= p + 1) s[p] += dif;
  }
  ll query(int p) {  // [0, p)
    ll res = 0;
    for (; p > 0; p &= p - 1) res += s[p - 1];
    return res;
  }
};