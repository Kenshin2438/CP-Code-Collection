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
#define rall(a) (a).rbegin(), (a).rend()
#define sz(x) static_cast<int>((x).size())

using db = double;
using ll = long long;

vec<int> ans;
void SingleTest(__attribute__((unused)) int TestCase) {
  int n; cin >> n;

  cout << ans[n - 1] << '\n';
}

const int LIM = 1e6;
bitset<LIM> isPrime;
void eratosthenes() {
  isPrime.set();
  isPrime[0] = isPrime[1] = 0;
  for (int i = 2; i < LIM; i++) if (isPrime[i])
    for (int j = i + i; j < LIM; j += i)
        isPrime[j] = 0;
}

void init() {
  eratosthenes();
  for (int i = 1; i <= 1e7; i++) {
    int sum = 0, _ = i;
    while (_) sum += _ % 10, _ /= 10;
    if (isPrime[sum]) ans.push_back(i);

    if (ans.size() == 100000) break;
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  // cout << fixed << setprecision(10);
  int T = 1, TestCase = 0;
  // cin >> T;
  for (init(); T--;) SingleTest(++TestCase);
  return 0;
}
