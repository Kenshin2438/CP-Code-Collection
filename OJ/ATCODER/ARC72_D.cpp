/*******************************
| Author:  Kenshin2438
| Problem: D - Alice&Brown
| Contest: AtCoder - AtCoder Regular Contest 072
| URL:     https://atcoder.jp/contests/arc072/tasks/arc072_b
| When:    2022-02-18 17:21:34
|
| Memory:  256 MB
| Time:    2000 ms
*******************************/

#include <bits/stdc++.h>
using namespace std;

#define PII pair<int, int>
#define PLL pair<ll, ll>
#define vec vector
#define str string
#define fi first
#define se second
#define pb push_back
#define all(a) a.begin(), a.end()

typedef long double db;
typedef long long ll;

void sol(int TestCase) {
  ll n, m; cin >> n >> m;
  cout << (llabs(n - m) > 1 ? "Alice" : "Brown");
}

void init() { }

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr), cout.tie(nullptr);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  // cin >> T;
  for (init(); T--; ) sol(++TestCase);
  return 0;
}
