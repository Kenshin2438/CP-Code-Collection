#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

using ll = long long;
#define all(a) begin(a), end(a)
#define sz(x) (int)((x).size())

void solve() {
  int n, m, k; cin >> n >> m >> k;
  assert(1 <= n && n <= (int)2E5);
  assert(1 <= m && m <= (int)2E5);
  assert(k <= n + m);

  using Tp = tuple<ll, int, int, int>;
  vector<Tp> a;
  // < 10*g+f, 1/0, g, id >
  for (int i = 0; i < n; i++) {
    int id, f, g; cin >> id >> f >> g;
    a.emplace_back(10LL * g + f, 1, g, - id);
  }
  for (int i = 0; i < m; i++) {
    int id, f, g; cin >> id >> f >> g;
    a.emplace_back(10LL * g + f, 0, g, - id);
  }

  sort(all(a), greater<>());
  decltype(a) A, B;
  for (int i = 0; i < k; i++) {
    if (get<1>(a[i]) == 0) A.emplace_back(a[i]);
  }
  for (int i = k; i < n + m; i++) {
    if (get<1>(a[i]) == 1) B.emplace_back(a[i]);
  }

  cout << sz(A) << ' ' << sz(B) << '\n';
  sort(all(A), [](Tp pre, Tp aft) { 
    return get<3>(pre) > get<3>(aft);
  });
  sort(all(B), [](Tp pre, Tp aft) { 
    return get<3>(pre) > get<3>(aft);
  });
  for (const auto &span : A) {
    ll F; int id, f, g;
    tie(F, std::ignore, g, id) = span;
    f = F - 10LL * g;
    id = -id;

    cout << id << ' ' << f << ' ' << g << '\n';
  }
  for (const auto &span : B) {
    ll F; int id, f, g;
    tie(F, std::ignore, g, id) = span;
    f = F - 10LL * g;
    id = -id;

    cout << id << ' ' << f << ' ' << g << '\n';
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--) solve();

  return 0;
}