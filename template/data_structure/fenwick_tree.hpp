struct FenwickTree {
  vector<ll> s;
  FenwickTree(int n) : s(n) {}
  void update(int pos, ll dif) {
    for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
  }
  ll query(int pos) { // [0, pos)
    ll res = 0;
    for (; pos > 0; pos &= pos - 1) res += s[pos - 1];
    return res;
  }
};

struct FenwickTree {
  vector<ll> s, d;

  FenwickTree() = default;
  FenwickTree(int n) : s(n), d(n) {}

  void add(int p, ll dif) {
    ll val = (p + 1) * dif;
    for (; p < s.size(); p |= p + 1) {
      s[p] += val, d[p] += dif;
    }
  }
  ll query(int i) {
    ll S = 0LL, D = 0LL;
    for (int p = i; p > 0; p &= p - 1) {
      S += s[p - 1], D += d[p - 1];
    }
    return D * (i + 1) - S;
  }
  void range_add(int l, int r, ll val) {  // [l, r)
    add(l, val), add(r, -val);
  }
  ll range_query(int l, int r) {  // [l, r)
    return query(r) - query(l);
  }
};
