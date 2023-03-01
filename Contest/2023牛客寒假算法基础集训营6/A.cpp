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

void solve()
{
  int x;
  cin >> x;

  if (1 <= x && x <= 7)
    cout << "very easy";
  if (7 < x && x <= 233)
    cout << "easy";
  if (233 < x && x <= 10032)
    cout << "medium";
  if (10032 < x && x <= 114514)
    cout << "hard";
  if (114514 < x && x <= 1919810)
    cout << "very hard";
  if (1919810 < x)
    cout << "can not imagine";
}

int main()
{
  cin.tie(nullptr)->sync_with_stdio(false);
  cout << fixed << setprecision(15);

  int T = 1;
  // cin >> T;
  while (T--)
    solve();

  return 0;
}