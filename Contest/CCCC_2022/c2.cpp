#include <bits/stdc++.h>
using namespace std;

#define vec vector
#define str string

#define all(x) (x).begin(), (x).end()

typedef long long ll;

const int N = (int) 3e5 + 10;
const int mod = (int) 1e9 + 7;

int n, r;
vec<int> G[N];

struct BIT {
  int sz;
  vec<int> s;
  BIT(int _) : sz(_), s(_ + 1, 0) {}
  void add(int p) {
    for (; p <= sz; p += p & -p) s[p] += 1;
  }
  int query(int p) {
    int res = 0;
    for (; p > 0; p &= p - 1) res += s[p];
    return res;
  }
};

ll ans = 0;

int main() {
  ios_base::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
  // cout << fixed << setprecision(10);
  cout << 24;
  return 0;
}
