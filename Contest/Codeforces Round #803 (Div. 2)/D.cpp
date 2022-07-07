#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)

vector<int> query(int l, int r) {
  cout << "? " << l << ' ' << r << endl;
  vector<int> res(r - l + 1);
  for (int &x : res) cin >> x;
  return res;
}

void answer(int p) { cout << "! " << p << endl; }

int ok[10005], A = 0;

void f(int s, int t) {
  if (s == t) return answer(s);

  int m = (s + t) >> 1;
  auto res = query(s, m);
  vector<int> a;
  for (int x : res) {
    if (s <= x && x <= m) a.push_back(x);
  }
  if (a.size() & 1) {
    f(s, m);
  } else {
    f(m + 1, t);
  }
}

void solve() {
  int n; cin >> n;
  if (n <= 15) {
    for (int i = 1; i <= n; i++) {
      auto r = query(i, i);
      if (r[0] == i) return answer(i);
    }
  } else {
    f(1, n);
  }
}

int main() {
  // cin.tie(nullptr)->sync_with_stdio(false);
  int T;
  cin >> T;
  while (T--) solve();
  return 0;
}
