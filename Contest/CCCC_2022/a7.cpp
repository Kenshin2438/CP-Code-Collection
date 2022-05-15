#include <bits/stdc++.h>
using namespace std;

#define vec vector
#define str string
typedef long long ll;

const int N = (int) 1e5 + 10;

int r[N], c[N];

int main() {
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  cout << fixed << setprecision(10);
  int n, m, q; cin >> n >> m >> q;
  for (int op, p; q--; ) {
    cin >> op >> p;
    if (op == 0) {
      r[p] ++;
    } else {
      c[p] ++;
    }
  }
  ll R = count(r + 1, r + 1 + n, 0);
  ll C = count(c + 1, c + 1 + m, 0);
  // cout << "debug" << R << " " << C << " \n";
  cout << R * C << '\n';
  return 0;
}
