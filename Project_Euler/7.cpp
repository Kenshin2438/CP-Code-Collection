#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define all(a) begin(a), end(a)

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);

  const int N = 1e6;
  vector<int> p, lpf(N, 0);
  for (int i = 2; i < N; i++) {
    if (lpf[i] == 0) lpf[i] = i, p.push_back(i);
    for (int x : p) {
      if (1LL * x * i >= N) break;
      lpf[x * i] = x;
      if (i % x == 0) break;
    }

    if (p.size() == 10'001) break;
  }
  cout << p.back() << '\n';
  return 0;
}