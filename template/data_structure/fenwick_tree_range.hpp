struct FenwickTreeRange {
  vector<ll> s, d;
  FenwickTreeRange(int n) : s(n), d(n) {}
  void add(int p, ll dif) {
    ll val = (p + 1) * dif;
    for (; p < sz(s); p |= p + 1) s[p] += val, d[p] += dif;
  }
  ll _query(int p) { // Prefix Sum [0, p)
    ll S = 0LL, D = 0LL;
    for (int i = p; i > 0; i &= i - 1)
      S += s[i - 1], D += d[i - 1];
    return D * (p + 1) - S;
  }
  void range_add(int l, int r, ll val) // [l, r)
  { add(l, val), add(r, -val); }
  ll range_query(int l, int r) // [l, r)
  { return _query(r) - _query(l); }
};
