#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "debug.hpp"
#else
#define debug(...) 42
#endif

#define PII pair<int, int>
#define vec vector
#define str string
#define fi first
#define se second
#define all(a) (a).begin(), (a).end()
#define SZ(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

void SingleTest(int TestCase) {
  int N; cin >> N;
  vec<int> A(1 << N), B(1 << N);
  for (int &x : A) cin >> x;
  for (int i = 0; i < N; i++) {
    for (int s = 0; s < (1 << N); s++) {
      if (s >> i & 1) {
        int t = s ^ (1 << i);
        if (A[t] >= A[s]) {
          B[s] = A[s], A[s] = A[t];
        } else {
          B[s] = max(B[s], A[t]);
        }
      }
    }
  }
  int ans = 0;
  for (int s = 1; s < (1 << N); s++) {
    ans = max(ans, A[s] + B[s]);
    cout << ans << '\n';
  }
}

void init() {}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  // cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
